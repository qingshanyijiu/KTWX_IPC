#ifndef LOCALSERVERIMPL_H
#define LOCALSERVERIMPL_H

#include "serverbase.h"
#include "qlocalserverex.h"

class CLocalServerImpl  : public CServerBase
{
public:
    CLocalServerImpl(CWorkDispatchBase* pDispatcher);
    ~CLocalServerImpl();

    int StartServer(const char* pConName);
    int StopServer();
    int SendEventToClient(const char* lpData,int iLen);
    int SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen);
    int SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen);

private:
    QLocalServerEx     m_localServer;
};

#endif // LOCALSERVERIMPL_H
