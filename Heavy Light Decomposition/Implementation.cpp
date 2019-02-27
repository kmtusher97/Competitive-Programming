#define MX_N 30005
int n, a[MX_N];
vector<int> G[MX_N];

/*--------------BIT---------------*/
ll tt[MX_N * 2];

void Upd( int id, ll v ) {
  for(; id <= n; tt[id] += v, id += (id & -id));
}

ll Qry( int id ) {
  ll sum = 0LL;
  for(; id > 0; sum += tt[id], id -= (id & -id));
  return sum;
}

ll QryR( int L, int R ) {
  return Qry( R ) - Qry( L - 1 );
}
/*--------------------------------*/

/*--------------HLD---------------*/
int dpth, H[MX_N], P[MX_N], sz[MX_N];
int head[MX_N], st[MX_N];

void dfs_sz( int u = 1, int p = 0 ) {
  H[u] = H[p] + 1;
  P[u] = p, sz[u] = 1;

  for(int i = 0; i < (int)G[u].size(); i++) {
    int v = G[u][i];
    if( v == p ) continue;
    dfs_sz( v, u ), sz[u] += sz[v];
    if( sz[v] > sz[G[u][0]] )
      swap(G[u][0], G[u][i]); // big child in index 0
  }
}

void decompose( int u = 1, int p = 0 ) {
  st[u] = ++dpth;
  Upd( st[u], a[u] ); //create DS

  for(int i = 0; i < (int)G[u].size(); i++) {
    int v = G[u][i];
    if( v == p ) continue;
    head[v] = i ? v : head[u];
    decompose( v, u );
  }
}

void UpdHLD( int u, int vlu ) {
  ll tvlu = QryR( st[u], st[u] );
  Upd( st[u], -tvlu );
  Upd( st[u], vlu );
}

ll QryHLD( int u, int v ) {
  ll ret = 0LL;
  while( head[u] != head[v] ) {
    if( H[head[u]] > H[head[v]] )
      ret += QryR( st[head[u]], st[u] ), u = P[head[u]];
    else
      ret += QryR( st[head[v]], st[v] ), v = P[head[v]];
  }
  ret += QryR( min(st[u], st[v]), max(st[u], st[v]) );
  return ret;
}
/*--------------------------------*/

int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
      scanf("%d", a + i), G[i].clear();

    for(int i = 2, u, v; i <= n; i++) {
      scanf("%d %d", &u, &v), u++, v++;
      G[u].push_back(v);
      G[v].push_back(u);
    }

    memset(tt, 0, sizeof tt);
    dpth = 0, head[1] = 1;
    dfs_sz();
    decompose();

    int Q;
    scanf("%d", &Q);
    printf("Case %d:\n", ++caseno);
    while( Q-- ) {
      int t, x, y;
      scanf("%d %d %d", &t, &x, &y);
      if( t ) UpdHLD( ++x, y );
      else printf("%lld\n", QryHLD( ++x, ++y ));
    }
  }

  return 0;
}
