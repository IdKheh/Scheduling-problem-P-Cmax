#include <iostream>
#include <vector>
#include <algorithm>
#include "polaczenie.hpp"
#define MAXPopulation 1000 // how many population we create
#define MINVectorSize 2
#define TheBestCandidats 5
#define MAXCandidats 10

std::vector<std::vector<int>> init(std::vector<std::vector<int>>t,std::vector<int> topResult){
    int n = t[0][0], m = t[0][1];

    std::vector<std::vector<int>> popTask;
    std::vector<int> child1(n,0);
    std::vector<int> child2(n,0);

    for(int x=0;x<10;x++){
        int changeProcess1 = std::rand()%(n);
        int changeProcess2 = std::rand()%(n);
        int changeMachine1 = std::rand()%m+1;
        int changeMachine2 = std::rand()%m+1;

        child1 = topResult;
        child1[changeProcess1] = changeMachine1;

        child2 = topResult;
        child2[changeProcess2] = changeMachine2;

        popTask.push_back(child1);
        popTask.push_back(child2);
    }
    popTask.push_back(topResult);
    child1.clear();
    child2.clear();
    return popTask;
}

std::vector<std::vector<int>> crossbreeding(std::vector<std::vector<int>>t,std::vector<std::vector<int>> topResult){
    int n = t[0][0], m = t[0][1];

    std::vector<std::vector<int>> popTask;
    std::vector<int> child1(n+1,0);
    std::vector<int> child2(n+1,0);


    for(int x=0;x<MAXPopulation;x++){
        int setTask1 = std::rand()%MAXCandidats;
        int setTask2 = std::rand()%MAXCandidats;
        int joinVectors = std::rand()%(n-MINVectorSize);
        int changeProcess1 = std::rand()%(n-MINVectorSize); //dzielimy nasz najlepszy wynik na dwa wektory
        int changeProcess2 = n - changeProcess1;
        int changeMachine1 = std::rand()%m+1;
        int changeMachine2 = std::rand()%m+1;

        for(int i=0;i<n;i++){
            if(i<x){
                child1[i] = topResult[setTask1][i];
                child2[i] = topResult[setTask2][i];
            }
            else{
                child1[i] = topResult[setTask2][i];
                child2[i] = topResult[setTask1][i];
            }
        }
        child1[changeProcess1] = changeMachine1;
        child2[changeProcess2] = changeMachine2;

        popTask.push_back(child1);
        popTask.push_back(child2);
        popTask.push_back(topResult[setTask1]);
        popTask.push_back(topResult[setTask2]);
    }
    child1.clear();
    child2.clear();
    return popTask;
}

void mutation(int n, int m, std::vector<std::vector<int>> &tasks)
{
    int sizePop = tasks.size();
    int x=std::rand()%sizePop; //losujemy liczbe permutacji do zmutowania

    for(int i=0;i<x;i++){
        int taskSet = std::rand()%sizePop;
        int indexTask = std::rand()%n;
        int indexMachine = std::rand()%m+1;

        tasks[taskSet][indexTask]=indexMachine;       
    }
}

std::vector<std::vector<int>> population(std::vector<std::vector<int>> t, std::vector<std::vector<int>> &tasks){
    int sizePop = tasks.size(), n=t[0][0], m=t[0][1];
    std::vector<int> machines(m,0); // wybor cmax
    std::vector<std::vector<int>> result(10, std::vector<int>(n+1,0));
      
    for(int i=0;i<sizePop;i++){// obliczam cmax
        for(int j=0;j<m;j++)
            machines[j]=0;

        for(int j=0;j<n;j++)
            machines[tasks[i][j]-1]+=t[j+1][1];
        tasks[i][n]=cMax(machines);
    }
    std::sort(tasks.begin(), tasks.end(),[](const std::vector<int>& a, const std::vector<int>& b) {return a[a.size()-1] < b[b.size()-1];});

    for(int i=0;i<MAXCandidats;i++){ //wybieramy 5 najlepszych i 5 losowych kandydatów
        if(i<TheBestCandidats)
            for(int j=0;j<n+1;j++)
                result[i][j]=tasks[i][j];
        else{
            int x=std::rand()%sizePop;
            for(int j=0;j<n+1;j++)
                result[i][j]=tasks[x][j];
        }

    }

    return result;
}

std::vector<int> geneticAlgorithm(std::vector<std::vector<int>> t,std::vector <int> greedyResult, int n){// calosc O(n^2*i) n = 30 - populacja, i - ilosc iteracji
    std::vector <int> result(t[0][0]+1,0);
    std::vector<std::vector<int>> popTask;
    result = greedyResult;
    for(int i=0;i<n;i++){

        if(i==0) popTask = init(t,greedyResult); // generowanie populacji = O(m+n) (m=1000)
        else popTask = crossbreeding(t,popTask); // O(m+n^2)

        mutation(t[0][0],t[0][1],popTask); // O(x), x - ilosc mutacji
        popTask=population(t,popTask); // wybieramy 5 najlepszych i 5 losowych O(n^2)

        if(result[t[0][0]>popTask[0][n]]){
            result = popTask[0];
        }
    }

    return result;
}