#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR 50
#define MAX 100

struct db {
    int num;
    char string[STR];
};



void countingsort(struct db *data,int size)
{
  int count[MAX]={0},i,j;
  struct db output[size];
  for(i=0;i<size;i++)
  {
     j=data[i].num;
     count[j]=count[j]+1;
  }
  for(i=1;i<MAX;i++)
   {
      count[i]=count[i]+count[i-1];
   }
   for(i=size-1;i>=0;i--)
   {
      j=data[i].num;
      output[count[j]-1]=data[i];
      count[j]--;
   }
   for (i = 0; i < size; i++) {
        data[i] = output[i]; 
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
    countingsort(data, row);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
