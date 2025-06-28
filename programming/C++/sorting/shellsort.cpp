#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct db{
int num;
std::string str;
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

void shellsort(std::vector<db>& data,int n)
{
    int gaps[10], size;
    generate_gap_sequence(n, gaps, &size);
    for (int g = 0; g < size; g++) 
    {
        int gap = gaps[g];  
        for (int i = gap; i < n; i++) 
        {
            db temp = data[i];  
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
     std::vector<db> data;
    std::ifstream file("sort.txt");
    if (!file) 
    {
        std::cerr<<"error opening file!\n";
        return 1;
    }
    db temp;
    while (file>>temp.num>>temp.str) 
    {
      data.push_back(temp) ;   
    }
    file.close();
    shellsort(data,data.size());
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }

   return 0;
}
