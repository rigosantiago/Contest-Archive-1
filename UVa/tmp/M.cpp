#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef __int128 ll;

vector<ll> toTest = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

ll modPow(ll a, ll m, ll n){
	ll ans = 1;

	for (; m; m /= 2){
		if(m % 2)
			ans = (ans * a) % n;
		a = (a * a) % n;
	}

	return ans;
}

bool isPrimeMR(ll n){
	if (n == 2) return true;
	if (n % 2 == 0 || n <= 1) return false;

	ll m;
	int k = 0;
	for(m = n-1; m % 2 == 0; m /= 2) k++;

	for(auto a: toTest){
		if (a >= n) break;
		
		ll x = modPow(a, m, n);

		if (x == 1 || x == n-1) continue;

		int j;
		for(j = 0; j < k-1; j++){
			x = (x * x) % n;
			if(x == n-1) break;
		}

		if (j == k - 1) return false;
	}

	return true;
}

ll factor(ll n){
	ll A = 2 + rand() % (n - 2);
	ll B = 2 + rand() % (n - 2);

	auto f = [&](ll x){ return x * (x + A) % n + B; };
	ll d, x = 2, y = 2;

	do{
		x = f(x);
		y = f(f(y));
		d = __gcd(x >= y ? x - y : y - x, n);
	} while (d == 1);

	return d;
}

void factorize(ll n, vector<ll> &v){
	if (n == 1) return;
	if (isPrimeMR(n)){
		v.push_back(n);
		return;
	}

	ll f;
	do f = factor(n);
	while (f == n);

	factorize(f, v);
	factorize(n/f, v);
}

int main(){
	int t;

	scanf("%d", &t);

	vector<ll> f;

	while (t--){
		long long n;

		scanf("%lld", &n);

		f.clear();
		factorize(n, f);
		sort(f.begin(), f.end());

		ll ans = 1;

		vector<ll>::iterator e;
		const __int128 lim = 1LL<<62;
		for (auto it = f.begin(); it != f.end(); it = e){
			e = find_if(it, f.end(), [=](ll x){ return x != *it; });

			ll ai = distance(it, e);

			ans *= (modPow(*it, ai+1, lim) - 1) / (*it - 1);
		}

		ans -= n;
		//printf("%lld\n", (long long) ans);

		if (ans < n)
			printf("deficient\n");
		else if (ans == n)
			printf("perfect\n");
		else
			printf("abundant\n");
	}
}
