#ifndef KTWX_IPC_API_H
#define KTWX_IPC_API_H

#ifdef WIN32
#define KTWX_IPC_API    __declspec(dllexport)
#else
#define KTWX_IPC_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

//****************Server Interface *****************//

int KTWX_IPC_API IPCInitServer(void* fpMsgFunc,unsigned char bDispatchMode,void* pUserInfo);

int KTWX_IPC_API IPCSetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval);

int KTWX_IPC_API IPCStartServer(const char* pConName);

int KTWX_IPC_API IPCStopServer();

int KTWX_IPC_API IPCSendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen);

int KTWX_IPC_API IPCSendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen);

int KTWX_IPC_API IPCSendEventToClient(const char* lpData,int iLen);

int KTWX_IPC_API IPCRunServer();


//****************Client Interface *****************//

int KTWX_IPC_API IPCConnectSever(int* pKey,const char* pConName,void* fpMsgFunc,void* pUserInfo);

int KTWX_IPC_API IPCDisConnect(int iKey);

int KTWX_IPC_API IPCSendDataToServer(int iKey,const char* lpData,int iLen);

bool KTWX_IPC_API IPCIsServerStart(const char* pConName);

int KTWX_IPC_API IPCOpenServerProcess(const char* pConName,const char* pServerExeName);

//*************** memory pool*********************//

void* KTWX_IPC_API IPCNewArray(int iSize);

void  KTWX_IPC_API IPCDeleteArray(void* pPointer);

void* KTWX_IPC_API IPCNewPacketInfo(int iDataSize);

void  KTWX_IPC_API IPCDeletePacketInfo(void* pInfo);

#ifdef __cplusplus
}
#endif


#endif // KTWX_IPC_API_H
