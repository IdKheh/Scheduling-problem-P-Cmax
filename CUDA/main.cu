#include <iostream>
#include <vector>
#include <chrono>
#define vector2D std::vector<std::vector<int>>
#define vector1D std::vector<int>
#define MAXNumber 10
#define MINNumber 0

__global__ void multiplication(int *A, int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int tmpSum = 0;
    if (row< n && col < n) {
        for (int i = 0; i < n; i++) {
            tmpSum += A[row * n + i] * B[i * n + col];
        }
    }
    C[row * n + col] = tmpSum;
}
void translate(vector2D T,vector1D &arrayT,int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            arrayT[i*n+j]=T[i][j];

}
void display(vector2D t){
    int n = t.size();
    int m = t[0].size();

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            std::cout<<t[i][j]<<" ";
        std::cout<<std::endl;
    }
}
void display(vector1D t){
    int n = t.size();
    for(int i=0;i<n;i++){
        std::cout<<t[i]<<" ";
    }
    std::cout<<std::endl;
}

void multiplyCUDA(vector2D &A, vector2D &B,vector2D &C, int n) {
    int size = n*n;
    vector1D arrayA(size,0);
    vector1D arrayB(size,0);
    vector1D arrayC(size,0);

    translate(A,arrayA,n); // przepisanie danych z wektora wektów to pojedyńczego wektora
    translate(B,arrayB,n);
    translate(C,arrayC,n);
    display(arrayA);
    display(arrayB);
    display(arrayC);
    
    size_t sizeT = size * sizeof(int); 
    int *d_A,*d_B,*d_C;
    int *res = (int*)malloc(sizeT);

    cudaMalloc(&d_A, sizeT);       //alokowanie pamięci na kacie graficznej
    cudaMalloc(&d_B, sizeT);
    cudaMalloc(&d_C, sizeT);

    cudaMemcpy(d_A, arrayA.data(), sizeT, cudaMemcpyHostToDevice);     // kopiowanie pamięci z RAM do karty
    cudaMemcpy(d_B, arrayB.data(), sizeT, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, arrayC.data(), sizeT, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(n, n);
    dim3 numBlocks((n + threadsPerBlock.x - 1) / threadsPerBlock.x, (n + threadsPerBlock.y - 1) / threadsPerBlock.y);
    if (size > 512){
        threadsPerBlock.x = 512;
        threadsPerBlock.y = 512;
        numBlocks.x = ceil(double(n)/double(threadsPerBlock.x));
        numBlocks.y = ceil(double(n)/double(threadsPerBlock.y));
    }

    multiplication<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, n);
    //cudaDeviceSynchronize();
    cudaMemcpy(res, d_C, size * sizeof(int), cudaMemcpyDeviceToHost);  //na odwrót

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = res[i * n + j];
        }
    }

    free(res);
}

vector2D generator(int n){
    vector2D t(n,vector1D(n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            t[i][j]=std::rand()%MAXNumber + MINNumber;
        }
    }
    return t;
}

vector2D multiply(vector2D A,vector2D B){
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
    int n=22;
    std::cout<<"GENERATE DATA\n\n";

    vector2D A=generator(n);
    vector2D B=generator(n);
    vector2D C2(n,vector1D(n,0));
    display(A);
    std::cout<<"----------------\n";
    display(B);

    auto start1 = std::chrono::steady_clock::now();
    vector2D C1 = multiply(A,B);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time1 = end1 - start1;

    std::cout<<"\nRESULT SEQUENCY time: "<<time1.count()*1000<<" ms\n----------------\n";
    display(C1);

    auto start2 = std::chrono::steady_clock::now();
    multiplyCUDA(A,B,C2,n);
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time2 = end2 - start2;

    std::cout<<"\nRESULT CUDA time: "<<time2.count()*1000<<" ms\n----------------\n";
    display(C2);

    A.clear();
    B.clear();
    C1.clear();
    C2.clear();

    return 0;
}
