#ifndef LOGDATAINFO_H
#define LOGDATAINFO_H

#include "../KTWX_Log_Client/KTWX_Log_Client_Def.h"
#include "workrunnable.h"
#include "logwriter.h"
#include <list>
#include <QMutex>
#include <QThreadPool>
using namespace std;

class CLogDataInfo
{
public:
    CLogDataInfo(QThreadPool* pThreadPool);
    ~CLogDataInfo();

    void PushMsg(PLogInfo pInfo);
    void DisposeFrontItem();
    void WaitForComplete();

private:
    QMutex              m_mutexLock;
    list<LogInfo>       m_itemList;
    volatile bool       m_bIsWorking;
    CWorkRunnable       m_currRunable;
    QThreadPool*        m_pThreadPool;

private:
    CLogWriter          m_logWriter;
};

#endif // LOGDATAINFO_H
