/*  ~*BISMILLAHIR RAHMANIR RAHIM*~  */
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef vector<int> vi;
#define MX_N 500005

vi G[MX_N];

/*------------------------HLD Section---------------------------*/
static int dpth;
int prnt[MX_N], st[MX_N], ed[MX_N];
int head[MX_N], big_child[MX_N], sz[MX_N];

void dfs( int u = 1 , int p = 0 ) {
  sz[u] = 1, prnt[u] = p;
  int mx = -1;

  for(auto& v : G[u]) {
    if( v == p ) continue;
    dfs( v, u ), sz[u] += sz[v];
    if( sz[v] > mx )
      mx = sz[v], big_child[u] = v;
  }
}

void decompose( int u = 1, int p = 0 ) {
  st[u] = ++dpth;

  if( big_child[u] )
    head[big_child[u]] = head[u], decompose( big_child[u], u );

  for(auto& v : G[u])
    if( v != p && v != big_child[u] )
      head[v] = v, decompose( v, u );

  ed[u] = dpth;
}
/*-------------------------------------------------------------*/

int sg[MX_N * 4], lzy[MX_N * 4];

void Prp( int nd, int l, int r ) {
  sg[nd] = lzy[nd];
  if( l != r )
    lzy[nd << 1] = lzy[(nd << 1) | 1] = lzy[nd];

  lzy[nd] = -1;
}

void U( int nd, int l, int r, int L, int R, int x ) {
  if( ~lzy[nd] ) Prp( nd, l, r );
  if( l > R || r < L ) return;
  if( l >= L && r <= R ) {
    lzy[nd] = x, Prp( nd, l, r );
    return;
  }

  int mid = l + (r - l) / 2, lft = nd << 1, rgt = lft | 1;
  U( lft, l, mid, L, R, x );
  U( rgt, mid + 1, r, L, R, x );
  sg[nd] = sg[lft] | sg[rgt];
}

int Q( int nd, int l, int r, int L, int R ) {
  if( ~lzy[nd] ) Prp( nd, l, r );
  if( l > R || r < L ) return 0;
  if( l >= L && r <= R ) return sg[nd];

  int mid = l + (r - l) / 2, lft = nd << 1, rgt = lft | 1;
  return Q( lft, l, mid, L, R ) | Q( rgt, mid + 1, r, L, R );
}


int main() {
  int n, m;
  scanf("%d", &n);
  for(int i = 1, u, v; i < n; i++) {
    scanf("%d %d", &u, &v);
    G[u].pb(v), G[v].pb(u);
  }

  /*----------HLD------------*/
  head[1] = 1, dpth = 0;
  dfs();
  decompose();
  /*-------------------------*/

  memset(lzy, -1, sizeof lzy);

  scanf("%d", &m);
  for(int i = 1, t, u; i <= m; i++) {
    scanf("%d %d", &t, &u);
    if( t == 1 )
      U( 1, 1, dpth, st[u], ed[u], 1 );
    else if( t == 2 )
      for(; u; u = prnt[head[u]]) /* updating the ancestors of node u */
        U( 1, 1, dpth, st[head[u]], st[u], 0 );
    else
      printf("%d\n", Q( 1, 1, dpth, st[u], st[u] ));
  }
  return 0;
}
