#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter=0;
 pthread_mutex_t mutex;

void* print_message(void* arg) {
 
         for (int i = 0; i < 100000; i++) {
          pthread_mutex_lock(&mutex);
          counter++;
          pthread_mutex_unlock(&mutex);
       }
       return NULL;
    }

int main()
{
   pthread_t thread1, thread2;
   pthread_mutex_init(&mutex, NULL);
   pthread_create(&thread1, NULL, print_message, "Νήμα 1");
   pthread_create(&thread2, NULL, print_message, "Νήμα 2");
   
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   printf("counter is :%d\n",counter);
   pthread_mutex_destroy(&mutex);
   return 0;
}