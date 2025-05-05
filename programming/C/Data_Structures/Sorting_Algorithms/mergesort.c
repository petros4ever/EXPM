#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR 50
#define MAX 100

struct db {
    int num;
    char string[STR];
};


void merge(struct db *data, struct db *left, int left_size, struct db *right, int right_size) 
{
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) 
    {
        if (left[i].num <= right[j].num) 
        {
            data[k++] = left[i++];
        } 
        else 
        {
            data[k++] = right[j++];
        }
    }
    while (i < left_size) 
    {
        data[k++] = left[i++];
    }

    while (j < right_size) 
    {
        data[k++] = right[j++];
    }
}


void mergesort(struct db *data, int size) 
{
    if (size <= 1) return;

    int mid = size / 2;
    struct db left[mid], right[size - mid];

    
    for (int i = 0; i < mid; i++)
        left[i] = data[i];

    for (int i = mid; i < size; i++)
        right[i - mid] = data[i];

    mergesort(left, mid);
    mergesort(right, size - mid);
    merge(data, left, mid, right, size - mid);
}

int main(void) 
{
    FILE *f;
    int row = 0, i;
    struct db data[MAX];
    f = fopen("sort.txt", "r");
    if (f == NULL) 
    {
        printf("Error opening file!\n");
        return 1;
    }
    while (fscanf(f, "%d %s", &data[row].num, data[row].string) != EOF) 
    {
        row++;
    }
    fclose(f);
    mergesort(data, row);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
