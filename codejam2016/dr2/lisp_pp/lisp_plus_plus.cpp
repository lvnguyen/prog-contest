#include "lisp_plus_plus.h"
#include "message.h"
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int prefix[10000005], N, m, id;
int MASTER_NODE = 0;

int main() {
	N = GetLength(), m = NumberOfNodes(), id = MyNodeId();
	int low = 1LL * N * id / m, high = 1LL * N * (id + 1)/m;
	if (high >= N) {
		high = N;
	}

	for (int i = low; i < high; i++) {
		char ch = GetCharacter(i);
		prefix[i - low] = (ch == '(') ? 1 : -1;
	}
	for (int i = low + 1; i < high; i++) {
		prefix[i - low] += prefix[i - 1 - low];
	}
	
	// send all prefix sum to master
	if (low < high) {
		PutInt(MASTER_NODE, prefix[high - 1 - low]);
	}
	else {
		PutInt(MASTER_NODE, 0);
	}
	Send(MASTER_NODE);

	if (id == MASTER_NODE) {
		int totalSum = 0;
		for (int i = 0; i < m; i++) {
			PutInt(i, totalSum);
			Send(i);

			Receive(i);
			int val = GetInt(i);
			totalSum += val;
		}
	}

	// receive sum of prefixes from master node
	Receive(MASTER_NODE);
	int totalSum = GetInt(MASTER_NODE);
	int break_id = -1;
	for (int i = low; i < high; i++) {
		if (prefix[i - low] + totalSum < 0) {
			break_id = i;
			break;
		}
	}
	PutInt(MASTER_NODE, break_id);
	Send(MASTER_NODE);

	if (id == MASTER_NODE) {
		int final_id = -1;
		for (int i = 0; i < m; i++) {
			Receive(i);
			int my_id = GetInt(i);
			if (my_id >= 0 && final_id < 0) {
				final_id = my_id;
			}
		}
		printf("%d\n", final_id);
	}
	return 0;
}