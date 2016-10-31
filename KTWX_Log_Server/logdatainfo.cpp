#include "logdatainfo.h"
#include "ktwx_ipc_api.h"
#include <QMutexLocker>
#include <QDebug>

#define MAKEWORD(low,high)  (((high)<<8)|(low))

CLogDataInfo::CLogDataInfo(QThreadPool* pThreadPool)
    :m_pThreadPool(pThreadPool),m_currRunable(this)
{
    m_bIsWorking = false;
}

CLogDataInfo::~CLogDataInfo()
{

}

void CLogDataInfo::PushMsg(PLogInfo pInfo)
{
    QMutexLocker lock(&m_mutexLock);
    m_itemList.push_back(*pInfo);

    if(false == m_bIsWorking)
    {
        m_bIsWorking = true;
        m_pThreadPool->start(&m_currRunable);
    }
}

void CLogDataInfo::DisposeFrontItem()
{
    LogInfo& logInfo = m_itemList.front();

    switch(logInfo.pHead->bCmd)
    {
    case CMD_TYPE_WRITE_LOG:
        {
            m_logWriter.WriteLog((const char*)logInfo.pData,logInfo.pHead->nDataLen,logInfo.pHead->bLogLevel*KTDP_DEBUG_LOG_LEVEL);
            break;
        }
    case CMD_TYPE_OPEN_LOG:
        {
            m_logWriter.Open(logInfo.pHead->csLogFileKey,NULL,logInfo.pHead->bLogLevel*KTDP_DEBUG_LOG_LEVEL,\
                             MAKEWORD(logInfo.pHead->csReserveData[0],logInfo.pHead->csReserveData[1]));
            break;
        }
    case CMD_TYPE_CLOSE_LOG:
        {
            m_logWriter.Close();
            delete this;
            break;
        }
    case CMD_TYPE_SET_LOG_LEVEL:
        {
            m_logWriter.UpdateLevel(logInfo.pHead->bLogLevel*KTDP_DEBUG_LOG_LEVEL);
            break;
        }
    default:
        break;
    }

    IPCDeleteArray(logInfo.pHead);

    QMutexLocker lock(&m_mutexLock);
    m_itemList.pop_front();

    if(m_itemList.size())
        m_pThreadPool->start(&m_currRunable);
    else
        m_bIsWorking = false;
}

void CLogDataInfo::WaitForComplete()
{
    while (m_itemList.size()) {
       QThread::msleep(100);
    }
}
