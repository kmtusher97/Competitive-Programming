int h[MX_N], sp[MX_N][MX_LOG][2];

void dfs( int u, int p, int c ) {
  sp[u][0][1] = c, sp[u][0][0] = p;
  if( p + 1 ) h[u] = h[p] + 1;

  for(int i = 1; i < MX_LOG; i++)
    if( sp[u][i - 1][0] + 1 ) {
      sp[u][i][1] = max( sp[u][i - 1][1], sp[sp[u][i - 1][0]][i - 1][1] );
      sp[u][i][0] = sp[sp[u][i - 1][0]][i - 1][0];
    }

  for(int i = 0; i < (int)G[u].size(); i++) {
    pii v = G[u][i];
    if( v.F != p )
      dfs( v.F, u, v.S );
  }
}

int queryLCA( int u, int v ) {
  if( h[u] < h[v] )
    swap(u, v);
  int res = 0;
  for(int i = MX_LOG-1; i >= 0; i--)
    if( sp[u][i][0] + 1 && h[sp[u][i][0]] >= h[v] )
      res = max( res, sp[u][i][1] ), u = sp[u][i][0];

  for(int i = MX_LOG - 1; i >= 0; i--)
    if( sp[u][i][0] != sp[v][i][0] ) {
      res = max( res, max( sp[u][i][1], sp[v][i][1] ) );
      u = sp[u][i][0], v = sp[v][i][0];
    }

  if( u != v ) {
    res = max( res, max( sp[u][0][1], sp[v][0][1] ) );
    u = sp[u][0][0];
    v = sp[v][0][0];
  }
  return res;
}
