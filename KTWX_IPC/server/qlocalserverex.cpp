#include "qlocalserverex.h"
#include <QMutexLocker>
#include "localserverconnection.h"

QLocalServerEx::QLocalServerEx(CServerBase* pSever)
    :m_pSever(pSever)
{
}

QLocalServerEx::~QLocalServerEx()
{
    Stop();
}

bool QLocalServerEx::Start(const char* pConnectName)
{
    if(!isListening())
    {
        removeServer(pConnectName);
        if(!listen(pConnectName))
        {
            qDebug()<<errorString();
            return false;
        }
    }

    return true;
}

void QLocalServerEx::Stop()
{
    {
        QMutexLocker lock(&m_mutexLock);
        set<CLocalServerConnection*>::iterator it = m_connectSet.begin();
        while(it != m_connectSet.end())
        {
            delete (*it);
            ++it;
        }
        m_connectSet.clear();
    }

    if(isListening())
        close();
}

void QLocalServerEx::incomingConnection(quintptr socketDescriptor)
{
    CLocalServerConnection* pNewConn = new CLocalServerConnection(socketDescriptor,m_pSever->m_pWorkpDispatcher);
    connect(pNewConn,&CLocalServerConnection::QuitMyself,this,&QLocalServerEx::HandleClientQuit);

    QMutexLocker lock(&m_mutexLock);
    m_connectSet.insert(pNewConn);
}

void QLocalServerEx::HandleClientQuit(CLocalServerConnection* pSocket)
{
    {
        QMutexLocker lock(&m_mutexLock);
        set<CLocalServerConnection*>::iterator it = m_connectSet.find(pSocket);
        if(it != m_connectSet.end())
        {
            delete (*it);
            m_connectSet.erase(it);
        }
    }

    if(0 == m_connectSet.size())
        m_pSever->StopServer();
}

void QLocalServerEx::SendDataToClient(const char* lpData,int iLen)
{
    set<CLocalServerConnection*>::iterator it = m_connectSet.begin();
    while(it != m_connectSet.end())
    {
        (*it)->WriteInfo(lpData,iLen);

        ++it;
    }
}

int  QLocalServerEx::SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen)
{
    CLocalServerConnection* pConnClient = (CLocalServerConnection*)pClientObject;
    if(NULL == pConnClient)
        return KTWX_IPC_ERROR;

    bool bRet = pConnClient->WriteInfo(lpData,iLen);

    return  bRet?KTWX_IPC_ERROR:KTWX_IPC_SUCCESS;
}

int  QLocalServerEx::SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen)
{
    CLocalServerConnection* pConnClient = (CLocalServerConnection*)pClientObject;
    if(NULL == pConnClient)
        return KTWX_IPC_ERROR;

    bool bRet = pConnClient->WriteInfo(lpData,iLen);

    return  bRet?KTWX_IPC_ERROR:KTWX_IPC_SUCCESS;
}
