#ifndef WORKDISPATCHBASE_H
#define WORKDISPATCHBASE_H

#include "ktwx_ipc_def.h"
#include <QLocalSocket>

class CWorkDispatchBase
{
public:
    CWorkDispatchBase(fpDispMsgCallback pMsgCall,void* pUserInfo);
    virtual ~CWorkDispatchBase();

    int SetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval);

    virtual void PushMsg(QLocalSocket* pSocket,PIPCPacketInfo pPack)=0;
    virtual void Stop()=0;

protected:
    fpDispMsgCallback   m_fpDispMsgCall;
    void*               m_pUserInfo;
    fpOnIdleCallBack    m_fpOnIdleCall;
    unsigned long       m_ulIdleInterval;
};

#endif // WORKDISPATCHBASE_H
