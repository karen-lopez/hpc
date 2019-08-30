#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;
#define NUM_THREADS	4
vector<vector< int > > C;

struct thread_data {
  int	thread_id;
  vector<vector< int > > A;
  vector<vector< int > > B;
  int N;
} mult[NUM_THREADS];



void *multmat(void *threadarg){
  int t,N;
  vector<vector< int > > A, B, Caux;
  struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;
   t = my_data->thread_id;
   N = my_data->N;
   A = my_data->A;
   B = my_data->B;

   std::cout << "t es: " << t <<'\n';

  for(int i=(N/4)*t; i<(N/4)*(t+1); ++i){
        for(int j=0; j<N; ++j){
            for(int z=0; z<N; ++z){
                C[i][j] += A[i][z] * B[z][j];
            }
          }
        }


}


int main(){
    int N;
    scanf("%d", &N);
    vector<vector< int > > A(N,vector<int>(N));
    vector<vector< int > > B(N,vector<int>(N));
    vector<vector< int > > aux(N,vector<int>(N));
    C = aux;
    clock_t t;

   //rellenar matrices
   for(int i=0; i<N; i++){

             for(int j=0; j<N; j++){

                    A[i][j] = rand() % 10;
                    B[i][j] = rand() % 10;

              }

   }

   // Impresión de las matrices

   for(int i=0; i<N; i++){

         for(int j=0; j<N; j++){

                 cout <<  A[i][j] << " ";

         }

         cout << endl;

   }

   cout << endl;

   for(int i=0; i<N; i++){

            for(int j=0; j<N; j++){

                   cout <<  B[i][j] << " ";

           }

           cout << endl;

   }

   //empieza a tomar el tiempo
   t = clock();

   //hilos
   pthread_t threads[NUM_THREADS];
   int *taskids[NUM_THREADS];
   int rc;
   long thread;
   for(thread=0;thread<NUM_THREADS;thread++){
     mult[thread].thread_id = thread;
     mult[thread].N = N;
     mult[thread].A = A;
     mult[thread].B = B;
     printf("In main: creating thread %ld\n", thread);
     rc = pthread_create(&threads[thread], NULL, multmat, (void *) &mult[thread]);
     if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
    }

    t = clock() - t;
   //C = multmat(A, B, C, N);

   cout << endl;

   for(int i=0; i<N; i++){

            for(int j=0; j<N; j++){

                   cout <<  C[i][j] << " ";

           }

           cout << endl;

   }


   printf ("It took me %d clicks (%f seconds).\n",(int)t,((float)t)/CLOCKS_PER_SEC);
   pthread_exit(NULL);


   return 0;
}
