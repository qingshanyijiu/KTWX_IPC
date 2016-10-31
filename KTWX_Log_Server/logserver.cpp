#include "logserver.h"
#include "../KTWX_Log_Client/KTWX_Log_Client_Def.h"
#include "ktwx_ipc_api.h"
#include "ktwx_ipc_def.h"

CLogServer::CLogServer()
{

}

CLogServer::~CLogServer()
{
    IPCStopServer();
}

bool CLogServer::Init()
{
    int iRet = IPCInitServer((void*)DisposeMsg,SERVER_DISPATCH_TYPE_CONCURR,this);
    if(KTWX_IPC_SUCCESS ==  iRet)
    {
        iRet = IPCStartServer(LOG_CONNECT_NAME);
    }

    return (iRet==KTWX_IPC_SUCCESS)?true:false;
}

bool CLogServer::DisposeMsg(void* pClientObject,void* pMsgData,void* pUserInfo)
{
    PIPCPacketInfo pPacketInfo = (PIPCPacketInfo)pMsgData;

    LogInfo logInfo = {0};
    logInfo.pHead = (PLogHeadInfo)pPacketInfo->pPacketData;
    if(pPacketInfo->nDataLen > sizeof(LogHeadInfo))
        logInfo.pData = pPacketInfo->pPacketData+sizeof(LogHeadInfo);

    ((CLogServer*)pUserInfo)->m_logCtrl.PushMsg(&logInfo);
    IPCDeleteArray(pMsgData);

    return false;
}
