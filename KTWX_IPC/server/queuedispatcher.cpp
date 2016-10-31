#include "queuedispatcher.h"
#include <QMutexLocker>
#include <QTime>
#include "localserverconnection.h"
#include "memorypool.h"

CQueueDispatcher::CQueueDispatcher(fpDispMsgCallback pMsgCall,void* pUserInfo)
    :CWorkDispatchBase(pMsgCall,pUserInfo)
{
    start();
}

CQueueDispatcher::~CQueueDispatcher()
{
   Stop();
   Clear();
}

void CQueueDispatcher::PushMsg(QLocalSocket* pSocket,PIPCPacketInfo pPack)
{
    {
        QMutexLocker lock(&m_mutexLock);
        m_itemList.push_back(WorkItem(pSocket,pPack));
    }

    m_itemSemap.release();
}

void CQueueDispatcher::Stop()
{
     requestInterruption();
     wait(2000);
}


void CQueueDispatcher::run()
{
    QTime timer;

    qDebug("\nDisThreadID =%d,0x%x\n",QThread::currentThreadId(),QThread::currentThread());

    timer.start();
    while(!isInterruptionRequested())
    {
        if(m_itemSemap.tryAcquire(1,500))
        {
            if(m_itemList.size())
                DispatchMsg();

            timer.restart();
        }
        else
        {
            if(m_fpOnIdleCall&&timer.elapsed()>m_ulIdleInterval)
            {
                m_fpOnIdleCall(m_pUserInfo);
                timer.restart();
            }
        }
    }
}

void CQueueDispatcher::Clear()
{
    QMutexLocker lock(&m_mutexLock);

    list<WorkItem>::iterator it = m_itemList.begin();
    while(it != m_itemList.end())
    {
        DeletePacketInfo(it->m_pPack);
        ++it;
    }
    m_itemList.clear();
}

void CQueueDispatcher::DispatchMsg()
{
    WorkItem& workItem = m_itemList.front();

    if(workItem.m_pPack)
    {
        if(m_fpDispMsgCall(workItem.m_pSocket,workItem.m_pPack,m_pUserInfo))
        {
            DeletePacketInfo(workItem.m_pPack);
        }
    }
    else
    {
        workItem.m_pSocket->close();
    }

    QMutexLocker lock(&m_mutexLock);
    m_itemList.pop_front();
}
