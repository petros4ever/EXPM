#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct db{
int num;
std::string str;
}; 



void selectionsort(std::vector<db>& data)
{
     for (size_t i = 0; i < data.size() - 1; i++) {
        int minIndex = i;
        for (size_t j = i + 1; j < data.size(); j++) {
            if (data[j].num < data[minIndex].num) {
                minIndex = j;
            }
        }
        std::swap(data[i], data[minIndex]);
    }
}

int main(void)
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
          data.push_back(temp);
      }
   }
   file.close();
   selectionsort(data);
   std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
        std::cout << entry.num << " " << entry.str << '\n';
         }
   return 0;
}
