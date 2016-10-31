#ifndef LOCALSERVERCONNECTION_H
#define LOCALSERVERCONNECTION_H

#include <QLocalSocket>
#include <QThread>
#include <QMutex>
#include <QByteArray>
#include "workdispatchbase.h"

class CLocalServerConnection : public QLocalSocket
{
    Q_OBJECT
public:
    CLocalServerConnection(qintptr socketDescriptor,CWorkDispatchBase* pDispatcher);
    ~CLocalServerConnection();

    bool WriteInfo(const void* pData,int iLen);
    void close();

protected:
    bool  Readn(void* pData,int iLen);
    bool  Writen(const void* pData,int iLen);

signals:
    void  QuitMyself(CLocalServerConnection*);

public slots:
    int   SendData(const void* pData,int iLen);

public slots:
    void  HandleDisconnect();
    void  HandleReadData();

private:
    QThread              m_thread;
    CWorkDispatchBase*   m_pWorkpDispatcher;
    PIPCPacketInfo       m_pIpcInfo;
    QMutex               m_writeLock;
    QByteArray           m_recvByteData;
};

#endif // LOCALSERVERCONNECTION_H
