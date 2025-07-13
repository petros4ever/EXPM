#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define STR 50
#define SIZE 1000000  
#define MAX_DEPTH 3  

struct db {
    int num;
    char string[STR];
};

struct thread_args {
    struct db* data;
    int low;
    int high;
    int depth;
};

void swap(struct db* a, struct db* b) {
    struct db temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct db* data, int low, int high) {
    int pivot = data[high].num;
    int i = low;
    for (int j = low; j < high; j++) {
        if (data[j].num <= pivot) {
            swap(&data[i], &data[j]);
            i++;
        }
    }
    swap(&data[i], &data[high]);
    return i;
}

void quicksort(struct db* data, int low, int high) {
    if (low >= high) return;
    int p = partition(data, low, high);
    quicksort(data, low, p - 1);
    quicksort(data, p + 1, high);
}

void* threaded_quicksort(void* arg) {
    struct thread_args* args = (struct thread_args*)arg;
    int low = args->low;
    int high = args->high;
    int depth = args->depth;
    struct db* data = args->data;
    free(arg);

    if (low >= high) return NULL;

    int p = partition(data, low, high);

    if (depth > 0) {
        pthread_t left, right;

        struct thread_args* left_args = malloc(sizeof(struct thread_args));
        left_args->data = data;
        left_args->low = low;
        left_args->high = p - 1;
        left_args->depth = depth - 1;
        pthread_create(&left, NULL, threaded_quicksort, left_args);

        struct thread_args* right_args = malloc(sizeof(struct thread_args));
        right_args->data = data;
        right_args->low = p + 1;
        right_args->high = high;
        right_args->depth = depth - 1;
        pthread_create(&right, NULL, threaded_quicksort, right_args);

        pthread_join(left, NULL);
        pthread_join(right, NULL);
    } else {
        quicksort(data, low, p - 1);
        quicksort(data, p + 1, high);
    }

    return NULL;
}

void measure_time(const char* label, void (*func)(struct db*, int, int), struct db* array, int low, int high) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    func(array, low, high);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("⏱️ %s: %.6f seconds\n", label, elapsed);
}

int main() {
    struct db* original = malloc(SIZE * sizeof(struct db));
    struct db* data_seq = malloc(SIZE * sizeof(struct db));
    struct db* data_threaded = malloc(SIZE * sizeof(struct db));
    if (!original || !data_seq || !data_threaded) {
        fprintf(stderr, "Αποτυχία δέσμευσης μνήμης!\n");
        return 1;
    }
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        original[i].num = rand() % SIZE;
        snprintf(original[i].string, STR, "val_%d", original[i].num);
    }
    memcpy(data_seq, original, SIZE * sizeof(struct db));
    memcpy(data_threaded, original, SIZE * sizeof(struct db));
    measure_time("Σειριακό quicksort", quicksort, data_seq, 0, SIZE - 1);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    struct thread_args* args = malloc(sizeof(struct thread_args));
    args->data = data_threaded;
    args->low = 0;
    args->high = SIZE - 1;
    args->depth = MAX_DEPTH;
    threaded_quicksort(args);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("⏱️ Πολυνηματικό quicksort: %.6f seconds\n", elapsed);
    free(original);
    free(data_seq);
    free(data_threaded);

    return 0;
}
