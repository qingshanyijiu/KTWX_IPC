#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#include "SingletonInstance.h"
#include "server/serverbase.h"
#include "server/workdispatchbase.h"

class CServerImpl   :public CSingletonInstance<CServerImpl>
{
public:
    CServerImpl();
    ~CServerImpl();

    int InitServer(void* fpMsgFunc,unsigned char bDispatchMode,void* pUserInfo);
    int SetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval);
    int StartServer(const char* pConName);
    int StopServer();
    int SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen);
    int SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen);
    int SendEventToClient(const char* lpData,int iLen);

    static int  RunServer();

private:
    CServerBase*        m_pConnServer;
    CWorkDispatchBase*  m_pDispatcher;
};

#endif // SERVERIMPL_H
