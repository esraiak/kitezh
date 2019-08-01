#include "../allt.h"
#include <string>
#include <iostream>
#include <thread>
#define P(x) cout << x << endl;
#define I(u, v) if(u) { v };
typedef double fl;

const int n = 2000;
const fl inf = fl(1<<30);

fl f[n+10];
fl DP[n+10][n+10];

fl dp(int a, int b) {
  if(DP[a][b] >= 0) return DP[a][b];
  if(b - a == 1) return DP[a][b] = 0;
  assert(b - a >= 1);
  fl denom = b-a;
  fl smallest = inf;
  for(int x = a+1; x <= b-1; ++x) {
    fl cand = f[x] + ( (x - a) * dp(a, x) + (b - x) * dp(x, b) ) / denom;
    if(cand < smallest) {
      smallest = cand;
    }
  }
  return DP[a][b] = smallest;
}

void task(int a0, int a1, int k, int id) {
  for(int a = a0; a < a1; ++a)
   dp(a, a+k);
}

void in_parallel(int a0, int a1, int k, int n_th) {
  assert(a1-1+k <= n);
  int per_th = (a1 - a0) / n_th;
  int start = a0;
  vector<thread*> ths(n_th);
  rep(t, 0, n_th) {
    if(t != n_th - 1) ths[t] = new thread(task, start, start + per_th, k, t);
    else              ths[t] = new thread(task, start, a1, k, t);
    start += per_th;
  }
  rep(t, 0, n_th) {
    ths[t]->join();
    delete ths[t];
  }
}

//DP[a][b] needs to be computed before running this
int equi(int a, int b) {
  int mark = -1;
  fl smallest = inf;
  fl denom = b-a;
  for(int x = a+1; x <= b-1; ++x) {
    fl cand = f[x] + ( (x - a) * dp(a, x) + (b - x) * dp(x, b) ) / denom;
    cout << cand << endl;
    if(cand < smallest) {
      smallest = cand;
      mark = x;
    }
  }
  return mark;
}

void channeled() {
  double x;
  int _n = 0;
  while(cin >> x) {
    f[_n++] = x;
  }
  if(_n > n) { cout << "can handle at most " << n << " input weights" << endl; }
  rep(i,0,_n+1)rep(j,0,_n+1) DP[i][j]= -1;
  int n_th = 24;
  rep(k, 1, _n) {
    in_parallel(0, _n-k+1, k, n_th);
  }
  equi(0,_n);
}

void normal() {
  rep(i,0,n+1)rep(j,0,n+1) DP[i][j]= -1;
  rep(i,0,n) {
    f[i] = pow(log(i+1),5.0);
  }
  int n_th = 24;
  rep(k, 1, n) {
    in_parallel(0, n-k+1, k, n_th);
  }
  equi(0,n);
}

int main() {
  channeled();
}
