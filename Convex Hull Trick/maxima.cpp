/* BISMILLAHIR RAHMANIR RAHIM */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = 1e18;
const ll neg_inf = -(1LL << 62);

struct Line {
	ll m, c;
	mutable function< const Line*() > line;
	bool operator < ( const Line& o ) const {
		if( o.c != neg_inf ) 
			return m < o.m;
		const Line* l1 = line();

		if( !l1 ) return false;
		ll x = o.m;
		return ((c - l1->c) < (l1->m - m) * x);
	}
};

struct ConvexHullTrick : public multiset<Line> {
	bool bad( iterator y ) {
		auto z = next(y);
		if( y == begin() ) {
			if( z == end() ) return false;
			return (y->m == z->m and y->c <= z->c);
		}
		auto x = prev(y);
		if( z == end() )
			return (y -> m == x -> m and y -> c <= x -> c);
		return (1.0 * (x -> c - y -> c) * (z -> m - y -> m) >= 1.0 * (y -> c - z -> c) * (y -> m - x -> m));
	}

	void add_line( ll m, ll c ) {
		auto y = insert({m, c});
		y -> line = [=]{ return next(y) == end() ? 0 : &*next(y); };

		if( bad( y ) ) {
			erase(y); 
			return;
		}
		for(; next(y) != end() and bad(next(y)); erase(next(y)));
		for(; y != begin() and bad(prev(y)); erase(prev( y )));
	}

	ll query( ll x ) {
		auto l = *lower_bound((Line) {x, neg_inf});
		return (l.m * x + l.c);
	}
};


int main() {
	ios_base :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector< pair< pair<ll, ll> , ll > > A(n);
	for(int i = 0; i < n; i++) {
		cin >> A[i].first.first >> A[i].first.second >> A[i].second;
	}
	sort(A.begin(), A.end());

	//dp(i) = xi.yi - ai + F(0 < j < i)MAX(-xj.yi + dp(j))

	ConvexHullTrick cht;
	ll cost = 0LL, res = -1e16;
	cht.add_line( 0, 0 );
	
	for(int i = 0; i < n; i++) {
		cost = A[i].first.first *  A[i].first.second - A[i].second + cht.query( A[i].first.second );
		cht.add_line( -A[i].first.first, cost );
		res = max(res, cost);
	}

	cout << res << "\n";
}