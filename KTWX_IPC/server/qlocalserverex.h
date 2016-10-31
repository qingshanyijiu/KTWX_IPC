#ifndef QLOCALSERVEREX_H
#define QLOCALSERVEREX_H

#include <QLocalServer>
#include "workdispatchbase.h"
#include "localserverconnection.h"
#include "serverbase.h"
#include <set>
#include <QMutex>
using namespace std;

class QLocalServerEx    : public QLocalServer
{
    Q_OBJECT
public:
    QLocalServerEx(CServerBase* pSever);
    ~QLocalServerEx();

    bool Start(const char* pConnectName);
    void Stop();
    void SendDataToClient(const char* lpData,int iLen);
    int  SendCurrCmdResultToClient(void* pClientObject,const char* lpData,int iLen);
    int  SendCurrCmdEventToClient(void* pClientObject,const char* lpData,int iLen);

protected:
    void incomingConnection(quintptr socketDescriptor);

public slots:
    void HandleClientQuit(CLocalServerConnection* pSocket);

private:
    set<CLocalServerConnection*>    m_connectSet;
    QMutex                          m_mutexLock;
    CServerBase*                    m_pSever;
};

#endif // QLOCALSERVEREX_H
