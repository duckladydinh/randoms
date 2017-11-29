/**
 * 
 * First Experiment Project: How to use FFT sample code
 * to efficiently compute all catalan numbers from 1..n
 * 
 * Formula: catalan[n+1] = catalan[i] * catalan[n - i], i = 0..n
 * Command Line: g++ -std=gnu++14 fft_convolution_catalan.cpp && time ./a.out
 * 
 * Date: Nov. 24, 2017
 * Time: 23:45
 * 
 * Result:
 * + Convolution is slower for n < 2^15
 * + All comparisions are correct
 * + Mysteries: While len + len - 1?
 * 
*/

#include <bits/stdc++.h>
#include "fft.h"
using namespace std;

const int N = 1 << 20;
const int mod = 1e9 + 7;
long long catalan[N];

// FFT wrapper for vectors
vector<long long> mult(vector<long long> &a, vector<long long>& b) {
  int n = a.size(), m = b.size();
  while (a.size() < b.size()) a.push_back(0);
  while (b.size() < a.size()) b.push_back(0);
  int N = max(n, m);
  vector<long long> c(N+N);
  FFT::mult_mod(&a[0], &b[0], &c[0], N, mod);
  c.resize(n+m-1);
  return c; 
}

// divide and conquer
void solve(int l, int r) {
  if (l + 1 == r) return;
  int m = (l + r) / 2;
  // solve the left half
  solve(l, m);
  // compute contribution
  int len = m - l;
  vector<long long> a(&catalan[l], &catalan[l + len]);
  vector<long long> b(&catalan[0], &catalan[len + (l != 0 ? len - 1 : 0)]);
  auto c = mult(a, b);
  // add contribution
  for (int i = len - 1; i < len + len - 1; ++i) {
    if (l == 0) {
      catalan[l + i + 1] += c[i];
    } else {
      catalan[l + i + 1] += c[i] * 2;  
    }
    catalan[l + i + 1] %= mod;
  }
  // solve the right half
  solve(m, r);
}


// brute force
vector<long long> brute_catalan(int n) {
  vector<long long> catalan {1};
  for (int i = 1; i <= n; ++i) {
    long long res = 0;
    for (int j = 0; j < i; ++j) {
      res = (res + (catalan[j] * catalan[i - j - 1])) % mod;
    }
    catalan.push_back(res);
  }
  return catalan;
}


int main() {
  catalan[0] = 1;

  int n = 1 << 5;
  solve(0, n);
  auto correct = brute_catalan(n - 1);
  cout << "\n";
  for (int i = 0; i < n; ++i) {
    printf("%3d|%20lld\tvs%17lld\n", i, catalan[i], correct[i]);
  }
  return 0;
}
