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

int getparent(int element)
{
  if(element==0)
  {
    return -1;
   }
  else
  {
     return floor((element-1)/2);
   }
}

void siftdown(struct db *data,int root,int end)
{
   int child;
   while(2*root+1<end)
   {
      child=2*root+1;
      if(child+1<end && data[child].num<data[child+1].num)
      {
         child=child+1;
      }
     if(data[root].num<data[child].num)
     {
        swap(&data[root],&data[child]);
        root=child;
     }
     else
     {
       return;
     }
    }

}

void heapify(struct db *data,int size)
{
   int start=getparent(size-1);
   while(start>=0)
   {
     siftdown(data,start,size);
     start--;
   }
}

void heapsort(struct db *data,int size)
{ 
   heapify(data,size);
   int end=size;
   while(end>1)
   {
      end=end-1;
      swap(&data[end],&data[0]);
      siftdown(data,0,end);
    }
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
    heapsort(data, row);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
