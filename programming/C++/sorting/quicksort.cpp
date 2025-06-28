#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct db {
    int num;
    std::string str;
};


int partition(std::vector<db>& data,int low,int high)
{
   int pivot;
   pivot=data[high].num;
   int i=low;
   int j;
   for(j=low;j<high;j++)
   {
      if(data[j].num<=pivot)
      {
          std::swap(data[j],data[i]);
          i=i+1;
       }
    }
    std::swap(data[i],data[high]);
    return i;
}

void quicksort(std::vector<db>& data,int low,int high)
{
 int p;
 if(low>=high || low<0)
  {
      return;
   }
  p=partition(data,low,high);
  quicksort(data,low,p-1);
  quicksort(data,p+1,high);
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
    quicksort(data,0,data.size()-1);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }

        return 0;
}
