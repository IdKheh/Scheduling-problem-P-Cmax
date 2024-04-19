#include <iostream>
#include <vector>
#include "polaczenie.hpp"

//zadania będą duplikowane jeśli maszyna padnie
//możliwe będzie w sumie również, że niektóre zadania będą mogły wykonywać się krócej na niektórych zadaniach


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    std::cout<<"GENERATE DATA\n";
    std::vector<std::vector<int>> t= generator();

    wypisz(t);

    std::cout<<"GREEDY ALGORITHM\n";
    std::vector<int> resultGreedy = greedy(t);
    std::cout<<"Greedy Cmax: "<<resultGreedy[t[0][0]]<<std::endl;
    //wypisz_male(resultGreedy);
    
    std::cout<<"GENETIC ALGORITHM\n";
    std::vector<int> resultGenetic = geneticAlgorithm(t,resultGreedy, 1000);
    std::cout<<"Genetic Cmax: "<<resultGenetic[t[0][0]]<<std::endl;
    //wypisz_male(resultGenetic);

    return 0;
}
