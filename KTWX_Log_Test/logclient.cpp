#include "logclient.h"
#include "ktwx_log_client.h"
#include "mainwindow.h"

CLogClient::CLogClient(QObject *parent) :
    QThread(parent)
{
    m_iKey = 0;

    connect((MainWindow*)parent,&MainWindow::closeLog,this,&CLogClient::exit);
}

CLogClient::~CLogClient()
{
    requestInterruption();
    wait(2000);

    CloseLog(m_iKey);
}


void CLogClient::Start(const char* lpFileKey,int iLevel,QString& strData)
{
    InitLogClient(&m_iKey,lpFileKey,iLevel,90);
    m_strData = strData;

    QThread::start();
}

void CLogClient::run()
{
    QByteArray byteArray = m_strData.toLocal8Bit();
    while(!isInterruptionRequested())
    {
//        WriteLogString(m_iKey,"All_Log_Info",0);
//        WriteLogString(m_iKey,"DEBUG_LOG_LEVEL",1);
//        WriteLogString(m_iKey,"INFO_LOG_LEVEL",2);
//        WriteLogString(m_iKey,"WARN_LOG_LEVEL",3);
//        WriteLogString(m_iKey,"ERROR_LOG_LEVEL",4);
//        WriteLogString(m_iKey,"FATAL_LOG_LEVEL",5);
        byteArray.data()[0] = 'A';
        WriteLogData(m_iKey,(unsigned char*)byteArray.data(),byteArray.size(),1);
        byteArray.data()[0] = 'B';
        WriteLogData(m_iKey,(unsigned char*)byteArray.data(),byteArray.size(),2);
        byteArray.data()[0] = 'C';
        WriteLogData(m_iKey,(unsigned char*)byteArray.data(),byteArray.size(),3);
        byteArray.data()[0] = 'D';
        WriteLogData(m_iKey,(unsigned char*)byteArray.data(),byteArray.size(),4);
        byteArray.data()[0] = 'E';
        WriteLogData(m_iKey,(unsigned char*)byteArray.data(),byteArray.size(),5);

        msleep(200);
    }
}

void CLogClient::exit()
{
    requestInterruption();
    wait(2000);

    CloseLog(m_iKey);
}
