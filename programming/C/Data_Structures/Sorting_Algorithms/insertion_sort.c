#include <stdio.h>

#define STR 50
#define MAX 100

struct db{
int num;
char string[STR];
}; 


void insertionsort(struct db *data,int size)
{
    int i;
    for(int i=1;i<size;i++)
    {
        int reverse_counter=i-1;
        struct db key=data[i];
        while(reverse_counter>=0 && data[reverse_counter].num>key.num)
     { 
        data[reverse_counter+1]=data[reverse_counter];
        reverse_counter-=1;
      }
     data[reverse_counter+1]=key;
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
   insertionsort(data,row);
   printf("Sorted data:\n");
   for(i=0;i<row;i++)
   {
      printf("%d %s\n",data[i].num,data[i].string);
   }
   return 0;
}
