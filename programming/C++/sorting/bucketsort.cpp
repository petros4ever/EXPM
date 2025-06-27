#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct db {
    int num;
    std::string str;
};


int findmax(std::vector<db>& data)
{ 
   
   int max=data[0].num;
   for(size_t i=1;i<data.size();i++)
   {
      if(data[i].num>max)
      {
         max=data[i].num;
      }
   }
   return max;
}

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


void bucketsort(std::vector<db>& data,int k)
{
     int max = findmax(data);
    std::vector<std::vector<db>> buckets(k);

    for (const auto& elem : data) 
    {
        int bucketIndex = (k * elem.num) / (max + 1);
        if (bucketIndex >= k) bucketIndex = k - 1;
        buckets[bucketIndex].push_back(elem);
    }

    for (auto& bucket : buckets) 
    {
        if (bucket.size() > 1) 
        {
            quicksort(bucket, 0, bucket.size() - 1);
        }
    }

    data.clear();
    for (const auto& bucket : buckets) 
    {
        for (const auto& elem : bucket) 
       {
            data.push_back(elem);
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
    bucketsort(data, 10);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
        return 0;
}
