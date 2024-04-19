#include<vector>

extern std::vector<std::vector<int>> t;

std::vector< std::vector<int>> generator();
std::vector< std::vector<int>> brokenGenerator(int m, int time);
std::vector<int> greedy(std::vector<std::vector<int>> t);
std::vector<int> greedyBroken(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken);
std::vector<int> geneticAlgorithm(std::vector<std::vector<int>> t,std::vector<std::vector<int>> broken,std::vector <int> greedyResult, int n);

void wypisz(std::vector<std::vector<int>> t);
void wypisz_male(std::vector<int> t);
int cMax(std::vector<int> machines);