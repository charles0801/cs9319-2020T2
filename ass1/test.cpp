#include <iostream>
#include <vector>

using namespace std;

void add(int n) {
  n++;
}

void push(vector<int> &v, int n) {
  v.push_back(n);
}

int main(void) {
  vector<int> v;
  push(v, 2);
  cout << v.size();
  
  return 0;
}