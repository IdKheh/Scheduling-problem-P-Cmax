#include <iostream>
#include <vector>
#include "polaczenie.hpp"

//zadania będą duplikowane jeśli maszyna padnie
//możliwe będzie w sumie również, że niektóre zadania będą mogły wykonywać się krócej na niektórych maszynach

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    std::cout<<"GENERATE DATA\n";
    //std::vector<std::vector<int>> t= generator();

    std::vector<std::vector<int>> t(5+1,std::vector<int>(2,0));
    std::vector<std::vector<int>> broken(2,std::vector<int>(1,0));

    t[0][0]=5; t[0][1]=3;
    t[1][0]=1; t[1][1]=10;
    t[2][0]=2; t[2][1]=12;
    t[3][0]=3; t[3][1]=15;
    t[4][0]=4; t[4][1]=25;
    t[5][0]=5; t[5][1]=13;

    broken[0][0]=2; broken[1][0] = 13;
    
    wypisz(t);

    std::cout<<"GREEDY ALGORITHM\n";
    std::vector<int> resultGreedy = greedy(t);
    std::cout<<"Greedy Cmax: "<<resultGreedy[t[0][0]]<<std::endl;
    wypisz_male(resultGreedy);

    //std::vector<std::vector<int>> broken = brokenGenerator(t[0][1],resultGreedy[t[0][0]]);

    wypisz(broken);

    std::cout<<"Greedy Broken ALGORITHM\n";
    std::vector<int> resultGreedyBroken = greedyBroken(t,broken);
    std::cout<<"Greedy Broken Cmax: "<<resultGreedyBroken[t[0][0]]<<std::endl;
    wypisz_male(resultGreedyBroken);
    
    std::cout<<"GENETIC ALGORITHM\n";
    std::vector<int> resultGenetic = geneticAlgorithm(t,broken,resultGreedyBroken, 100);
    std::cout<<"Genetic Cmax: "<<resultGenetic[t[0][0]]<<std::endl;
    wypisz_male(resultGenetic);

    return 0;
}
