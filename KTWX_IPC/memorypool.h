#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

void* NewArray(int iSize);
void  DeleteArray(void* pPointer);

void* NewPacketInfo(int iDataSize=0);
void  DeletePacketInfo(void* pInfo);


#endif // MEMORYPOOL_H
