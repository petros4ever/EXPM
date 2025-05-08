#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void quicksort(struct db *data,int size,int low,int high)
{
 int p;
 if(low>=high || low<0)
  {
      return;
   }
  p=partition(data,low,high);
  quicksort(data,p-1-low,low,p-1);
  quicksort(data,high-(p+1),p+1,high);
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
    quicksort(data, row,0,row-1);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
