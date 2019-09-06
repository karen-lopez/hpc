#include <bits/stdc++.h>

using namespace std;

//funcion que multiplica 2 matrices (A Y B) de tamaño NXN y
//retorna el resultado de la multiplicacion
vector<vector< int > > multmatris(vector<vector< int > > A, vector<vector< int > > B,int N){
  vector<vector< int > > C(N,vector<int>(N));

  for(int i= 0; i<N; ++i){
        for(int j=0; j<N; ++j){
            for(int z=0; z<N; ++z){
                C[i][j] += A[i][z] * B[z][j];
            }
          }
  }
  return C;
}

int main(){
    int casos;
    cin>>casos;
    while (casos > 0) {
      int N;
      scanf("%d", &N);
      vector<vector< int > > A(N,vector<int>(N));
      vector<vector< int > > B(N,vector<int>(N));
      vector<vector< int > > C(N,vector<int>(N));
      clock_t times;


      //rellenar matrices
      for(int i=0; i<N; i++){

               for(int j=0; j<N; j++){

                      A[i][j] = rand() % 10;
                      B[i][j] = rand() % 10;

                }

      }

      times = clock();
      C = multmatris(A, B, N);
      times = clock() - times;

      printf("%f\n", ((float)times)/CLOCKS_PER_SEC);
      casos--;
  }

}
