#include "again.h"
#include "message.h"
#include <cstdio>
#include <vector>
using namespace std;

int N;
int MASTER_NODE = 0;
int MOD = (int) (1e9) + 7;
vector<int> totalSumA, totalSumB;

int main() {
	long long sumA = 0, sumB = 0;
	N = GetN();
	int nodes = NumberOfNodes(), id = MyNodeId();

	for (int i = id; i < N; i += nodes) {
		sumA += GetA(i);
		sumB += GetB(i);
		sumA %= MOD;
		sumB %= MOD;
	}

	PutLL(MASTER_NODE, sumA);
	PutLL(MASTER_NODE, sumB);
	Send(MASTER_NODE);

	if (id == MASTER_NODE) {
		totalSumA.resize(nodes);
		totalSumB.resize(nodes);

		for (int i = 0; i < nodes; i++) {
			Receive(i);
			totalSumA[i] = GetLL(i);
			totalSumB[i] = GetLL(i);
		}

		long long sum = 0;
		for (int i = 0; i < nodes; i++) {
			for (int j = 0; j < nodes; j++) {
				if ((i + j) % nodes) {
					sum = (sum + totalSumA[i] * totalSumB[j]) % MOD;
				}
			}
		}
		printf("%lld\n", sum);
	}
	return 0;
}