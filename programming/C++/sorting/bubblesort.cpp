#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct db{
int num;
std::string str;
}; 


void bubblesort(std::vector<db>& data)
{
    for (size_t i = 0; i < data.size() - 1; i++) 
    { 
        for (size_t j = 0; j < data.size() - i - 1; j++) 
        {
            if (data[j].num > data[j + 1].num) 
                {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

int main()
{
   std::vector<db> data;
   std::ifstream file("sort.txt");
   if(!file)
   {
      std::cerr<<"error opening file!\n";
      return 1;
   }
   else
   {   
      db temp;
      while(file>>temp.num>>temp.str)
      {
          data.push_back(temp) ;     
      }
   }
   file.close();
   bubblesort(data);
   std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
   return 0;
}
