#include <stdio.h>

#define STR 50
#define MAX 100

struct db{
int num;
char string[STR];
}; 

void swap(struct db *db1,struct db *db2)
{
   struct db temp=*db2;
   *db2=*db1;
   *db1=temp;
}

void selectionsort(struct db *data,int size)
{
     for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (data[j].num < data[minIndex].num) {
                minIndex = j;
            }
        }
        swap(&data[i], &data[minIndex]);
    }
}

int main(void)
{
   FILE *f;
   int row=0,i;
   struct db data[MAX];
   f=fopen("sort.txt","r");
   if(f==NULL)
   {
      printf("Error opening file!\n");
      return 1;
   }
   else
   {
      while(fscanf(f,"%d %s",&data[row].num,data[row].string) !=EOF)
      {
          row+=1;
      }
   }
   fclose(f);
   selectionsort(data,row);
   printf("Sorted data:\n");
   for(i=0;i<row;i++)
   {
      printf("%d %s\n",data[i].num,data[i].string);
   }
   return 0;
}
