#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct db {
    int num;
    std::string str;
};



void countingsort(std::vector<db>& data)
{
     if (data.empty()) return;
    int max = data[0].num;
    for (const auto& entry : data)
        if (entry.num > max) max = entry.num;

    std::vector<int> count(max + 1, 0);
    std::vector<db> output(data.size());

    for (const auto& entry : data)
        count[entry.num]++;

    for (size_t i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = data.size() - 1; i >= 0; i--)
    {
        int key = data[i].num;
        output[count[key] - 1] = data[i];
        count[key]--;
    }

    data = std::move(output);
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
    countingsort(data);
    std::cout<<"sorted data:\n";
   for(const auto& entry:data)
   {
          std::cout << entry.num << " " << entry.str << '\n';
   }
    return 0;
}
