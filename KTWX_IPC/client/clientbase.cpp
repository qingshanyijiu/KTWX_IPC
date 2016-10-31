#include "clientbase.h"

CClientBase::CClientBase(int iKey)
    :m_iKey(iKey)
{
    m_fpMsgCall = 0;
    m_pUserInfo = 0;
}

CClientBase::~CClientBase()
{

}

int CClientBase::ConnectSever(const char* pConName,void* fpMsgFunc,void* pUserInfo)
{
    m_fpMsgCall = (fpDispMsgCallback)fpMsgFunc;
    m_pUserInfo = pUserInfo;

    return ConnectSever(pConName);
}

int CClientBase::GetUniqueKey()
{
    static  int iUniqueKey =0;

    return (++iUniqueKey);
}
