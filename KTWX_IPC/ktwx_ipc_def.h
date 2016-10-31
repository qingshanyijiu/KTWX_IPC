#ifndef KTWX_IPC_DEF_H
#define KTWX_IPC_DEF_H

#pragma pack (push, 1)

//***********************返回值以及类型定义*************************//

#define KTWX_IPC_SUCCESS        (0)
#define KTWX_IPC_ERROR          (1)
#define KTWX_IPC_TIMEOUT		(2)

//***********************回调函数********************************//
//消息数据回调,返回true：数据内部释放，返回false:外部手动释放
typedef bool (__stdcall *fpDispMsgCallback)(void* pClientObject,void* pMsgData,void* pUserInfo);

//空闲时间回调操作
typedef void (__stdcall *fpOnIdleCallBack)(void* pUserInfo);

//***********************公共结构定义************************//

typedef struct tagIPCPacketInfo
{
    unsigned int       nDataLen;
    unsigned char*     pPacketData;
}IPCPacketInfo,*PIPCPacketInfo;

//***********************服务器端定义**************************//
#define   SERVER_DISPATCH_TYPE_QUEUE               (0)
#define   SERVER_DISPATCH_TYPE_CONCURR             (1)


//***********************客户端定义***************************//


#pragma pack(pop)

#endif // KTWX_IPC_DEF_H
