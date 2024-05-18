#include<vector>

extern std::vector<std::vector<int>> t;

std::vector< std::vector<int>> generator(int n, int m);
std::vector< std::vector<int>> brokenGenerator(int m, int time, int x);
std::vector<int> greedy(std::vector<std::vector<int>> t);
std::vector<int> greedyBroken(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken);
std::vector<int> geneticAlgorithmP(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken,std::vector <int> greedyResult, int n,int pop);
std::vector<int> geneticAlgorithmS(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken,std::vector <int> greedyResult, int n,int pop);

void wypisz(std::vector<std::vector<int>> t);
void wypisz_male(std::vector<int> t);
int cMax(std::vector<int> machines);