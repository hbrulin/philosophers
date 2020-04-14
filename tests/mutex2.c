#include <stdlib.h>
#include <pthread.h>

typedef struct data {
    int var;
    pthread_mutex_t mutex;
} data;

int main(void)
{
    data new_data;
    new_data.mutex = PTHREAD_MUTEX_INITIALIZER; //autre manière d'initialiser un mutex
    return EXIT_SUCCESS;
}
