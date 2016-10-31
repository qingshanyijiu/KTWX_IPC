#ifndef QUEUEDISPATCHER_H
#define QUEUEDISPATCHER_H

#include "workdispatchbase.h"
#include <QMutex>
#include <list>
#include <QThread>
#include <QSemaphore>
using namespace std;

typedef struct tagWorkItem
{
    QLocalSocket*  m_pSocket;
    PIPCPacketInfo m_pPack;

    tagWorkItem(QLocalSocket* pSocket,PIPCPacketInfo pPack)
    {
       m_pSocket =  pSocket;
       m_pPack = pPack;
    }
}WorkItem,*PWorkItem;

class CQueueDispatcher  : public CWorkDispatchBase,public QThread
{
public:
    CQueueDispatcher(fpDispMsgCallback pMsgCall,void* pUserInfo);
    ~CQueueDispatcher();

    void PushMsg(QLocalSocket* pSocket,PIPCPacketInfo pPack);
    void Stop();

    void run();

protected:
    void Clear();
    void DispatchMsg();

private:
    list<WorkItem>      m_itemList;
    QMutex              m_mutexLock;
    QSemaphore          m_itemSemap;
};

#endif // QUEUEDISPATCHER_H
