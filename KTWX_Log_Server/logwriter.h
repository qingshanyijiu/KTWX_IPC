#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <QMutex>
#include <QString>

const int KTDP_OFF_LOG_LEVEL     = 60000;
const int KTDP_FATAL_LOG_LEVEL   = 50000;
const int KTDP_ERROR_LOG_LEVEL   = 40000;
const int KTDP_WARN_LOG_LEVEL    = 30000;
const int KTDP_INFO_LOG_LEVEL    = 20000;
const int KTDP_DEBUG_LOG_LEVEL   = 10000;
const int KTDP_TRACE_LOG_LEVEL   = 0;
const int KTDP_ALL_LOG_LEVEL     = KTDP_TRACE_LOG_LEVEL;


class CLogWriter
{
public:
    CLogWriter();
    ~CLogWriter();

    void Open(const char* lpName,const char* lpPath,int iLogLevel,int iMaxBackup=90);
    void UpdateLevel(int iLevel);
    void Close();

    void Debug(const char * data, size_t len);
    void Infor(const char * data, size_t len);
    void Warning(const char * data, size_t len);
    void Error(const char * data, size_t len);
    void Fatal(const char * data, size_t len);

    void WriteLog(const char * data,int iLevel = KTDP_INFO_LOG_LEVEL);
    void WriteLog(const char * data,size_t len,int iLevel = KTDP_INFO_LOG_LEVEL);

private:
    void GetFilePath(QString& strPath);

protected:
    QString             m_strLogName;
    volatile bool       m_isOpen;
    QMutex              m_mutexLock;
};

#endif // LOGWRITER_H
