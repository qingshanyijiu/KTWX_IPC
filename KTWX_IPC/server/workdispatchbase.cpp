#include "workdispatchbase.h"

CWorkDispatchBase::CWorkDispatchBase(fpDispMsgCallback pMsgCall,void* pUserInfo)
    :m_fpDispMsgCall(pMsgCall),m_pUserInfo(pUserInfo)
{
}

CWorkDispatchBase::~CWorkDispatchBase()
{

}

int CWorkDispatchBase::SetOnIdleInfo(void* fpOnIdleFunc,unsigned long ulIdleInterval)
{
    m_fpOnIdleCall = (fpOnIdleCallBack)fpOnIdleFunc;
    m_ulIdleInterval = ulIdleInterval;

    return KTWX_IPC_SUCCESS;
}
