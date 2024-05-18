#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "polaczenie.hpp"

//zadania będą duplikowane jeśli maszyna padnie
//możliwe będzie w sumie również, że niektóre zadania będą mogły wykonywać się krócej na niektórych maszynach

int main(int argc, char const *argv[])
{
    int n=100, m=20, x=5,l=100,pop=1000;
    double times[10][10][11];
    for(int i=0;i<1;i++){
        for(int j=0;j<1;j++){
            srand(time(NULL));
            std::cout<<"GENERATE DATA\n";
            std::vector<std::vector<int>> t= generator(n,m);
            
            //wypisz(t);

            std::cout<<"GREEDY ALGORITHM\n";
            std::vector<int> resultGreedy = greedy(t);
            //wypisz_male(resultGreedy);

            std::vector<std::vector<int>> broken = brokenGenerator(t[0][1],resultGreedy[t[0][0]],x);

            //wypisz(broken);

            std::cout<<"Greedy Broken ALGORITHM\n";
            auto start = std::chrono::steady_clock::now();
            std::vector<int> resultGreedyBroken = greedyBroken(t,broken);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> time = end - start;
            std::cout<<"Genetic Cmax: "<<resultGreedyBroken[t[0][0]]<<" time: "<<time.count()<<" s"<<std::endl;
            
            std::cout<<"GENETIC ALGORITHM P\n";
            auto start1 = std::chrono::steady_clock::now();
            std::vector<int> resultGeneticP = geneticAlgorithmP(t,broken,resultGreedyBroken, l,pop);
            auto end1 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time1 = end1 - start1;

            std::cout<<"Genetic Cmax: "<<resultGeneticP[t[0][0]]<<" time: "<<time1.count()<<" s"<<std::endl;
            //wypisz_male(resultGeneticP);


            std::cout<<"GENETIC ALGORITHM S\n";
            auto start2 = std::chrono::steady_clock::now();
            std::vector<int> resultGeneticS = geneticAlgorithmS(t,broken,resultGreedyBroken, l,pop);
            auto end2= std::chrono::steady_clock::now();
            std::chrono::duration<double> time2 = end2 - start2;

            std::cout<<"Genetic Cmax: "<<resultGeneticS[t[0][0]]<<" time: "<<time2.count()<<" s"<<std::endl;
            //wypisz_male(resultGeneticS);
            times[i][j][0]=n;
            times[i][j][1]=m;
            times[i][j][2]=x;
            times[i][j][3]=l;
            times[i][j][4]=pop;
            times[i][j][5]=time.count(); //greedy
            times[i][j][6]=time1.count();
            times[i][j][7]=time2.count();
            times[i][j][8]=resultGreedy[t[0][0]];
            times[i][j][9]=resultGeneticP[t[0][0]];
            times[i][j][10]=resultGeneticS[t[0][0]];
        }
        n+=100;
        m+=20;
        x+=5;
        l+=10;
        pop+=500;
    }
     // Save the times array to a file
    std::ofstream outFile("times.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (int k = 0; k < 11; ++k) {
                    outFile << times[i][j][k] << " ";
                }
                outFile << std::endl;
            }
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing\n";
    }
    return 0;
}
    /*
    srand(time(NULL));
    std::cout<<"GENERATE DATA\n";
    std::vector<std::vector<int>> t= generator(n,m);
    
    wypisz(t);

    std::cout<<"GREEDY ALGORITHM\n";
    std::vector<int> resultGreedy = greedy(t);
    std::cout<<"Greedy Cmax: "<<resultGreedy[t[0][0]]<<std::endl;
    wypisz_male(resultGreedy);

    std::vector<std::vector<int>> broken = brokenGenerator(t[0][1],resultGreedy[t[0][0]],x);

    wypisz(broken);

    std::cout<<"Greedy Broken ALGORITHM\n";
    std::vector<int> resultGreedyBroken = greedyBroken(t,broken);
    std::cout<<"Greedy Broken Cmax: "<<resultGreedyBroken[t[0][0]]<<std::endl;
    wypisz_male(resultGreedyBroken);
    
    std::cout<<"GENETIC ALGORITHM\n";
    auto start1 = std::chrono::steady_clock::now();
    std::vector<int> resultGeneticP = geneticAlgorithmP(t,broken,resultGreedyBroken, 100);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time1 = end1 - start1;

    std::cout<<"Genetic Cmax: "<<resultGeneticP[t[0][0]]<<" time: "<<time1.count()<<" s"<<std::endl;
    wypisz_male(resultGeneticP);


    std::cout<<"GENETIC ALGORITHM\n";
    auto start2 = std::chrono::steady_clock::now();
    std::vector<int> resultGeneticS = geneticAlgorithmS(t,broken,resultGreedyBroken, 100);
    auto end2= std::chrono::steady_clock::now();
    std::chrono::duration<double> time2 = end2 - start2;

    std::cout<<"Genetic Cmax: "<<resultGeneticS[t[0][0]]<<" time: "<<time2.count()<<" s"<<std::endl;
    wypisz_male(resultGeneticS);

    return 0;
}*/
