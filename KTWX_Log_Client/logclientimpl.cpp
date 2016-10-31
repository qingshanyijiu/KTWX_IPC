#include "logclientimpl.h"
#include "KTWX_Log_Client_Def.h"
#include <QMutexLocker>
#include <string.h>


class CSendData
{
public:
    CSendData(int iDataLen=0) {
        if(iDataLen)
        {
            m_iDataLen = sizeof(LogHeadInfo)+iDataLen;
            void* pBuffer = IPCNewArray(m_iDataLen);
            m_logInfo.pHead = (PLogHeadInfo)pBuffer;
            m_logInfo.pData = (unsigned char*)(pBuffer+sizeof(LogHeadInfo));

            m_logInfo.pHead->nDataLen = iDataLen;
        }
        else
        {
            m_iDataLen = sizeof(LogHeadInfo);
            m_logInfo.pHead = (PLogHeadInfo)IPCNewArray(m_iDataLen);
            m_logInfo.pData = NULL;
        }
    }
    ~CSendData()
    {
        IPCDeleteArray(m_logInfo.pHead);
    }

    const char* GetSendData(){
        return (char*)(m_logInfo.pHead);
    }

public:
    LogInfo   m_logInfo;
    int       m_iDataLen;
};

CLogClientImpl::CLogClientImpl()
{
#ifdef WIN32
    IPCOpenServerProcess(LOG_CONNECT_NAME,"KTWX_LOG_Server.exe");
#else
    IPCOpenServerProcess(LOG_CONNECT_NAME,"KTWX_LOG_Server");
#endif
}

CLogClientImpl::~CLogClientImpl()
{
    map<int,string>::iterator it = m_fileKeyMap.begin();
    while(it != m_fileKeyMap.end())
    {
        CloseClient(it->first,it->second.c_str());
        ++it;
    }
    m_fileKeyMap.clear();
}

CLogClientImpl& CLogClientImpl::GetInstance()
{
    static CLogClientImpl s_clientImpl;

    return s_clientImpl;
}

int CLogClientImpl::InitLogClient(int *pConnectKey,const char* lpLogFileKey,int iLogLevel,int iSaveDays)
{
    if(NULL==pConnectKey||NULL==lpLogFileKey)
        return KTWX_IPC_ERROR;

    if(KTWX_IPC_SUCCESS == IPCConnectSever(pConnectKey,LOG_CONNECT_NAME,NULL,NULL))
    {
        {
            QMutexLocker lock(&m_mutexLock);
            m_fileKeyMap.insert(pair<int,string>(*pConnectKey,lpLogFileKey));
        }

        CSendData sendData;
        sendData.m_logInfo.pHead->bCmd = CMD_TYPE_OPEN_LOG;
        sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
        strncpy(sendData.m_logInfo.pHead->csLogFileKey,lpLogFileKey,32);
        sendData.m_logInfo.pHead->csReserveData[0] = iSaveDays&0xFF;
        sendData.m_logInfo.pHead->csReserveData[1] = (iSaveDays>>8)&0xFF;

        return IPCSendDataToServer(*pConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
    }
    else
    {
        return KTWX_IPC_ERROR;
    }
}

int CLogClientImpl::SetLogLevel(int iConnectKey,int iLogLevel)
{
    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    CSendData sendData;
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_SET_LOG_LEVEL;
    sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
    strncpy(sendData.m_logInfo.pHead->csLogFileKey,it->second.c_str(),32);

    return IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
}

int CLogClientImpl::WriteLogData(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel)
{
    if(NULL == lpData||0==iDataLen)
        return KTWX_IPC_ERROR;

    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    CSendData sendData(iDataLen);
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_WRITE_LOG;
    sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
    strncpy(sendData.m_logInfo.pHead->csLogFileKey,it->second.c_str(),32);
    memcpy(sendData.m_logInfo.pData,lpData,iDataLen);

    return IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
}

int CLogClientImpl::WriteLogString(int iConnectKey,const char* lpData,int iLogLevel)
{
    if(NULL == lpData)
        return KTWX_IPC_ERROR;

    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    int iStrLen = strlen(lpData);
    CSendData sendData(iStrLen);
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_WRITE_LOG;
    sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
    strncpy(sendData.m_logInfo.pHead->csLogFileKey,it->second.c_str(),32);
    memcpy(sendData.m_logInfo.pData,lpData,iStrLen);

    return IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
}

int CLogClientImpl::WriteLogDataEx(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel,const char* lpLogFileKey)
{
    if(NULL == lpData||0==iDataLen)
        return KTWX_IPC_ERROR;

    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    CSendData sendData(iDataLen);
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_WRITE_LOG;
    sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
    if(NULL==lpLogFileKey)
        strncpy(sendData.m_logInfo.pHead->csLogFileKey,it->second.c_str(),32);
    else
        strncpy(sendData.m_logInfo.pHead->csLogFileKey,lpLogFileKey,32);
    memcpy(sendData.m_logInfo.pData,lpData,iDataLen);

    return IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
}

int CLogClientImpl::WriteLogStringEx(int iConnectKey,const char* lpData,int iLogLevel,const char* lpLogFileKey)
{
    if(NULL == lpData)
        return KTWX_IPC_ERROR;

    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    int iStrLen = strlen(lpData);
    CSendData sendData(iStrLen);
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_WRITE_LOG;
    sendData.m_logInfo.pHead->bLogLevel = iLogLevel&0xFF;
    if(NULL==lpLogFileKey)
        strncpy(sendData.m_logInfo.pHead->csLogFileKey,it->second.c_str(),32);
    else
        strncpy(sendData.m_logInfo.pHead->csLogFileKey,lpLogFileKey,32);
    memcpy(sendData.m_logInfo.pData,lpData,iStrLen);

    return IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);
}

int CLogClientImpl::CloseLog(int iConnectKey)
{
    map<int,string>::iterator it = m_fileKeyMap.find(iConnectKey);
    if(it == m_fileKeyMap.end())
        return KTWX_IPC_ERROR;

    CloseClient(it->first,it->second.c_str());

    QMutexLocker lock(&m_mutexLock);
    m_fileKeyMap.erase(it);

    return KTWX_IPC_SUCCESS;
}

int CLogClientImpl::CloseClient(int iConnectKey,const char* lpFileKey)
{
    CSendData sendData;
    sendData.m_logInfo.pHead->bCmd = CMD_TYPE_CLOSE_LOG;
    strncpy(sendData.m_logInfo.pHead->csLogFileKey,lpFileKey,32);
    IPCSendDataToServer(iConnectKey,sendData.GetSendData(),sendData.m_iDataLen);

    return IPCDisConnect(iConnectKey);
}
