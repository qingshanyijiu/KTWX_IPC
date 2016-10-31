#ifndef KTWX_LOG_CLIENT_H
#define KTWX_LOG_CLIENT_H


#ifdef WIN32
#define KTWX_LOG_CLIENT_API    __declspec(dllexport)
#else
#define KTWX_LOG_CLIENT_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

int KTWX_LOG_CLIENT_API InitLogClient(int *pConnectKey,const char* lpLogFileKey,int iLogLevel,int iSaveDays=90);

int KTWX_LOG_CLIENT_API SetLogLevel(int iConnectKey,int iLogLevel);

int KTWX_LOG_CLIENT_API WriteLogData(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel);

int KTWX_LOG_CLIENT_API WriteLogString(int iConnectKey,const char* lpData,int iLogLevel);

int KTWX_LOG_CLIENT_API WriteLogDataEx(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel,const char* lpLogFileKey);

int KTWX_LOG_CLIENT_API WriteLogStringEx(int iConnectKey,const char* lpData,int iLogLevel,const char* lpLogFileKey);

int KTWX_LOG_CLIENT_API CloseLog(int iConnectKey);

#ifdef __cplusplus
}
#endif

#endif // KTWX_LOG_CLIENT_H
