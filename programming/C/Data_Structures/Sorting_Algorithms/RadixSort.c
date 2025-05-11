#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR 50
#define MAX 100

struct db {
    int num;
    char string[STR];
};

int getMaxDigits(struct db *data, int size) {
    int maxNum = data[0].num, digits = 0;
    
    for (int i = 1; i < size; i++) 
    {
        if (data[i].num > maxNum)
            maxNum = data[i].num;     
    }
    
    while (maxNum > 0) 
    {
        maxNum /= 10;
        digits++;
    }
    
    return digits; 
}

void countingsort(struct db *data, int size, int exp) {
    int count[10] = {0}, i;
    struct db output[size];
    for (i = 0; i < size; i++)
        count[(data[i].num / exp) % 10]++;

    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];


    for (i = size - 1; i >= 0; i--) 
    {
        int digit = (data[i].num / exp) % 10;
        output[count[digit] - 1] = data[i];
        count[digit]--;
    }
    for (i = 0; i < size; i++)
        data[i] = output[i];
}

void RadixSort(struct db *data, int size) 
{
    int maxDigits = getMaxDigits(data, size);
    
    for (int exp = 1; maxDigits / exp > 0; exp *= 10)
        countingsort(data, size, exp);
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
    RadixSort(data, row);
    printf("Sorted data:\n");
    for (i = 0; i < row; i++) 
    {
        printf("%d %s\n", data[i].num, data[i].string);
    }
    return 0;
}
