#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int counter=0;
pthread_mutex_t mutex;
pthread_cond_t condition;
int ready = 0;

void* print_message(void* arg) {
    size_t thread_id = (size_t)arg;

    pthread_mutex_lock(&mutex);
    while (ready == 0) {
        pthread_cond_wait(&condition, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    printf("Νήμα %zu ολοκλήρωσε\n", thread_id);
    return NULL;
}


int main(int argc,char* argv[])
{

   if (argc < 2) {
        fprintf(stderr, "Χρήση: %s <αριθμός νημάτων>\n", argv[0]);
        return 1;
    }

int threads_num=strtol(argv[1],NULL,10);
if (threads_num <= 0) {
        fprintf(stderr, "Ο αριθμός νημάτων πρέπει να είναι θετικός ακέραιος.\n");
        return 1;
    }
pthread_t* thread_handles;
thread_handles = malloc(threads_num * sizeof(pthread_t));
if (thread_handles == NULL) {
        fprintf(stderr, "Αποτυχία δέσμευσης μνήμης για τα νήματα.\n");
        return 1;
    }
 pthread_mutex_init(&mutex, NULL);
for(int thread=0;thread<threads_num;thread++)
    pthread_create(&thread_handles[thread], NULL, print_message, (void*)(size_t) thread);
sleep(3);
pthread_mutex_lock(&mutex);
ready = 1;
pthread_cond_broadcast(&condition);
pthread_mutex_unlock(&mutex);
for(int thread=0;thread<threads_num;thread++)
    pthread_join(thread_handles[thread], NULL);
printf("counter is :%d\n",counter);
pthread_mutex_destroy(&mutex);
free(thread_handles);
   return 0;
}
