#include "localserverimpl.h"

CLocalServerImpl::CLocalServerImpl(CWorkDispatchBase* pDispatcher)
    :CServerBase(pDispatcher),m_localServer(this)
{

}

CLocalServerImpl::~CLocalServerImpl()
{

}

int CLocalServerImpl::StartServer(const char* pConName)
{
    int iRet = CServerBase::StartServer(pConName);
    if(KTWX_IPC_SUCCESS == iRet)
        iRet = m_localServer.Start(pConName)?KTWX_IPC_SUCCESS:KTWX_IPC_ERROR;

    return iRet;
}

int CLocalServerImpl::StopServer()
{
    m_localServer.Stop();

    return CServerBase::StopServer();
}

int CLocalServerImpl::SendEventToClient(const char* lpData,int iLen)
{
    m_localServer.SendDataToClient(lpData,iLen);

    return KTWX_IPC_SUCCESS;
}

int CLocalServerImpl::SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen)
{
    return m_localServer.SendCurrCmdResultToClient(pClientObject,lpData,iLen);
}

int CLocalServerImpl::SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen)
{
    return m_localServer.SendCurrCmdEventToClient(pClientObject,lpData,iLen);
}


