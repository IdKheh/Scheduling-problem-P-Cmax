#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "polaczenie.hpp"

void wypisz(std::vector< std::vector<int>> t)
{
    int n=t.size();

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<t[i].size();j++)
            std::cout<<t[i][j]<<" ";
        std::cout<<"\n";
    }
}
void wypisz_male(std::vector<int> t)
{
    int n=t.size();
    for(int i=0;i<n;i++)
        std::cout<<t[i]<<" ";
    
    std::cout<<"\n";
}
int cMax(std::vector<int> machines)
{
    int cmax=0;
    for(int i=0;i<machines.size();i++)
        cmax=std::max(cmax,machines[i]);
    return cmax;
}
