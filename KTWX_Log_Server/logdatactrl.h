#ifndef LOGDATACTRL_H
#define LOGDATACTRL_H

#include "logdatainfo.h"
#include <map>
#include <string>
#include <QMutex>
using namespace std;

class CLogDataCtrl
{
public:
    CLogDataCtrl();
    ~CLogDataCtrl();

    void PushMsg(PLogInfo pInfo);

private:
    void Clear();
    int  GetProcessorCount();

private:
    QMutex                      m_mutexLock;
    map<string,CLogDataInfo*>   m_logFileMap;
};

#endif // LOGDATACTRL_H
