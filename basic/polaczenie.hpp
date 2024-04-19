#include<vector>

extern std::vector<std::vector<int>> t;

std::vector< std::vector<int>> generator();
std::vector<int> greedy(std::vector<std::vector<int>> t);
std::vector<int> geneticAlgorithm(std::vector<std::vector<int>> t,std::vector <int> greedyResult, int n);

void wypisz(std::vector<std::vector<int>> t);
void wypisz_male(std::vector<int> t);
int cMax(std::vector<int> machines);
/*
void bruteForce(std::vector<std::vector<int>> &t);
void geneticAlgorithm(std::vector<std::vector<int>> t);*/