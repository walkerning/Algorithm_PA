#include "gen_randint.h"
#include <iostream> // fortest
// using namespace std;

unsigned int* gen_randints(int max_bit, int num) {
  unsigned int* ans = new unsigned int[num];
  //cout << RAND_MAX << endl;
  int bits = log2((unsigned int)RAND_MAX + 1);
  // cout << bits << endl;
  int num_sec = max_bit / bits;
  // cout << num_sec << endl;
  int residual = max_bit % bits;
  // cout << residual << endl;
  for (int i = 0; i < num; i++) {
    ans[i] = 0;
    for (int j = 0; j < num_sec; j ++) {
      ans[i] <<= bits;
      ans[i] += rand();
    }
    if (residual != 0) {
      ans[i] <<= residual;
      ans[i] += rand() >> (bits - residual);
    }
  }
  return ans;
}
