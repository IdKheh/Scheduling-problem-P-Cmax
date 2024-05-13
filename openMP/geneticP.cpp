#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include "polaczenie.hpp"
#define MAXPopulation 1000 // how many population we create
#define MINVectorSize 2
#define TheBestCandidats 5
#define MAXCandidats 10
#define vector2D std::vector<std::vector<int>>
#define vector1D std::vector<int>

void checkP(vector1D &child, vector2D broken, vector2D t,int n, int m){
    vector1D brokenMachines(m,0);
    vector1D times(m,0);
    vector1D end(n,0);

    for(int i=0;i<n;i++){
        auto index = std::find(broken[0].begin(),broken[0].end(),child[i]-1);

        if((brokenMachines[child[i]-1]) || 
        (index != broken[0].end() && times[child[i]-1]+t[i+1][1]==broken[1][index - broken[0].begin()])){

        }
        else {
            times[child[i]-1]+=t[i+1][1];
            end[i]++;
        }
    }

    for(int i=0;i<n;i++){
        if(!end[i]){
            int index=0;
            for(int j=0;j<m;j++){
                if(times[index]+t[i+1][1]>times[j]+t[i+1][1]) index = j;

                if(m-1 == j){
                times[index]+=t[i][1];
                child[i]=index+1;
                }
            }
        }
    }
}

vector2D initP(vector2D t,vector1D topResult,vector2D broken){
    int n = t[0][0], m = t[0][1];

    vector2D popTask;
    #pragma omp parallel for
    for(int x=0;x<2*MAXPopulation;x++){
        vector1D child1(n,0);
        vector1D child2(n,0);
        int changeProcess1 = std::rand()%(n);
        int changeProcess2 = std::rand()%(n);
        int changeMachine1 = std::rand()%m+1;
        int changeMachine2 = std::rand()%m+1;

        child1 = topResult;
        child1[changeProcess1] = changeMachine1;

        child2 = topResult;
        child2[changeProcess2] = changeMachine2;

        checkP(child1,broken,t,n,m);
        checkP(child2,broken,t,n,m);
        #pragma omp critical
        {
            popTask.push_back(child1);
            popTask.push_back(child2);
        }
    }
    popTask.push_back(topResult);
    return popTask;
}

vector2D crossbreedingP(vector2D t,vector2D topResult,vector2D broken){
    int n = t[0][0], m = t[0][1];

    vector2D popTask;

    #pragma omp parallel for
    for(int x=0;x<MAXPopulation;x++){
        vector1D child1(n+1,0);
        vector1D child2(n+1,0);
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

        checkP(child1,broken,t,n,m);
        checkP(child2,broken,t,n,m);

        #pragma omp critical
        {
            popTask.push_back(child1);
            popTask.push_back(child2);
            popTask.push_back(topResult[setTask1]);
            popTask.push_back(topResult[setTask2]);
        }
    }
    return popTask;
}

void mutationP(int n, int m, vector2D &tasks,vector2D broken, vector2D t)
{
    int sizePop = tasks.size();
    int x=std::rand()%sizePop; //losujemy liczbe permutacji do zmutowania

    #pragma omp parallel for
    for(int i=0;i<x;i++){
        int taskSet = std::rand()%sizePop;  //ryzyko wylosowania dwa razy tego samego wektora
        int indexTask = std::rand()%n;
        int indexMachine = std::rand()%m+1;

        tasks[taskSet][indexTask]=indexMachine;

        checkP(tasks[taskSet],broken,t,n,m);       
    }
}

vector2D populationP(vector2D t, vector2D &tasks){
    int sizePop = tasks.size(), n=t[0][0], m=t[0][1];
    vector2D result(10, vector1D(n+1,0));
    vector1D BrokenMachines(t[0][1],0);
    vector1D thebest(TheBestCandidats,-1);
    
    #pragma omp parallel for
    for(int i=0;i<sizePop;i++){// obliczam cmax
        vector1D machines(m,0);
        for(int j=0;j<m;j++)
            machines[j]=0;

        for(int j=0;j<n;j++)           
            machines[tasks[i][j]-1]+=t[j+1][1];
        tasks[i][n]=cMax(machines);
    }

    for(int x=0;x<TheBestCandidats;x++){
        int max=0, index=0;
        for(int i=0;i<sizePop;i++){
            if(max==0){
                max = tasks[i][n];
                index = i;
            }
            else if(max>tasks[i][n] && (thebest.end() == std::find(thebest.begin(), thebest.end(), index))){
                max = tasks[i][n];
                index = i;
            }
        }
        thebest[x]=index;
    }

    for(int i=0;i<MAXCandidats;i++){ //wybieramy 5 najlepszych i 5 losowych kandydatów
        if(i<TheBestCandidats)
            for(int j=0;j<n+1;j++)
                result[i][j]=tasks[thebest[i]][j];
        else{
            int x=std::rand()%sizePop;
            for(int j=0;j<n+1;j++)
                result[i][j]=tasks[x][j];
        }
    }

    return result;
}

vector1D geneticAlgorithmP(vector2D t,vector2D broken,vector1D greedyResult, int n){// calosc O(n^2*i) n = 30 - populacja, i - ilosc iteracji
    vector1D result(t[0][0]+1,0);
    vector2D popTask;
    result = greedyResult;
    for(int i=0;i<n;i++){

        if(i==0) popTask = initP(t,greedyResult,broken); // generowanie populacji = O(m+n) (m=1000)
        else popTask = crossbreedingP(t,popTask,broken); // O(m+n^2)

        mutationP(t[0][0],t[0][1],popTask,broken,t); // O(x), x - ilosc mutacji
        popTask=populationP(t,popTask); // wybieramy 5 najlepszych i 5 losowych O(n^2)

        if(result[t[0][0]>popTask[0][t[0][0]]]){
            result = popTask[0];
        }
    }

    return result;
}

// g++ main.cpp algorytm.cpp generator.cpp genetic.cpp functions.cpp -o main

//gcc -o hello -fopenmp hello.c

//g++ -o main -fopenmp main.cpp algorytm.cpp generator.cpp genetic.cpp functions.cpp