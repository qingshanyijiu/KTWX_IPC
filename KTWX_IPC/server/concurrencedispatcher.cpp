#include "concurrencedispatcher.h"
#include "memorypool.h"

ConcurrenceDispatcher::ConcurrenceDispatcher(fpDispMsgCallback pMsgCall,void* pUserInfo)
    :CWorkDispatchBase(pMsgCall,pUserInfo)
{

}

ConcurrenceDispatcher::~ConcurrenceDispatcher()
{

}

void ConcurrenceDispatcher::PushMsg(QLocalSocket* pSocket,PIPCPacketInfo pPack)
{
    if(pPack)
    {
        if(m_fpDispMsgCall)
        {
            if(m_fpDispMsgCall(pSocket,pPack,m_pUserInfo))
            {
                DeletePacketInfo(pPack);
            }
        }
        else
        {
            DeletePacketInfo(pPack);
        }
    }
    else
    {
        pSocket->close();
    }
}

void ConcurrenceDispatcher::Stop()
{

}
