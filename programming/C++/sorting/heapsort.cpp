#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


struct db {
    int num;
    std::string str;
};


int getparent(int element)
{
  if(element==0)
  {
    return -1;
   }
  else
  {
     return floor((element-1)/2);
   }
}

void siftdown(std::vector<db>& data,int root,int end)
{
   int child;
   while(2*root+1<end)
   {
      child=2*root+1;
      if(child+1<end && data[child].num<data[child+1].num)
      {
         child=child+1;
      }
     if(data[root].num<data[child].num)
     {
        std::swap(data[root],data[child]);
        root=child;
     }
     else
     {
       return;
     }
    }

}

void heapify(std::vector<db>& data)
{
   int start=getparent(data.size()-1);
   while(start>=0)
   {
     siftdown(data,start,data.size());
     start--;
   }
}

void heapsort(std::vector<db>& data)
{ 
   heapify(data);
   int end=data.size();
   while(end>1)
   {
      end=end-1;
      std::swap(data[end],data[0]);
      siftdown(data,0,end);
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
    heapsort(data);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
    return 0;
}
