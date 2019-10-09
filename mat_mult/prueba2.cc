// CPP Program to multiply two matrix using pthreads 
#include <bits/stdc++.h> 
#include <iostream>
#include "matrix.hh"
#include "timer.hh"

using namespace std; 
  
// maximum size of matrix 
#define MAX 4 
  
// maximum number of threads 
#define MAX_THREAD 4 

const int tam=4;
  
Matrix matA(tam,tam);
Matrix matB(tam,tam);
Matrix matC(tam,tam);

int step_i = 0; 

struct matrices{
  Matrix a;
  Matrix b;
  Matrix r;
};


void* mat_mult(void *input){
  //((struct args*)input)->age)
  int core = step_i++; 
  int N=((struct matrices*)input)->a.numRows();
  int M=((struct matrices*)input)->b.numCols();


}

void* mat_mult2(void *input){
  //((struct args*)input)->age)
  int core = step_i++; 
  int N=((struct matrices*)input)->a.numRows();
  int M=((struct matrices*)input)->b.numCols();
  
  for (size_t r = 0; r < N; r++){
    for (size_t c = 0; c < M; c++){
      double res=0;
      for (size_t nc = 0; nc < M; nc++)
        res += matA.at(r, nc) * matB.at(nc, c);
      matC.edit(r,c,res);
    }
  }
  //((struct matrices*)input)->r=e;
}

  
// Driver Code 
int main() 
{ 
  cout<<"Multiplicacion de matrices...\n";
  //cout<<"# hilos: "<<nthreads<<endl;

  //int tam=10;

  Matrix a(tam,tam);
  Matrix b(tam,tam);
  Matrix c(tam,tam);
  Matrix d(tam,tam);

  a.fill2();
  b.fill2();

  struct matrices *Mats = (struct matrices *)malloc(sizeof(struct matrices));
  Mats->a=a;
  Mats->b=b;
  Mats->r=c;

  matA=a;
  matB=b;
  matC=c;


  
  // declaring four threads 
  pthread_t threads[MAX_THREAD]; 

  // Creating four threads, each evaluating its own part 
  for (int i = 0; i < MAX_THREAD; i++) { 
      int* p; 
      pthread_create(&threads[i], NULL, mat_mult2, (void *) Mats); 
  } 

  //c.print();

  // joining and waiting for all threads to complete 
  for (int i = 0; i < MAX_THREAD; i++)  
      pthread_join(threads[i], NULL);     

  matC.print();

  return 0; 
} 