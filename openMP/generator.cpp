#include "polaczenie.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

#define MAXMachine 50
#define MAXProcess 1000
#define MAXTime 100
#define MINMachines 2
#define MIN 1

std::vector< std::vector<int>> generator(int n, int m) // losuje n - procesow, m - maszyn, niektore procesy moga byc przydzielone do pewnych maszyn
{
    //int n= (std::rand() % MAXProcess)+MIN;
    //int m= (std::rand() % MAXMachine)+MINMachines;
    std::vector<std::vector<int>> t(n+1,std::vector<int>(2,0));
    t[0][0] = n;
    t[0][1] = m;
    
    for(int i=1;i<=n;i++){
        t[i][0] = i;
        t[i][1] = (std::rand() % MAXTime)+MIN;
    }

    return t;
}

std::vector< std::vector<int>> brokenGenerator(int m, int time, int x){
    //int x = (std::rand() % (m-MIN))+MIN;  //how many machines will broke, but not all
    std::vector<std::vector<int>> broken(2,std::vector<int>(x,0));

    for(int i=0;i<x;i++){
        broken[0][i] = (std::rand() % m)+MIN;
        broken[1][i] = (std::rand() % time)+MIN;
    }
    sort(broken[1].begin(), broken[1].end()); 
    
    return broken;
}