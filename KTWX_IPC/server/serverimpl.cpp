#include "serverimpl.h"
#include "server/concurrencedispatcher.h"
#include "server/queuedispatcher.h"
#include "localserverimpl.h"

CServerImpl::CServerImpl()
{
    m_pConnServer = NULL;
    m_pDispatcher = NULL;
}

CServerImpl::~CServerImpl()
{
    if(m_pConnServer)
    {
        delete m_pConnServer;
        m_pConnServer = NULL;
    }

    if(m_pDispatcher)
    {
        delete m_pDispatcher;
        m_pDispatcher = NULL;
    }
}

int CServerImpl::InitServer(void* fpMsgFunc,unsigned char bDispatchMode,void* pUserInfo)
{
    if(NULL == m_pDispatcher)
    {
        if(SERVER_DISPATCH_TYPE_CONCURR == bDispatchMode)
            m_pDispatcher = new ConcurrenceDispatcher((fpDispMsgCallback)fpMsgFunc,pUserInfo);
        else
            m_pDispatcher = new CQueueDispatcher((fpDispMsgCallback)fpMsgFunc,pUserInfo);
    }

    if(NULL == m_pConnServer)
    {
        m_pConnServer = new CLocalServerImpl(m_pDispatcher);
    }

    return KTWX_IPC_SUCCESS;
}

int CServerImpl::SetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval)
{
    if(NULL == m_pDispatcher)
        return KTWX_IPC_ERROR;

    return m_pDispatcher->SetOnIdleInfo(fpOnIdleFunc,ulIdleInterval);
}

int CServerImpl::StartServer(const char* pConName)
{
    if(NULL == m_pConnServer)
        return KTWX_IPC_ERROR;

    return m_pConnServer->StartServer(pConName);
}

int CServerImpl::StopServer()
{
    if(NULL == m_pConnServer)
        return KTWX_IPC_ERROR;

    return m_pConnServer->StopServer();
}

int CServerImpl::SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen)
{
    if(NULL == m_pConnServer)
        return KTWX_IPC_ERROR;

    if(NULL == lpData||0==iLen)
        return KTWX_IPC_ERROR;

    return m_pConnServer->SendCurrCmdResultToClient(pClientObject,lpData,iLen);
}

int CServerImpl::SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen)
{
    if(NULL == m_pConnServer)
        return KTWX_IPC_ERROR;

    if(NULL == lpData||0==iLen)
        return KTWX_IPC_ERROR;

    return m_pConnServer->SendCurrCmdEventToClient(pClientObject,lpData,iLen);
}

int CServerImpl::SendEventToClient(const char* lpData,int iLen)
{
    if(NULL == m_pConnServer)
        return KTWX_IPC_ERROR;

    if(NULL == lpData||0==iLen)
        return KTWX_IPC_ERROR;

    return m_pConnServer->SendEventToClient(lpData,iLen);
}

int CServerImpl::RunServer()
{
    return CServerBase::RunServer();
}
