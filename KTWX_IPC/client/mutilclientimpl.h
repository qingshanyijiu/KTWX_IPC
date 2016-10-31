#ifndef MUTILCLIENTIMPL_H
#define MUTILCLIENTIMPL_H

#include "SingletonInstance.h"
#include "clientbase.h"
#include <QMutex>
#include <map>
using namespace std;

class CMutilClientImpl :public CSingletonInstance<CMutilClientImpl>
{
public:
    CMutilClientImpl();
    ~CMutilClientImpl();

    int  ConnectSever(int* pKey,const char* pConName,void* fpMsgFunc,void* pUserInfo);
    int  DisConnect(int iKey);
    int  SendDataToServer(int iKey,const char* lpData,int iLen);
    static bool IsServerStart(const char* pConName);
    static int  OpenServerProcess(const char* pConName,const char* pServerExeName);

protected:
    void Clear();

private:
    map<int,CClientBase*>   m_clientMap;
    QMutex                  m_mutexLock;
};

#endif // MUTILCLIENTIMPL_H
