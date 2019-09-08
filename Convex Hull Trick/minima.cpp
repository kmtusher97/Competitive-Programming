/* BISMILLAHIR RAHMANIR RAHIM */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
/**
 * **Convex Hull Trick**
 *
 * upper hull for maxima
 * add lines {-m, -b} and retrun -ans for minima 
 */
const ll neg_inf = -(1LL << 62);
 
struct Line {
	ll m, c;
	mutable function< const Line*() > line;
 
	bool operator < ( const Line& other ) const {
		if( other.c != neg_inf ) 
			return m < other.m;
		
		const Line* l1 = line();
		if( !l1 ) return false;
		ll x = other.m;
		return (c - l1->c) < (l1->m - m) * x;
	}
};
 
 
struct HullDynamic : public multiset<Line> {
	bool bad( iterator it2 ) {
		auto it3 = next( it2 );
		if( it2 == begin() ) {
			if( it3 == end() ) return false;
			return it2->m == it3->m and it2->c <= it3->c;
		}
		auto it1 = prev( it2 );
		if( it3 == end() ) {
			return it2->m == it1->m and it2->c <= it1->c;
		}
		return (
			1.0 * (it1->c - it2->c) * (it3->m - it2->m) >=
			1.0 * (it2->c - it3->c) * (it2->m - it1->m)
		);
	}
 
	void add_line( ll m, ll c ) {
		auto it = insert( {m, c} ); 
		
		it->line = [=] { return next( it ) == end() ? 0 : &*next( it ); };
		if( bad( it ) ) {
			erase( it );
			return;
		}
		for(; next( it ) != end() and bad( next( it ) ); erase( next( it ) ));
		for(; it != begin() and bad( prev( it ) ); erase( prev( it ) ));
	} 
 
	ll query( ll x ) {
		auto lb = *lower_bound( (Line){x, neg_inf} );
		return (lb.m * x + lb.c);  
	}
};
 
int main() {
	ios_base :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<ll> A(n), B(n);
	for(auto& a : A) {
		cin >> a;
	}
	for(auto& b : B) {
		cin >> b;
	}
 
	ll cost = 0, res = 1e18;
	HullDynamic cht;
	
	for(int i = 0; i < n; i++) {
		if( i == 0 ) {
			cht.add_line( -B[i], 0 );
			continue;
		}
		cost = cht.query( A[i] );
		cht.add_line( -B[i], cost );
		res = min(res, cost);
	}
	cout << -res << "\n";
}
/**
 * dp(i) = min {a[i]. b[j] + dp(j)}
 *        0<j<i
 */
