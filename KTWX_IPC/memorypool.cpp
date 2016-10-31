#include "memorypool.h"
#include "ktwx_ipc_def.h"
#include "lib/tcmalloc.h"
#include <string.h>

void* NewArray(int iSize)
{
    if(0 == iSize)
        return NULL;

    void* pData =  tc_newarray(iSize);//new char[iSize];
    if(pData)
        memset(pData,0,iSize);

    return pData;
}

void  DeleteArray(void* pPointer)
{
    if(pPointer)
//        delete [] pPointer;
        tc_deletearray(pPointer);
}

void* NewPacketInfo(int iDataSize/*=0*/)
{
    PIPCPacketInfo pInfo = (PIPCPacketInfo)tc_newarray(sizeof(IPCPacketInfo));
    if(pInfo)
    {
        memset(pInfo,0,sizeof(IPCPacketInfo));
        if(iDataSize)
        {
            pInfo->pPacketData = (unsigned char*)tc_newarray(iDataSize);
            if(NULL == pInfo->pPacketData)
            {
                tc_deletearray(pInfo);
                pInfo = NULL;
            }
            else
            {
                pInfo->nDataLen = iDataSize;
                memset(pInfo->pPacketData,0,iDataSize);
            }
        }
        return pInfo;
    }
    else
    {
        return NULL;
    }
}

void  DeletePacketInfo(void* pInfo)
{
    PIPCPacketInfo pPacketInfo = (PIPCPacketInfo) pInfo;
    if(pPacketInfo)
    {
        if(pPacketInfo->pPacketData)
            tc_deletearray(pPacketInfo->pPacketData);

        tc_deletearray(pPacketInfo);
    }
}
