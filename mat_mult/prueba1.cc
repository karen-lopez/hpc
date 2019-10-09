//prueba1.cc
/*
compile line:
g++ -std=c++11 -pthread prueba1.cc -o main.out
./main.out<entradas>salida
run line:
./main.out

///references
https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/parallel/amp/walkthrough-matrix-multiplication.md
*/
#include <thread>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include "matrix.hh"
#include "timer.hh"

using namespace std;

//unsigned int nthreads = std::thread::hardware_concurrency();
unsigned int nthreads = 4;
int tam=1000;
int step_i = 0;

Matrix matA(tam,tam);
Matrix matB(tam,tam);
Matrix matC(tam,tam);
Matrix matD(tam,tam);

void write(string name,string text) {
	ofstream myfile;
	myfile.open(name);
	myfile <<text<< "\n";
	myfile.close();
}

struct matrices{
  Matrix a;
  Matrix b;
  Matrix r;
};

void matrix_mult_block(const Matrix& A, const Matrix& B, Matrix& C){
	int N=A.numCols();
	int M=B.numRows();
	int k=A.numRows();

	const int block_size = 64 / sizeof(double); // 64 = common cache line size
	int s=block_size,temp;

	for(int jj=0;jj<N;jj+= s){
        for(int kk=0;kk<N;kk+= s){
            for(int i=0;i<N;i++){
                for(int j = jj; j<((jj+s)>N?N:(jj+s)); j++){
                    temp = 0;
                    for(int k = kk; k<((kk+s)>N?N:(kk+s)); k++){
                        //temp += a[i][k]*b[k][j];
                        temp+=A.at(i,k)*B.at(k,j);
                    }
                    //c[i][j] += temp;
                    C.at(i,j)=temp;
                }
            }
        }
	}
}

void matrix_mult_sec(const Matrix& a,const Matrix& b, Matrix& C){
	for (size_t r = 0; r < a.numRows(); r++)
	    for (size_t c = 0; c < b.numCols(); c++)
	      	for (size_t nc = 0; nc < b.numRows(); nc++)
	       		C.at(r, c) += a.at(r, nc) * b.at(nc, c);
}

void* mat_mult2(void *input){
  //((struct args*)input)->age)
  int core = step_i++;
  int N=matA.numRows();
  int M=matB.numCols();

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

void* mat_mult3(void *input){

	int core = step_i++;
	int N=matA.numRows();
	int M=matB.numCols();
	int K=N;

	const int block_size = 64 / sizeof(double); // 64 = common cache line size
	int s=block_size,temp;


	for(int jj=0;jj<N;jj+= s){
        for(int kk=0;kk<N;kk+= s){
            for(int i=0;i<N;i++){
                for(int j = jj; j<((jj+s)>N?N:(jj+s)); j++){
                    temp = 0;
                    for(int k = kk; k<((kk+s)>N?N:(kk+s)); k++){
                        //temp += a[i][k]*b[k][j];
                        temp+=matA.at(i,k)*matB.at(k,j);
                    }
                    //c[i][j] += temp;
                    matD.at(i,j)=temp;
                }
            }
        }
	}
}

void mult_hilos(const Matrix a,const Matrix b,int nthreads){
	matA=a;
	matB=b;

	pthread_t threads[nthreads];

	// Creating four threads, each evaluating its own part
	for (int i = 0; i < nthreads; i++) {
	  int* p;
	  pthread_create(&threads[i], NULL, mat_mult2, (void *)(p));
	}

	// joining and waiting for all threads to complete
	for (int i = 0; i < nthreads; i++)
	  pthread_join(threads[i], NULL);

	//matC.print();
}

void mult_hilos_tiling(Matrix a,Matrix b,int nthreads){
	matA=a;
	matB=b;

	pthread_t threads[nthreads];

	// Creating four threads, each evaluating its own part
	for (int i = 0; i < nthreads; i++) {
	  int* p;
	  pthread_create(&threads[i], NULL, mat_mult3, (void *)(p));
	}

	// joining and waiting for all threads to complete
	for (int i = 0; i < nthreads; i++)
	  pthread_join(threads[i], NULL);

	//matC.print();
}


int main(int argc, char** argv){
	while(cin >> nthreads){
		int op;

		cin >> tam;
		cin >> op;
		//int intentos=stoi(argv[4]);

		//cout<<"Multiplicacion de matrices...\n";
		//cout<<"-# hilos: "<<nthreads<<endl;
		//cout<<"-tamano de la matriz: "<<tam<<"x"<<tam<<endl;
		//cout<<"-operacion: "<<op<<endl;
		//cout<<"-intentos: "<<intentos<<endl;

		Matrix a(tam,tam);
		Matrix b(tam,tam);
		Matrix c(tam,tam);
		Matrix d(tam,tam);

		a.fill();
		b.fill();

		//a.print();
		//b.print();

		Timer t1;
		int time1=0;

		switch(op){
			case 1:
				//Secuencial
				matrix_mult_sec(a,b,d);
				time1=int(t1.elapsed());
				cout << time1 <<endl;
				break;
			case 2:
				//hilos
				mult_hilos(a,b,nthreads);
				time1=int(t1.elapsed());
				cout << time1 <<endl;
				break;
			case 3:
				//Tiling
				matrix_mult_block(a,b,c);
				time1=int(t1.elapsed());
				cout << time1 <<endl;
				break;
			case 4:
				//Tiling hilos
				mult_hilos_tiling(a,b,nthreads);
				time1=int(t1.elapsed());
				cout << time1 <<endl;
				break;
		}
		//return false;
	}

	/*
	d.print();
	cout<<endl<<endl;
	matC.print();
	cout<<endl<<endl;
	c.print();
	cout<<endl<<endl;
	matD.print();
	*/
	return 0;
}
