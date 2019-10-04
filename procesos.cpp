#include <bits/stdc++.h>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
    int casos;
    cin>>casos;
    while (casos > 0) {
      int N;
      scanf("%d", &N);
      vector<vector< int > > A(N,vector<int>(N));
      vector<vector< int > > B(N,vector<int>(N));
      //vector<vector< int > > transpuesta(N,vector<int>(N));
      vector<vector< int > > C(N,vector<int>(N));
      std::chrono::time_point<std::chrono::system_clock> instanteInicial, instanteFinal;

      //rellenar matrices
      for(int i=0; i<N; i++){

               for(int j=0; j<N; j++){

                      A[i][j] = rand() % 10;
                      B[i][j] = rand() % 10;

                }

      }
      //transpuesta de la matriz B
      /*for(int i=0; i<N; i++){
               for(int j=0; j<N; j++){
                      transpuesta[j][i] = B[i][j];
                }
      }*/

      instanteInicial= std::chrono::system_clock::now();
       //pid_t pid;
       for (int i = 0; i < N; i++) {
          pid_t pid = vfork(); //creating the child process

          if (pid<0){
            cout<<"error, el pid es menor a cero";
          }

          if (pid == 0)          //if this is a chile process
          {
            for(int j=0; j<N; ++j){
                for(int z=0; z<N; ++z){
                    C[i][j] += A[i][z] * B[z][j];
                }
              }
              //printf("Child process finish %d\n", i);
              exit(0);
            }

          if (pid>0)//parent process execution
          {
              //printf("Now i am coming back to parent process\n");
              wait(0);
          }
      }

      instanteFinal  = std::chrono::system_clock::now();

      std::chrono::duration<double> segundos = instanteFinal-instanteInicial;
      cout << segundos.count() << endl;
      casos--;
  }
  return 0;
}
