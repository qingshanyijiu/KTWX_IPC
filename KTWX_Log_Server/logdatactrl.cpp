#include "logdatactrl.h"
#include "ktwx_ipc_api.h"

#ifdef WIN32
#include <windows.h>
#else
#include<sys/sysinfo.h>
#endif

CLogDataCtrl::CLogDataCtrl()
{
    QThreadPool::globalInstance()->setMaxThreadCount(GetProcessorCount());
}

CLogDataCtrl::~CLogDataCtrl()
{
    Clear();
}

void CLogDataCtrl::PushMsg(PLogInfo pInfo)
{
    map<string,CLogDataInfo*>::iterator it = m_logFileMap.find(pInfo->pHead->csLogFileKey);
    if(it != m_logFileMap.end())
    {
        bool bCmd = pInfo->pHead->bCmd;
        it->second->PushMsg(pInfo);

        if(CMD_TYPE_CLOSE_LOG == bCmd)
        {
            QMutexLocker lock(&m_mutexLock);
            m_logFileMap.erase(it);
        }
    }
    else
    {
        if(CMD_TYPE_CLOSE_LOG == pInfo->pHead->bCmd)
        {
            IPCDeleteArray(pInfo->pHead);
            return;
        }

        QMutexLocker lock(&m_mutexLock);
        it = m_logFileMap.find(pInfo->pHead->csLogFileKey);
        if(it != m_logFileMap.end())
        {
            bool bCmd = pInfo->pHead->bCmd;
            it->second->PushMsg(pInfo);

            if(CMD_TYPE_CLOSE_LOG == bCmd)
                m_logFileMap.erase(it);
        }
        else
        {
            CLogDataInfo* pLog = new CLogDataInfo(QThreadPool::globalInstance());
            m_logFileMap.insert(pair<string,CLogDataInfo*>(pInfo->pHead->csLogFileKey,pLog));

            if(CMD_TYPE_OPEN_LOG != pInfo->pHead->bCmd)
            {
                LogInfo logData={0};
                logData.pHead = (PLogHeadInfo)IPCNewArray(sizeof(LogHeadInfo));
                logData.pHead->bCmd = CMD_TYPE_OPEN_LOG;
                logData.pHead->bLogLevel = pInfo->pHead->bLogLevel;
                strcpy(logData.pHead->csLogFileKey,pInfo->pHead->csLogFileKey);
                logData.pHead->csReserveData[0] = 90;

                pLog->PushMsg(&logData);
            }

            pLog->PushMsg(pInfo);
        }
    }
}

void CLogDataCtrl::Clear()
{
    QMutexLocker lock(&m_mutexLock);

    map<string,CLogDataInfo*>::iterator it = m_logFileMap.begin();
    while(it != m_logFileMap.end())
    {
        it->second->WaitForComplete();
        delete it->second;
        ++it;
    }

    m_logFileMap.clear();
}

int  CLogDataCtrl::GetProcessorCount()
{
    int iCount = 4;

#ifdef WIN32
   SYSTEM_INFO info;
   GetSystemInfo(&info);
   iCount = info.dwNumberOfProcessors;
#else
    iCount = get_nprocs();
#endif

    iCount = iCount*2+1;

    return iCount;
}
