#include "logwriter.h"
#include "log4cplus/logger.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/layout.h"
#include "log4cplus/ndc.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/loggingmacros.h"
#include <QMutexLocker>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

CLogWriter::CLogWriter()
{
    m_strLogName = "Test";
    m_isOpen = false;
}

CLogWriter::~CLogWriter()
{
    Close();
}

void CLogWriter::GetFilePath(QString& strPath)
{
    wchar_t csBuf[256]={0};
    QString strFind;

#ifdef _WIN32
    ::GetModuleFileName(NULL,csBuf, 256 );
    strFind = '\\';
#else
    readlink( "/proc/self/exe", csBuf, 256 );
    strFind = '/';
#endif

   QString strTemp = QString::fromUtf16((unsigned short*)csBuf);
   strPath = strTemp.left(strTemp.lastIndexOf(strFind)+1);
}

void CLogWriter::Open(const char* lpName,const char* lpPath,int iLogLevel,int iMaxBackup/*=90*/)
{
    if(m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    m_strLogName = lpName;

    QString strPath;

    if(NULL==lpPath)
            GetFilePath(strPath);
    else
           strPath =lpPath;
    strPath  += "/KTWX_LOG_DATA/";
    strPath  += lpName;
    strPath  += '/';
    strPath  += lpName;

    SharedAppenderPtr append(new DailyRollingFileAppender(strPath.toStdWString(),  DAILY, true, iMaxBackup,true));
    append->setName(m_strLogName.toStdWString());

    QString pattern = "%D{%Y-%m-%d %H:%M:%S.%q}\t %-5p\t %m\t %n";
    std::auto_ptr<Layout> layout(new PatternLayout(pattern.toStdWString()));
    append->setLayout(layout);

    Logger::getInstance(m_strLogName.toStdWString()).addAppender(append);
    Logger::getInstance(m_strLogName.toStdWString()).setLogLevel(iLogLevel);

    m_isOpen = true;
}

void CLogWriter::UpdateLevel(int iLevel)
{
    if(!m_isOpen)
           return;

    QMutexLocker lock(&m_mutexLock);
    Logger::getInstance(m_strLogName.toStdWString()).setLogLevel(iLevel);
}

void CLogWriter::Close()
{
    QMutexLocker lock(&m_mutexLock);
    if(m_isOpen)
    {
        Logger::getInstance(m_strLogName.toStdWString()).shutdown();
        m_isOpen = false;
    }
}

void CLogWriter::Debug(const char * data, size_t len)
{
    if(!m_isOpen)
           return;

   QMutexLocker lock(&m_mutexLock);

   Logger log = Logger::getInstance(m_strLogName.toStdWString());

   LOG4CPLUS_DEBUG(log,QString::fromLocal8Bit(data,len).toStdWString());
}

void CLogWriter::Infor(const char * data, size_t len)
{
    if(!m_isOpen)
          return;


  QMutexLocker lock(&m_mutexLock);

  Logger log = Logger::getInstance(m_strLogName.toStdWString());

  LOG4CPLUS_INFO(log,QString::fromLocal8Bit(data,len).toStdWString());
}

void CLogWriter::Warning(const char * data, size_t len)
{
    if(!m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    Logger log = Logger::getInstance(m_strLogName.toStdWString());

    LOG4CPLUS_WARN(log,QString::fromLocal8Bit(data,len).toStdWString());
}

void CLogWriter::Error(const char * data, size_t len)
{
    if(!m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    Logger log = Logger::getInstance(m_strLogName.toStdWString());

    LOG4CPLUS_ERROR(log,QString::fromLocal8Bit(data,len).toStdWString());
}

void CLogWriter::Fatal(const char * data, size_t len)
{
    if(!m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    Logger log = Logger::getInstance(m_strLogName.toStdWString());

    LOG4CPLUS_FATAL(log,QString::fromLocal8Bit(data,len).toStdWString());
}

void CLogWriter::WriteLog(const char * data,int iLevel /*= KTDP_INFO_LOG_LEVEL*/)
{
    if(!m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    Logger log = Logger::getInstance(m_strLogName.toStdWString());

    switch (iLevel) {
    case KTDP_DEBUG_LOG_LEVEL:   LOG4CPLUS_DEBUG(log,data);      break;
    case KTDP_INFO_LOG_LEVEL:    LOG4CPLUS_INFO(log,data);      break;
    case KTDP_WARN_LOG_LEVEL:    LOG4CPLUS_WARN(log,data);      break;
    case KTDP_ERROR_LOG_LEVEL:   LOG4CPLUS_ERROR(log,data);      break;
    case KTDP_FATAL_LOG_LEVEL:   LOG4CPLUS_FATAL(log,data);      break;
    default:
         LOG4CPLUS_INFO(log,data);
        break;
    }
}

void CLogWriter::WriteLog(const char * data,size_t len,int iLevel /*= KTDP_INFO_LOG_LEVEL*/)
{
    if(!m_isOpen)
        return;

    QMutexLocker lock(&m_mutexLock);

    Logger log = Logger::getInstance(m_strLogName.toStdWString());

//    std::locale::global(std::locale(""));
//    std::wstring str = QString::fromLocal8Bit(data,len).toStdWString();

    switch (iLevel) {
    case KTDP_DEBUG_LOG_LEVEL:   LOG4CPLUS_DEBUG(log,QString::fromLocal8Bit(data,len).toStdWString());      break;
    case KTDP_INFO_LOG_LEVEL:    LOG4CPLUS_INFO(log,QString::fromLocal8Bit(data,len).toStdWString());      break;
    case KTDP_WARN_LOG_LEVEL:    LOG4CPLUS_WARN(log,QString::fromLocal8Bit(data,len).toStdWString());      break;
    case KTDP_ERROR_LOG_LEVEL:   LOG4CPLUS_ERROR(log,QString::fromLocal8Bit(data,len).toStdWString());      break;
    case KTDP_FATAL_LOG_LEVEL:   LOG4CPLUS_FATAL(log,QString::fromLocal8Bit(data,len).toStdWString());      break;
    default:
         LOG4CPLUS_INFO(log,QString::fromLocal8Bit(data,len).toStdWString());
        break;
    }
}
