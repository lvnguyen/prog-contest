#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int T, n;
string s;

int main() {
	scanf("%d", &T);
	for (int it = 1; it <= T; it++) {
		cin >> s;
		int score = 0;
		while (true) {
			bool match = false;
			for (int i = 0; i + 1 < s.size(); i++) {
				if (s[i] == s[i + 1]) {
					string t = s.substr(0, i) + s.substr(i + 2, s.size());
					score += 10;
					match = true;
					s = t;
					break;
				}
			}
			if (!match) {
				break;
			}
		}
		score += 5 * s.size() / 2;
		printf("Case #%d: %d\n", it, score);
	}
	return 0;
}