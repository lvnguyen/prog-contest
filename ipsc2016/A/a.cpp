#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int T;
string s[10];

int main() {
	cin >> T;
	while (T--) {
		for (int i = 0; i < 10; i++) {
			cin >> s[i];
		}
		int L = s[0].size();
		bool ans = false;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) if (i != j) {
				for (int k = 0; k < L; k++) {
					if (s[i].substr(k, L) == s[j].substr(0, L - k)) {
						if (ans) continue;
						ans = true;
						string sol = s[i] + s[j].substr(L - k, L);
						for (int t = 0; t < 10; t++) if (t != i && t != j) sol += s[t];
						while (sol.size() < 39) sol += "X";
						cout << sol << endl; 
					}
				}
			}
		}
	}
	return 0;
}