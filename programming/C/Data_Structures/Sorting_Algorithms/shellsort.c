#include <stdio.h>

#define STR 50
#define MAX 100

struct db{
int num;
char string[STR];
}; 


void generate_gap_sequence(int n, int gaps[], int *size) 
{
    int k = 1;
    while ((3 * k + 1) < n) 
   {         
       k = 3 * k + 1;
    }

    *size = 0;
    while (k > 0) 
    {
        gaps[(*size)++] = k;
        k /= 3; 
    }
}

void shellsort(struct db *data,int n)
{
    int gaps[10], size;
    generate_gap_sequence(n, gaps, &size);
    for (int g = 0; g < size; g++) 
    {
        int gap = gaps[g];  
        for (int i = gap; i < n; i++) 
        {
            struct db temp = data[i];  
            int j = i;
            while (j >= gap && data[j - gap].num > temp.num) 
            {
                data[j] = data[j - gap];  
                j -= gap;
            }
            data[j] = temp;  
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
   shellsort(data,row);
   printf("Sorted data:\n");
   for(i=0;i<row;i++)
   {
      printf("%d %s\n",data[i].num,data[i].string);
   }
   return 0;
}
