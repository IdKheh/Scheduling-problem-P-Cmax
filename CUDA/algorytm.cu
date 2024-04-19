#include <iostream>
#include <algorithm>
#include "polaczenie.hpp"

std::vector<int> greedy(std::vector<std::vector<int>> t){ // O(n^2) 
    std::vector<int> result(t[0][0],0); //przypisanie zadań do maszyn
    std::vector<int> times(t[0][1],0); //obciążenie maszyn

    for(int i=1;i<=t[0][0];i++){ //każdemu zadaniu przyznajemy maszynę
        int index = 0;
        for(int j=0;j<t[0][1];j++){ //dodaj przechowywanie czasu oraz
            if(times[index]+t[i][1] > times[j]+t[i][1]) index=j;

            if(t[0][1]-1 == j){
                times[index]+=t[i][1];
                result[i-1]=index+1;
            }
        }
    }
    result.push_back(cMax(times));
    return result;
}

std::vector<int> greedyBroken(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken){
    std::vector<int> result(t[0][0],0); //przypisanie zadań do maszyn
    std::vector<int> times(t[0][1],0); //obciążenie maszyn
    std::vector<int> BrokenMachines(t[0][1],0);

    for(int i=1;i<=t[0][0];i++){ //każdemu zadaniu przyznajemy maszynę
        int index = 0, indexBroken = 0;
        for(int j=0;j<t[0][1];j++){

            if(BrokenMachines[j]) continue;

            if(broken[0][indexBroken]-1 ==j){
                if(times[j]+t[i][1]>=broken[1][indexBroken]){
                    BrokenMachines[j]=1;
                    indexBroken++;
                    continue;
                }
            }

            if(times[index]+t[i][1] > times[j]+t[i][1]) index=j;

            if(t[0][1]-1 == j){
                times[index]+=t[i][1];
                result[i-1]=index+1;
            }
        }
    }
    result.push_back(cMax(times));
    return result;
}