#include "localserverconnection.h"
#include <QMutexLocker>
#include "memorypool.h"

CLocalServerConnection::CLocalServerConnection(qintptr socketDescriptor,CWorkDispatchBase* pDispatcher)
    :m_pWorkpDispatcher(pDispatcher)
{
    m_pIpcInfo = NULL;
    m_recvByteData.reserve(10240);

    setSocketDescriptor(socketDescriptor);
    this->moveToThread(&m_thread);

    connect(this,&QLocalSocket::disconnected,this,&CLocalServerConnection::HandleDisconnect);
    connect(this,&QLocalSocket::readyRead,this,&CLocalServerConnection::HandleReadData);

    m_thread.start();
}

CLocalServerConnection::~CLocalServerConnection()
{
    m_thread.quit();
    m_thread.wait(2000);

    if(isOpen())
        close();
}

void CLocalServerConnection::HandleDisconnect()
{
    m_pWorkpDispatcher->PushMsg(this,NULL);
}

void CLocalServerConnection::HandleReadData()
{
    /*if(NULL == m_pIpcInfo)
    {
        if(bytesAvailable()>=sizeof(unsigned int))
        {
            m_pIpcInfo = (PIPCPacketInfo)NewPacketInfo();

            if(!Readn(m_pIpcInfo,sizeof(unsigned int))||0 == m_pIpcInfo->nDataLen)
            {
                DeletePacketInfo(m_pIpcInfo);
                m_pIpcInfo = NULL;
                reset();
            }
            else
            {
    //            qDebug("Recv Len=%d\n",m_pIpcInfo->nDataLen);
                m_pIpcInfo->pPacketData = (unsigned char*)NewArray(m_pIpcInfo->nDataLen);
            }
        }
    }


    if(m_pIpcInfo)
    {
        if(bytesAvailable()>=m_pIpcInfo->nDataLen)
        {
            if(Readn(m_pIpcInfo->pPacketData,m_pIpcInfo->nDataLen))
            {
                m_pWorkpDispatcher->PushMsg(this,m_pIpcInfo);
            }
            else
            {
                DeletePacketInfo(m_pIpcInfo);
                reset();
            }

            m_pIpcInfo = NULL;
        }
    }*/

    m_recvByteData.push_back(readAll());

    int index = 0,iHeadLen=sizeof(unsigned int);

    do
    {
        if(NULL == m_pIpcInfo)
        {
            if(m_recvByteData.size()>=iHeadLen+index)
            {
                m_pIpcInfo = (PIPCPacketInfo)NewPacketInfo();
                memcpy(&m_pIpcInfo->nDataLen,m_recvByteData.data()+index,iHeadLen);
                index += iHeadLen;

                if(m_pIpcInfo->nDataLen)
                {
                     m_pIpcInfo->pPacketData = (unsigned char*)NewArray(m_pIpcInfo->nDataLen);
                }
                else
                {
                    DeletePacketInfo(m_pIpcInfo);
                    m_pIpcInfo = NULL;
                }
            }
            else
            {
                break;
            }
        }

        if(m_pIpcInfo)
        {
            if(m_recvByteData.size()>=m_pIpcInfo->nDataLen+index)
            {
                memcpy(m_pIpcInfo->pPacketData,m_recvByteData.data()+index,m_pIpcInfo->nDataLen);
                index += m_pIpcInfo->nDataLen;

                m_pWorkpDispatcher->PushMsg(this,m_pIpcInfo);
                m_pIpcInfo = NULL;
            }
            else
            {
                break;
            }
        }
    }while(index>0);

    if(index>0)
    {
        m_recvByteData = m_recvByteData.remove(0,index);
    }
}

bool CLocalServerConnection::Readn(void* pData,int iLen)
{
    int iReadLen = 0,index=0;
    bool bRet = false;

    do
    {
        iReadLen = read((char*)pData+index,iLen);
        if(iReadLen<=0)
        {
            break;
        }
        else
        {
            index += iReadLen;
            iLen -= iReadLen;
        }
    }while(iReadLen&&iLen);

    if(0 == iLen)
        bRet = true;

    return bRet;
}

bool CLocalServerConnection::Writen(const void* pData,int iLen)
{
    int iWriteLen = 0,index=0;
    bool bRet = false;

    do
    {
        iWriteLen = write((char*)pData+index,iLen);
        if(iWriteLen<=0)
        {
            break;
        }
        else
        {
            index += iWriteLen;
            iLen -= iWriteLen;
        }
    }while(iWriteLen&&iLen);

    if(0 == iLen)
    {
        bRet = true;//waitForBytesWritten(3000);
    }

    return bRet;
}

int  CLocalServerConnection::SendData(const void* pData,int iLen)
{
    return WriteInfo(pData,iLen);
}

bool CLocalServerConnection::WriteInfo(const void* pData,int iLen)
{
    QMutexLocker lock(&m_writeLock);

    bool bRet = Writen(&iLen,sizeof(iLen));
    if(bRet)
    {
        bRet = Writen(pData,iLen);
    }

    return bRet;
}

void  CLocalServerConnection::close()
{
    if(isOpen())
    {
        m_thread.quit();
        QLocalSocket::close();
        QLocalSocket::disconnectFromServer();
        emit QuitMyself(this);
    }
}
