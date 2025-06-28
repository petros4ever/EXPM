#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct db {
    int num;
    std::string str;
};


void merge(std::vector<db>& data,std::vector<db>& left,std::vector<db>& right) 
{
    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) 
    {
        if (left[i].num <= right[j].num) 
        {
            data[k++] = left[i++];
        } 
        else 
        {
            data[k++] = right[j++];
        }
    }
    while (i < left.size()) 
    {
        data[k++] = left[i++];
    }

    while (j < right.size()) 
    {
        data[k++] = right[j++];
    }
}


void mergesort(std::vector<db>& data) 
{
    if (data.size() <= 1) return;

    int mid = data.size() / 2;
     std::vector<db> left(mid), right(data.size() - mid);

    
    for (size_t i = 0; i < mid; i++)
        left[i] = data[i];

    for (size_t i = mid; i < data.size(); i++)
        right[i - mid] = data[i];

    mergesort(left);
    mergesort(right);
    merge(data, left, right);
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
    mergesort(data);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
        return 0;
}
