#include "mutilclientimpl.h"
#include "ktwx_ipc_def.h"
#include "localsocketclient.h"
#include <QProcess>
#include <QMutexLocker>
#include <QLockFile>
#include <QThread>

CMutilClientImpl::CMutilClientImpl()
{
}

CMutilClientImpl::~CMutilClientImpl()
{
    Clear();
}

int  CMutilClientImpl::ConnectSever(int* pKey,const char* pConName,void* fpMsgFunc,void* pUserInfo)
{
    if(NULL==pKey||NULL==pConName)
        return KTWX_IPC_ERROR;

    QMutexLocker lock(&m_mutexLock);

    int iKey = CClientBase::GetUniqueKey();

    CClientBase* pClient = new CLocalSocketClient(iKey);
    if(KTWX_IPC_SUCCESS == pClient->ConnectSever(pConName,fpMsgFunc,pUserInfo))
    {
        *pKey = iKey;
        m_clientMap.insert(pair<int,CClientBase*>(*pKey,pClient));

        return KTWX_IPC_SUCCESS;
    }
    else
    {
        delete pClient;
        return KTWX_IPC_ERROR;
    }
}

int  CMutilClientImpl::DisConnect(int iKey)
{
    int iRet = KTWX_IPC_ERROR;
    QMutexLocker lock(&m_mutexLock);

    std::map<int,CClientBase*>::iterator it = m_clientMap.find(iKey);

    if(it !=m_clientMap.end())
    {
        iRet = it->second->DisConnect();
        delete it->second;

        m_clientMap.erase(it);
    }

    return iRet;
}

int  CMutilClientImpl::SendDataToServer(int iKey,const char* lpData,int iLen)
{
    if(NULL == lpData||0==iLen)
        return KTWX_IPC_ERROR;

    int iRet = KTWX_IPC_ERROR;

    std::map<int,CClientBase*>::iterator it = m_clientMap.end();
    it = m_clientMap.find(iKey);

    if(it !=m_clientMap.end())
    {
        iRet = it->second->SendDataToServer(lpData,iLen);
    }

    return iRet;
}

bool CMutilClientImpl::IsServerStart(const char* pConName)
{
    QString strLockName = pConName;
    strLockName +="_Lock";

    QLockFile lockFile(strLockName);

    if(!lockFile.tryLock())
        return true;
    else
    {
       lockFile.unlock();
      // lockFile.removeStaleLockFile();

       return false;
    }
}

int  CMutilClientImpl::OpenServerProcess(const char* pConName,const char* pServerExeName)
{
    if(IsServerStart(pConName))
        return KTWX_IPC_SUCCESS;

    if(!QProcess::startDetached(pServerExeName,QStringList(pServerExeName)))
        return KTWX_IPC_ERROR;

    QThread::sleep(1);

    return KTWX_IPC_SUCCESS;
}

void CMutilClientImpl::Clear()
{
    QMutexLocker lock(&m_mutexLock);

    map<int,CClientBase*>::iterator it = m_clientMap.begin();
    while(it != m_clientMap.end())
    {
        it->second->DisConnect();
        delete it->second;
        ++it;
    }

    m_clientMap.clear();
}
