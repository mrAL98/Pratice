#ifndef __MR_LIST_H__
#define __MR_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>

typedef struct MrListNode
{
    struct MrListNode *pNext;
    int data;    
} MrListNode_t;

typedef struct MrList
{
    MrListNode_t *pHead;
    MrListNode_t *pTail;
    pthread_mutex_t mrLock;
    int count;
    int size;
} MrList_t;

// 链表初始化函数
void *mrListCreate(MrList_t *pMrList);
// 链表增加节点函数
void *mrListAdd(MrList_t *pMrList);
// 链表删除节点函数
void *mrListRemove(MrList_t *pMrList);
// 链表释放函数
void *mrListDes(MrList_t *pMrList);

#endif