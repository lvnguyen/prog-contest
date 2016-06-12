#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int n, L, T;
string good[105];
string bad;

int main() {
	cin >> T;;
	for (int it = 1; it <= T; it++) {
		cin >> n >> L;
		for (int i = 0; i < n; i++) cin >> good[i];
		cin >> bad;

		bool is_bad = false;
		for (int i = 0; i < n; i++) if (good[i] == bad) is_bad = true;
		printf("Case #%d: ", it);
		if (is_bad) {
			printf("IMPOSSIBLE\n");
		} else {
			for (int i = 0; i < L; i++) {
				if (bad[i] == '1') printf("0"); else printf("1");
				printf("?");
			}
			printf(" ");
			for (int i = 0; i < L; i++) {
				if (bad[i] == '1') printf("0"); else printf("1");
				if (i + 1 < L) printf("%c", bad[i]);
			}
			printf("\n");
		}
	}
	return 0;
}