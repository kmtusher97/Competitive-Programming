/**  ~*BISMILLAHIR RAHMANIR RAHIM*~  **/

#include <bits/stdc++.h>
using namespace std;

typedef long long intl;
intl n, a, b, nm[17], ff[17][2][9*17];

intl dfs( int pos, int ok, int sum ) {
  if( pos==n ) return sum;
  intl& ret = ff[pos][ok][sum];
  if( ~ret ) return ret;

  ret = 0LL;
  if( ok ) {
    for(int i=0; i<=9; i++) {
      ret += dfs( pos+1, 1, sum+i );
  } }
  else {
    for(int i=0; i<nm[n-pos-1]; i++) {
      ret += dfs( pos+1, 1, sum+i );
    }
    ret += dfs( pos+1, 0, sum+nm[n-pos-1] );
  }
  return ff[pos][ok][sum] = ret;
}

void digitPartion( intl x ) {
  memset(nm, 0, sizeof nm);
  n = 0;
  if( x<=0 ) n = 1;
  while( x>0 ) {
    nm[n++] = x%10, x /= 10;
  }
}

int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    scanf("%lld %lld", &a, &b);
    digitPartion( b );
    memset(ff, -1, sizeof ff);
    intl res = dfs( 0, 0, 0 );
    digitPartion( a-1 );
    memset(ff, -1, sizeof ff);
    res -= dfs( 0, 0, 0 );
    printf("%lld\n", res);
  }
  return 0;
}
