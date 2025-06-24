#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct db{
int num;
std::string str;
}; 


void insertionsort(std::vector<db>& data)
{
    for(size_t i=1;i<data.size();i++)
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
   insertionsort(data);
   std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
   return 0;
}
