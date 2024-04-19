#include "polaczenie.hpp"
#include <iostream>
#include <cstdlib>

#define MAXMachine 60
#define MAXProcess 1000
#define MAXTime 100
#define MIN 1

std::vector< std::vector<int>> generator() // losuje n - procesow, m - maszyn, niektore procesy moga byc przydzielone do pewnych maszyn
{
    int n= (std::rand() % MAXProcess)+MIN;
    int m= (std::rand() % MAXMachine)+MIN;
    std::vector<std::vector<int>> t(n+1,std::vector<int>(2,0));
    t[0][0] = n;
    t[0][1] = m;
    
    for(int i=1;i<=n;i++){
        t[i][0] = i;
        t[i][1] = (std::rand() % MAXTime)+MIN;
    }

    return t;
}