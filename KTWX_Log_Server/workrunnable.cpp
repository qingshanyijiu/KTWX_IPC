#include "workrunnable.h"
#include "logdatainfo.h"

CWorkRunnable::CWorkRunnable(CLogDataInfo* pDataInfo)
    :m_pLogData(pDataInfo)
{
    setAutoDelete(false);
}

CWorkRunnable::~CWorkRunnable()
{

}

void CWorkRunnable::run()
{
    m_pLogData->DisposeFrontItem();
}
