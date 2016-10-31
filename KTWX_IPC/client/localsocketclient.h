#ifndef LOCALSOCKETCLIENT_H
#define LOCALSOCKETCLIENT_H

#include "clientbase.h"
#include <QLocalSocket>
#include <QMutex>

class CLocalSocketClient : public CClientBase
{
    Q_OBJECT
public:
    CLocalSocketClient(int iKey);
    ~CLocalSocketClient();

    int ConnectSever(const char* pConName);
    int DisConnect();
    int SendDataToServer(const char* lpData,int iLen);

public slots:
    void HandleRecvData();

protected:
    bool  Readn(void* pData,int iLen);
    bool  Writen(const void* pData,int iLen);

private:
    QLocalSocket    m_localSocket;
    PIPCPacketInfo  m_pPacketInfo;
    QMutex          m_mutexLock;
};

#endif // LOCALSOCKETCLIENT_H
