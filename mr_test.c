#include "mr_list.h"

// 先让生产者生产一些数字
#define CONSUMER_WAIT_TIME 10

int main(void)
{
    MrList_t *list = (MrList_t*)malloc(sizeof(MrList_t));
    mrListCreate(&list);

    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, NULL, mrListAdd, &list);
    sleep(CONSUMER_WAIT_TIME);
    pthread_create(&consumer, NULL, mrListRemove, &list);

    pthread_join(consumer, NULL);

    mrListDes(&list);

    return 0;
}