#include <iostream>
#include <vector>
#include <chrono>
#define vector2D std::vector<std::vector<int>>
#define vector1D std::vector<int>
#define MAXNumber 10;
#define MINNumber 0;

void display(vector2D t){
    int n = t.size();
    int m = t[0].size();

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            std::cout<<t[i][j]<<" ";
        std::cout<<std::endl;
    }
}

vector2D generator(int n,int m){
    vector2D t(n,vector1D(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            t[i][j]=std::rand()%MAXNumber + MINNumber;
        }
    }
    return t;
}

vector2D multiplay(vector2D A,vector2D B){
    int n = A.size();
    int p = A[0].size();
    int m = B[0].size();

    vector2D t(n,vector1D(m,0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k) {
                t[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return t;
}

int main(){
    int n=3, m=1;
    std::cout<<"GENERATE DATA\n\n";

    vector2D A=generator(n,m);
    vector2D B=generator(m,n);
    display(A);
    std::cout<<"----------------\n";
    display(B);

    auto start1 = std::chrono::steady_clock::now();
    vector2D C = multiplay(A,B);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time1 = end1 - start1;

    std::cout<<"\nRESULT time: "<<time1.count()*1000<<" ms\n----------------\n";
    display(C);

    return 0;
}
