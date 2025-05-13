#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STR 50
#define MAX 100

struct db {
    int num;
    char string[STR];
};

void swap(struct db *db1,struct db *db2)
{
   struct db temp=*db2;
   *db2=*db1;
   *db1=temp;
}

int findmax(struct db *data,int size)
{ 
   
   int max=data[0].num;
   int i;
   for(i=1;i<size;i++)
   {
      if(data[i].num>max)
      {
         max=data[i].num;
      }
   }
   return max;
}

int partition(struct db *data,int low,int high)
{
   int pivot;
   pivot=data[high].num;
   int i=low;
   int j;
   for(j=low;j<high;j++)
   {
      if(data[j].num<=pivot)
      {
          swap(&data[j],&data[i]);
          i=i+1;
       }
    }
    swap(&data[i],&data[high]);
    return i;
}

void quicksort(struct db *data,int low,int high)
{
 int p;
 if(low>=high || low<0)
  {
      return;
   }
  p=partition(data,low,high);
  quicksort(data,low,p-1);
  quicksort(data,p+1,high);
}


void bucketsort(struct db *data,int size,int k)
{
     struct db **buckets = (struct db **)malloc(k * sizeof(struct db *));
    int *bucket_sizes = (int *)calloc(k, sizeof(int));
    int max = findmax(data, size);
    for (int i = 0; i < k; i++)
        buckets[i] = NULL; 
    for (int i = 0; i < size; i++) 
    {
        int bucketIndex = (k * data[i].num) / (max + 1);
        if (bucketIndex >= k) bucketIndex = k - 1;
        bucket_sizes[bucketIndex]++;
    }
    for (int i = 0; i < k; i++) {
        if (bucket_sizes[i] > 0)
            buckets[i] = (struct db *)malloc(bucket_sizes[i] * sizeof(struct db));
    }
    int *positions = (int *)calloc(k, sizeof(int));
    for (int i = 0; i < size; i++) {
        int bucketIndex = (k * data[i].num) / (max + 1);
        if (bucketIndex >= k) bucketIndex = k - 1;
        buckets[bucketIndex][positions[bucketIndex]++] = data[i];
    }
    free(positions); 
    int index = 0;
    for (int i = 0; i < k; i++) 
    {
        if (bucket_sizes[i] > 1) 
            quicksort(buckets[i], 0, bucket_sizes[i] - 1);

        for (int j = 0; j < bucket_sizes[i]; j++)
            data[index++] = buckets[i][j];

        free(buckets[i]); 
    }
    free(buckets);
    free(bucket_sizes);
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
    bucketsort(data, row,10);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
