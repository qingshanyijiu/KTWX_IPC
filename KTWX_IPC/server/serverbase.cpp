#include "serverbase.h"
#include <QApplication>

CServerBase::CServerBase(CWorkDispatchBase* pDispatcher)
    :m_pWorkpDispatcher(pDispatcher)
{
    m_pLockFile = NULL;
}

CServerBase::~CServerBase()
{
    StopServer();
}

int CServerBase::StartServer(const char* pConName)
{
    QString strLockName = pConName;
    strLockName +="_Lock";

    m_pLockFile = new QLockFile(strLockName);

    if(m_pLockFile->tryLock())
        return KTWX_IPC_SUCCESS;
    else
    {
        return KTWX_IPC_ERROR;
    }
}

int CServerBase::StopServer()
{
    m_pWorkpDispatcher->Stop();

    if(m_pLockFile)
    {
        m_pLockFile->unlock();
        m_pLockFile->removeStaleLockFile();

        delete m_pLockFile;
        m_pLockFile = NULL;
    }

   QApplication::quit();

   return KTWX_IPC_SUCCESS;
}

int CServerBase::RunServer()
{
    return QApplication::exec();
}
