#ifndef LOGSERVER_H
#define LOGSERVER_H

#include "logdatactrl.h"

class CLogServer
{
public:
    CLogServer();
    ~CLogServer();

    bool Init();

public:
    static bool DisposeMsg(void* pClientObject,void* pMsgData,void* pUserInfo);

private:
    CLogDataCtrl    m_logCtrl;
};

#endif // LOGSERVER_H
