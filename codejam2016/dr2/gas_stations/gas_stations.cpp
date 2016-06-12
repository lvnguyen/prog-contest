#include <cstdio>
#include <cstdlib>
#include <deque>
#include <vector>
#include "message.h"
#include "gas_stations.h"
using namespace std;

vector< pair<int,int> > value;
int N, K, m, id;
deque< pair<int, int> > s;
const int MASTER_NODE = 0;

int main() {
  N = GetNumKms();
  K = GetTankSize();
  m = NumberOfNodes();
  id = MyNodeId();

  int low = 1LL * N * id / m, high = 1LL * N * (id + 1)/m;
  if (high > N) {
    high = N;
  }

  for (int i = low - K + 1; i < high; i++) if (i >= 0) {
    int price = GetGasPrice(i);
    value.push_back(make_pair(price, i)); 
  }

  long long totalSum = 0;
  for (auto v : value) {
    while (!s.empty() && v.second - s.front().first >= K) s.pop_front();
    while (!s.empty() && v.first <= s.back().first) s.pop_back();
    s.push_back(v);
    if (v.second >= low) {
      totalSum += v.first;
    }
  }

  PutLL(MASTER_NODE, totalSum);
  Send(MASTER_NODE);

  if (id == MASTER_NODE) {
    long long finalSum = 0;
    for (int i = 0; i < m; i++) {
      Receive(i);
      finalSum += GetLL(i);
    }
    printf("%lld\n", finalSum);
  }
  return 0;
}
