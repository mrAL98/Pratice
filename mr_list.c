#include "mr_list.h"

#define PRODUCER_SLEEP_TIME 2
#define CONSUMER_SLEEP_TIME 1

// 链表初始化函数
void* mrListCreate(MrList_t *pMrList)
{
    pMrList->pHead = NULL;
    pMrList->pTail = NULL;
    pMrList->count = 0;
    pMrList->size = 0;

    if (0 > pthread_mutex_init(&pMrList->mrLock, NULL))
    {
        printf("%s\n", "[ERROR]:Mutex lock init failed. [mrListCreate]");
        return NULL;
    }

    printf("%s\n", "[INFO]:List create succeed. [mrListCreate]");
}

// 链表增加节点函数
void *mrListAdd(MrList_t *pMrList)
{
    while (1)
    {
        MrListNode_t *curNode = (MrListNode_t*)malloc(sizeof(MrListNode_t));

        if (NULL == curNode)
        {
            printf("%s\n", "[ERROR]:New node failed. [mrListAdd]");
            break;
        }
        // 创建节点成功
        curNode->data = pMrList->count;
        curNode->pNext = NULL;

        pthread_mutex_lock(&pMrList->mrLock);

        if (0 == pMrList->size)
        {
            pMrList->pHead = curNode;
            pMrList->pTail = curNode;
        }
        else 
        {
            pMrList->pTail->pNext = curNode;
            pMrList->pTail = curNode;
        }

        printf("%s%d%s\n", "[INFO]:List add node ", curNode->data, " succeed. [mrListAdd]");

        pMrList->size++;
        pMrList->count++;

        pthread_mutex_unlock(&pMrList->mrLock);
        sleep(PRODUCER_SLEEP_TIME);
    }

    return NULL;
}

// 链表删除节点函数
void *mrListRemove(MrList_t *pMrList)
{
    int data = 0;

    while (1) 
    {
        pthread_mutex_lock(&pMrList->mrLock);

        if (0 == pMrList->size)
        {
            printf("%s\n", "                                         \
                    [ERROR]:List empty. [mrListRemove]");
            pthread_mutex_unlock(&pMrList->mrLock);
            break;
        }

        data = pMrList->pHead->data;
        pMrList->pHead = pMrList->pHead->pNext;

        printf("%s%d%s\n", "                                            \
                [INFO]:List remove node ", data, " succeed. [mrListRemove]");

        pMrList->size--;

        if (0 == pMrList->size)
        {
            pMrList->pTail = NULL;
        }

        pthread_mutex_unlock(&pMrList->mrLock);
        sleep(CONSUMER_SLEEP_TIME);
    }

    return NULL;
}

// 链表释放函数
void *mrListDes(MrList_t *pMrList)
{
    MrListNode_t *curNode = NULL;

    if (NULL == pMrList)
    {
        printf("%s\n", "[ERROR]:List has been destroyed. [mrListDes]");
        return NULL;
    }

    pthread_mutex_lock(&pMrList->mrLock);

    if (0 == pMrList->size)
    {
        printf("%s\n", "[INFO]:List empty. [mrListDes]");
        pthread_mutex_unlock(&pMrList->mrLock);
        printf("%s\n", "[INFO]:List destroy succeed. [mrListDes]");
        return NULL;
    }

    while (pMrList->pHead)
    {
        curNode = pMrList->pHead->pNext;
        free(pMrList->pHead);
        pMrList->pHead = curNode;
    }

    pthread_mutex_unlock(&pMrList->mrLock);
    free(pMrList);

    printf("%s\n", "[INFO]:List destroy succeed. [mrListDes]");
}