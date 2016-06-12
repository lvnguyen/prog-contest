#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

string tests[5];
int prereq[105], weight[105], indeg[105];
int appear[5];
vector<int> adj[105];
string method;
int T, n, m;

int recurse(int x) {
	weight[x] = 1;
	for (auto v : adj[x]) {
		weight[x] += recurse(v);
	}
	return weight[x];
}

int main() {
	cin >> T;
	for (int it = 1; it <= T; it++) {
		fprintf(stderr, "%d\n", it);
		cin >> n;

		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			indeg[i] = 0;
			weight[i] = 0;
		}

		for (int i = 1; i <= n; i++) {
			cin >> prereq[i];
			if (prereq[i] != 0) {
				adj[prereq[i]].push_back(i);
				indeg[i] = 1;
			}
		}
		for (int i = 1; i <= n; i++) if (!indeg[i]) recurse(i);

		cin >> method;
		cin >> m;
		for (int i = 0; i < m; i++) {
			appear[i] = 0;
			cin >> tests[i];
		}

		for (int sim = 0; sim < 10000; sim++) {
			string eval = "";
			vector<int> options;
			for (int i = 1; i <= n; i++) if (!indeg[i]) {
				options.push_back(i);
			}

			for (int i = 0; i < n; i++) {
				int total_count = 0;
				for (int j = 0; j < options.size(); j++) if (options[j] > 0) {
					total_count += weight[options[j]];
				}

				int picks = rand() % total_count, sum = 0;
				for (int j = 0; j < options.size(); j++) if (options[j]) {
					int candidate = options[j];
					if (sum <= picks && picks < sum + weight[options[j]]) {
						options[j] = 0;
						eval += method[candidate - 1];
						for (auto v : adj[candidate]) {
							options.push_back(v);
						}
						break;
					}
					sum += weight[options[j]];
				}
			}

			for (int i = 0; i < m; i++) {
				if (eval.find(tests[i]) != string::npos) {
					appear[i]++;
				}
			}
		}
		printf("Case #%d: ", it);
		for (int i = 0; i < m; i++) printf("%.5lf ", appear[i] * 1. / 10000);
		printf("\n");
	}
	return 0;
}
