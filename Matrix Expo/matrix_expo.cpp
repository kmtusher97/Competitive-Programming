/* BISMILLAHIR RAHMANIR RAHIM */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MX_N 16
ll MOD;

/*------------------ Matrix Expo ----------------*/
class matrix {
  public:
    int n;
    vector< vector<ll> > mm;

    void initialize( vector<ll> f ) {
      n = f.size();
      mm.clear();
      mm.push_back(f);
      for(int i = 1; i < n; i++) {
        vector<ll> tmp;
        for(int j = 0; j < i - 1; j++)
          tmp.push_back(0);
        tmp.push_back(1);
        for(int j = i; j < n; j++)
          tmp.push_back(0);

        mm.push_back(tmp);
      }
    }

    void identity_matrix( int o ) {
      n = o;
      mm.clear();
      for(int i = 0; i < n; i++) {
        vector<ll> tmp;
        for(int j = 0; j < i; j++)
          tmp.push_back(0);
        tmp.push_back(1);
        for(int j = i + 1; j < n; j++)
          tmp.push_back(0);

        mm.push_back(tmp);
      }
    }

    matrix operator * ( matrix o ) const {
      matrix r;
      r.n = o.n;
      for(int i = 0; i < n; i++) {
        vector<ll> tmp;
        for(int j = 0; j < n; j++) {
          ll sum = 0LL;
          for(int k = 0; k < n; k++)
            sum = (sum % MOD + (mm[i][k] * o.mm[k][j]) % MOD) % MOD;

          tmp.push_back(sum);
        }
        r.mm.push_back(tmp);
      }
      return r;
    }

    void prnt() {
      printf("%d x %d : \n", n, n);
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
          printf("%5lld ", mm[i][j]);
        }
        printf("\n");
      }
      printf("-----------------------\n\n");
    }
};

matrix Expo( matrix B, ll p ) {
  matrix I;
  I.identity_matrix( B.n );

  for(; p > 0; p /= 2) {
    if( p & 1 ) I = I * B;
    B = B * B;
  }
  return I;
}

/*--------------------------------------------------------*/

int main() {
  ll d, n, m;
  while( ~scanf("%lld %lld %lld", &d, &n, &m) and d and n and m ) {
    vector<ll> a(d), f(d);
    for(int i = 0; i <d; i++)
      scanf("%lld", &a[i]), a[i] %= m;
    for(int i = 0; i <d; i++)
      scanf("%lld", &f[i]), f[i] %= m;

    if( n <= d ) {
      printf("%lld\n", f[d - n]);
      continue;
    }

    MOD = m;
    matrix B;
    B.initialize( a );
   // B.prnt();
    matrix R = Expo( B, max(0LL, n - d) );
    //R.prnt();
    ll res = 0LL;
    for(int i = 0; i < d; i++)
      res = (res % m + (f[d - i - 1] * R.mm[0][i]) % m) % m;

    printf("%lld\n", res);
  }
  return 0;
}
