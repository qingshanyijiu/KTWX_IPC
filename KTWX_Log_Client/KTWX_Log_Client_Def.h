#ifndef KTWX_LOG_CLIENT_DEF_H
#define KTWX_LOG_CLIENT_DEF_H

#pragma pack (push, 1)

#define LOG_CONNECT_NAME            ("ktLogConnectName")

#define CMD_TYPE_WRITE_LOG          (0)
#define CMD_TYPE_OPEN_LOG           (1)
#define CMD_TYPE_CLOSE_LOG          (2)
#define CMD_TYPE_SET_LOG_LEVEL      (3)


typedef struct tagLogHeadInfo
{
    unsigned char   bCmd;
    unsigned char   bLogLevel;
    char            csLogFileKey[32];
    unsigned int    nDataLen;
    unsigned char   csReserveData[8];
}LogHeadInfo,*PLogHeadInfo;

typedef struct tagLogInfo
{
    PLogHeadInfo    pHead;
    unsigned char*  pData;
}LogInfo,*PLogInfo;


#pragma pack(pop)

#endif // KTWX_LOG_CLIENT_DEF_H
