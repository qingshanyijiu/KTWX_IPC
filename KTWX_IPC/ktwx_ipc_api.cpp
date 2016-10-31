#include "ktwx_ipc_api.h"
#include "server/serverimpl.h"
#include "client/mutilclientimpl.h"
#include "memorypool.h"

//****************Server Interface *****************//

int KTWX_IPC_API IPCInitServer(void* fpMsgFunc,unsigned char bDispatchMode,void* pUserInfo)
{
    return CServerImpl::GetInstance()->InitServer(fpMsgFunc,bDispatchMode,pUserInfo);
}

int KTWX_IPC_API IPCSetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval)
{
    return CServerImpl::GetInstance()->SetOnIdleInfo(fpOnIdleFunc,ulIdleInterval);
}

int KTWX_IPC_API IPCStartServer(const char* pConName)
{
    return CServerImpl::GetInstance()->StartServer(pConName);
}

int KTWX_IPC_API IPCStopServer()
{
    return CServerImpl::GetInstance()->StopServer();
}

int KTWX_IPC_API IPCSendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen)
{
    return CServerImpl::GetInstance()->SendCurrCmdResultToClient(pClientObject,lpData,iLen);
}

int KTWX_IPC_API IPCSendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen)
{
    return CServerImpl::GetInstance()->SendCurrCmdEventToClient(pClientObject,lpData,iLen);
}

int KTWX_IPC_API IPCSendEventToClient(const char* lpData,int iLen)
{
    return CServerImpl::GetInstance()->SendEventToClient(lpData,iLen);
}

int KTWX_IPC_API IPCRunServer()
{
    return CServerImpl::RunServer();
}


//****************Client Interface *****************//

int KTWX_IPC_API IPCConnectSever(int* pKey,const char* pConName,void* fpMsgFunc,void* pUserInfo)
{
    return CMutilClientImpl::GetInstance()->ConnectSever(pKey,pConName,fpMsgFunc,pUserInfo);
}

int KTWX_IPC_API IPCDisConnect(int iKey)
{
    return CMutilClientImpl::GetInstance()->DisConnect(iKey);
}

int KTWX_IPC_API IPCSendDataToServer(int iKey,const char* lpData,int iLen)
{
    return CMutilClientImpl::GetInstance()->SendDataToServer(iKey,lpData,iLen);
}

bool KTWX_IPC_API IPCIsServerStart(const char* pConName)
{
    return CMutilClientImpl::IsServerStart(pConName);
}

int KTWX_IPC_API IPCOpenServerProcess(const char* pConName,const char* pServerExeName)
{
    return CMutilClientImpl::OpenServerProcess(pConName,pServerExeName);
}

void* KTWX_IPC_API IPCNewArray(int iSize)
{
    return NewArray(iSize);
}

void  KTWX_IPC_API IPCDeleteArray(void* pPointer)
{
    DeleteArray(pPointer);
}

void* KTWX_IPC_API IPCNewPacketInfo(int iDataSize)
{
    return NewPacketInfo(iDataSize);
}

void  KTWX_IPC_API IPCDeletePacketInfo(void* pInfo)
{
    DeletePacketInfo(pInfo);
}
