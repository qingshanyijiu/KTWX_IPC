#ifndef LOGCLIENTIMPL_H
#define LOGCLIENTIMPL_H

#include "ktwx_ipc_api.h"
#include "ktwx_ipc_def.h"
#include <map>
#include <QMutex>
#include <string>
using namespace std;

class CLogClientImpl
{
private:
    CLogClientImpl();

public:
    ~CLogClientImpl();
    static CLogClientImpl& GetInstance();

public:
    int InitLogClient(int *pConnectKey,const char* lpLogFileKey,int iLogLevel,int iSaveDays);
    int SetLogLevel(int iConnectKey,int iLogLevel);
    int WriteLogData(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel);
    int WriteLogString(int iConnectKey,const char* lpData,int iLogLevel);
    int WriteLogDataEx(int iConnectKey,unsigned char* lpData,int iDataLen,int iLogLevel,const char* lpLogFileKey);
    int WriteLogStringEx(int iConnectKey,const char* lpData,int iLogLevel,const char* lpLogFileKey);
    int CloseLog(int iConnectKey);

private:
    int CloseClient(int iConnectKey,const char* lpFileKey);

private:
    QMutex              m_mutexLock;
    map<int,string>     m_fileKeyMap;
};

#endif // LOGCLIENTIMPL_H
