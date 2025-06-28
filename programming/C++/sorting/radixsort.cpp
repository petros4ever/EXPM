#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>


struct db {
    int num;
    std::string str;
};

int getMaxDigits(std::vector<db>& data) 
{
    int maxNum = data[0].num, digits = 0;
    
    for (size_t i = 1; i < data.size(); i++) 
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

void countingsort(std::vector<db>& data, int exp) 
{
     if (data.empty()) return;
    int max = data[0].num;
    for (const auto& entry : data)
        if (entry.num > max) max = entry.num;
    
    std::vector<db> output(data.size());
    std::vector<int> count(10, 0);
    
    for (const auto& entry : data)
        count[(entry.num / exp) % 10]++;

    
    for (size_t i = 1; i < 10; i++)
        count[i] += count[i - 1];


    for (ssize_t i = data.size() - 1; i >= 0; i--) 
    {
        int digit = (data[i].num / exp) % 10;
        output[count[digit] - 1] = data[i];
        count[digit]--;
    }
     data = std::move(output);
}

void RadixSort(std::vector<db>& data) 
{
    int maxDigits = getMaxDigits(data);
    
    for (int exp = 1, i = 0; i < maxDigits; exp *= 10, ++i)
        countingsort(data, exp);
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
    RadixSort(data);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
    return 0;
}
