#include <bits/stdc++.h>
using namespace std;


int main() {

  int tiempo, hilos, aux=2;
  int i = 0;
  while (cin>>hilos) {
    if(hilos != aux){
      cout<<endl;
      aux = hilos;
    }
    cin>>tiempo;
    cout<<tiempo<<" ";
    i++;
    if(i==10){
      i = 0;
      cout<<endl;
    }
  }
  return 0;
}
