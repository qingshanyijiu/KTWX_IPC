#include "localsocketclient.h"
#include "../ktwx_ipc_def.h"
#include "memorypool.h"
#include <QThread>
#include <QMutexLocker>

CLocalSocketClient::CLocalSocketClient(int iKey)
    :CClientBase(iKey)
{
    m_pPacketInfo = NULL;
}

CLocalSocketClient::~CLocalSocketClient()
{
    DisConnect();
}

int CLocalSocketClient::ConnectSever(const char* pConName)
{
    bool bRet = false;
    int  iCount=300;
    m_localSocket.connectToServer(pConName);

    do
    {
        bRet = m_localSocket.waitForConnected();
        if(!bRet)
        {
            qDebug()<<m_localSocket.error()<<","<<m_localSocket.errorString();
        }
        else
        {
            break;
        }

        QThread::msleep(100);
    }while(--iCount);


    if(m_fpMsgCall)
        connect(&m_localSocket,&QLocalSocket::readyRead,this,&CLocalSocketClient::HandleRecvData);

    return bRet?KTWX_IPC_SUCCESS:KTWX_IPC_ERROR;
}

int CLocalSocketClient::DisConnect()
{
    if(m_localSocket.isOpen())
        m_localSocket.disconnectFromServer();

    return KTWX_IPC_SUCCESS;
}

int CLocalSocketClient::SendDataToServer(const char* lpData,int iLen)
{
    if(!m_localSocket.isOpen())
        return KTWX_IPC_ERROR;

    QMutexLocker lock(&m_mutexLock);

    bool bRet= Writen(&iLen,sizeof(int));
    if(bRet)
        bRet = Writen(lpData,iLen);

    return bRet?KTWX_IPC_SUCCESS:KTWX_IPC_ERROR;
}

void CLocalSocketClient::HandleRecvData()
{
    if(NULL == m_pPacketInfo)
    {
        if(m_localSocket.bytesAvailable()>=sizeof(unsigned int))
        {
            m_pPacketInfo = (PIPCPacketInfo)NewPacketInfo();

            if(!Readn(m_pPacketInfo,sizeof(unsigned int))||0 == m_pPacketInfo->nDataLen)
            {
                DeletePacketInfo(m_pPacketInfo);
                m_pPacketInfo = NULL;
                m_localSocket.reset();
            }
            else
            {
                //qDebug("Recv Len=%d\n",m_pPacketInfo->nDataLen);

                m_pPacketInfo->pPacketData = (unsigned char*)NewArray(m_pPacketInfo->nDataLen);
            }
        }
    }

    if(m_pPacketInfo)
    {
        if(m_localSocket.bytesAvailable()>=m_pPacketInfo->nDataLen)
        {
            if(Readn(m_pPacketInfo->pPacketData,m_pPacketInfo->nDataLen))
            {
                if(m_fpMsgCall(&m_iKey,m_pPacketInfo,m_pUserInfo))
                {
                    DeletePacketInfo(m_pPacketInfo);
                }
            }
            else
            {
                m_localSocket.reset();
                DeletePacketInfo(m_pPacketInfo);
            }

            m_pPacketInfo = NULL;
        }
    }
}

bool CLocalSocketClient::Readn(void* pData,int iLen)
{
    int iReadLen = 0,index=0;
    bool bRet = false;

    do
    {
        iReadLen = m_localSocket.read((char*)pData+index,iLen);
        if(iReadLen<=0)
        {
            break;
        }
        else
        {
            index += iReadLen;
            iLen -= iReadLen;
        }
    }while(iReadLen&&iLen);

    if(0 == iLen)
        bRet = true;

    return bRet;
}

bool CLocalSocketClient::Writen(const void* pData,int iLen)
{
    int iWriteLen = 0,index=0;
    bool bRet = false;

    do
    {
        iWriteLen = m_localSocket.write((char*)pData+index,iLen);
        if(iWriteLen<=0)
        {
            break;
        }
        else
        {
            index += iWriteLen;
            iLen -= iWriteLen;
        }
    }while(iWriteLen&&iLen);

    if(0 == iLen)
    {
        bRet = true;//m_localSocket.waitForBytesWritten(3000);
    }

    return bRet;
}
