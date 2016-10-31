#ifndef CONCURRENCEDISPATCHER_H
#define CONCURRENCEDISPATCHER_H

#include "workdispatchbase.h"

class ConcurrenceDispatcher : public CWorkDispatchBase
{
public:
    ConcurrenceDispatcher(fpDispMsgCallback pMsgCall,void* pUserInfo);
    ~ConcurrenceDispatcher();

    void PushMsg(QLocalSocket* pSocket,PIPCPacketInfo pPack);
    void Stop();
};

#endif // CONCURRENCEDISPATCHER_H
