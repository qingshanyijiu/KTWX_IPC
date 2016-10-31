#ifndef WORKRUNNABLE_H
#define WORKRUNNABLE_H

#include <QRunnable>


class CLogDataInfo;
class CWorkRunnable : public QRunnable
{
public:
    CWorkRunnable(CLogDataInfo* pDataInfo);
    ~CWorkRunnable();

    void run();

private:
    CLogDataInfo*   m_pLogData;
};

#endif // WORKRUNNABLE_H
