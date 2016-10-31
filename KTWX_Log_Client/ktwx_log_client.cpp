#include "ktwx_log_client.h"
#include "logclientimpl.h"


int KTWX_LOG_CLIENT_API InitLogClient(int *pConnectKey,const char* lpLogFileKey,int iLogLevel,int iSaveDays)
{
    return CLogClientImpl::GetInstance().InitLogClient(pConnectKey,lpLogFileKey,iLogLevel,iSaveDays);
}

int KTWX_LOG_CLIENT_API SetLogLevel(int iConnectKey,int iLogLevel)
{
    return CLogClientImpl::GetInstance().SetLogLevel(iConnectKey,iLogLevel);
}

int KTWX_LOG_CLIENT_API WriteLogData(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel)
{
    return CLogClientImpl::GetInstance().WriteLogData(iConnectKey,lpData,iDataLen,iLogLevel);
}

int KTWX_LOG_CLIENT_API WriteLogString(int iConnectKey,const char* lpData,int iLogLevel)
{
    return CLogClientImpl::GetInstance().WriteLogString(iConnectKey,lpData,iLogLevel);
}

int KTWX_LOG_CLIENT_API WriteLogDataEx(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel,const char* lpLogFileKey)
{
    return CLogClientImpl::GetInstance().WriteLogDataEx(iConnectKey,lpData,iDataLen,iLogLevel,lpLogFileKey);
}

int KTWX_LOG_CLIENT_API WriteLogStringEx(int iConnectKey,const char* lpData,int iLogLevel,const char* lpLogFileKey)
{
    return CLogClientImpl::GetInstance().WriteLogStringEx(iConnectKey,lpData,iLogLevel,lpLogFileKey);
}

int KTWX_LOG_CLIENT_API CloseLog(int iConnectKey)
{
    return CLogClientImpl::GetInstance().CloseLog(iConnectKey);
}
