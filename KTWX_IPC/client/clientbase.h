#ifndef CLIENTBASE_H
#define CLIENTBASE_H

#include "ktwx_ipc_def.h"
#include <QObject>

class CClientBase   :public QObject
{
public:
    CClientBase(int iKey);
    virtual ~CClientBase();

    virtual int ConnectSever(const char* pConName,void* fpMsgFunc,void* pUserInfo);
    virtual int ConnectSever(const char* pConName)=0;
    virtual int DisConnect()=0;
    virtual int SendDataToServer(const char* lpData,int iLen)=0;

public:
    static  int GetUniqueKey();

protected:
    fpDispMsgCallback   m_fpMsgCall;
    void*               m_pUserInfo;
    int                 m_iKey;
};

#endif // CLIENTBASE_H
