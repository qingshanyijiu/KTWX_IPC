#ifndef LOGCLIENT_H
#define LOGCLIENT_H

#include <QThread>
#include <QString>

class CLogClient : public QThread
{
    Q_OBJECT
public:
    explicit CLogClient(QObject *parent = 0);
    ~CLogClient();

    void Start(const char* lpFileKey,int iLevel,QString& strData);
    void run();

public slots:
    void exit();

private:
    int         m_iKey;
    QString     m_strData;
};

#endif // LOGCLIENT_H
