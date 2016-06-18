#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

long long fact[100005], inv[100005], dp[100005];
int MOD = (1e9) + 9;
int s[100005];
bool reach[100005];
int T, n;
vector<int> moves;

long long getexp(int x, int p) {
	if (!p) return 1;
	long long q = getexp(x, p/2);
	q = (q * q) % MOD;
	if (p & 1) q = (q * x) % MOD;
	return q;
}

int main() {
	fact[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	inv[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		inv[i] = inv[i - 1] * getexp(i, MOD - 2) % MOD;
	}
	/*dp[1] = dp[2] = 1;
	for (int i = 3; i <= 100000; i++) {
		for (int j = 1; j <= i/2; j++) {
			long long top = fact[i - 2], bot = (inv[j - 1] * inv[i - j - 1]) % MOD;
			top = (top * bot) % MOD;
			long long mult = (j == i - j) ? (i/2) : i;
			top = (top * mult) % MOD;
			mult = (dp[j] * dp[i - j]) % MOD;
			top = (top * mult) % MOD;
			dp[i] = (dp[i] + top) % MOD;
		}
		if (i <= 10) cout << i << ' ' << dp[i] << endl;
	}*/
	dp[1] = dp[2] = 1;
	for (int i = 3; i <= 100000; i++) dp[i] = getexp(i, i - 2);

	cin >> T;
	while (T--) {
		moves.clear();
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i];
		memset(reach, false, sizeof reach);

		int sz_count = 0;
		long long ret = 1;

		for (int i = 1; i <= n; i++) if (!reach[i]) {
			int cnt = 0, idx = i;
			while (true) {
				if (reach[idx]) break;
				cnt++;
				reach[idx] = true;
				idx = s[idx];
			}
			if (cnt > 1) {
				sz_count += (cnt - 1);
				moves.push_back(cnt - 1);
			}
		}
		ret = fact[sz_count];
		// cout << sz_count << endl;
		for (auto v : moves) {
			// cout << v << endl;
			ret = (ret * inv[v]) % MOD;
			ret = (ret * dp[v + 1]) % MOD;
		}
		cout << ret << endl;
	}
	return 0;
}