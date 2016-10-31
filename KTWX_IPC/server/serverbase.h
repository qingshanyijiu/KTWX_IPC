#ifndef SERVERBASE_H
#define SERVERBASE_H

#include "workdispatchbase.h"
#include <QLockFile>

class CServerBase
{
public:
    CServerBase(CWorkDispatchBase* pDispatcher);
    virtual ~CServerBase();

    virtual int StartServer(const char* pConName);
    virtual int StopServer();
    virtual int SendEventToClient(const char* lpData,int iLen)=0;
    virtual int SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen)=0;
    virtual int SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen)=0;

    static  int RunServer();

public:
    CWorkDispatchBase*   m_pWorkpDispatcher;

private:
    QLockFile*           m_pLockFile;
};

#endif // SERVERBASE_H
