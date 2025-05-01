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

void bubblesort(struct db *data,int size)
{
    int i,j;
    for (int i = 0; i < size - 1; i++) 
    { 
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (data[j].num > data[j + 1].num) 
                {
                swap(&data[j], &data[j + 1]);
            }
        }
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
   bubblesort(data,row);
   printf("Sorted data:\n");
   for(i=0;i<row;i++)
   {
      printf("%d %s\n",data[i].num,data[i].string);
   }
   return 0;
}
