#define MX_N 10005
static int clk;
int n, m, dfs_num[MX_N], dfs_low[MX_N], SCC[MX_N], dgree[MX_N];
bool visited[MX_N];
vector<int> G[MX_N], S, R;

void tarjanSCC( int u, int p ) {
  dfs_low[u] = dfs_num[u] = ++clk;
  S.push_back(u);
  visited[u] = true;
  for(int i = 0; i < (int)G[u].size(); i++) {
    int v = G[u][i];
    if( !dfs_num[v] )
      tarjanSCC( v, u ), dfs_low[u] = min( dfs_low[u], dfs_low[v] );
    if( visited[v] && v != p )
      dfs_low[u] = min( dfs_low[u], dfs_num[v] );
  }
  if( dfs_low[u] == dfs_num[u] ) {
    while( true ) {
      int v = S.back(); S.pop_back();
      visited[v] = false;
      SCC[v] = u;
      if( u == v ) break;
    }
    R.push_back(u);
  }
}

/// inside main()
clk = 0, S.clear(), R.clear();
for(int i = 1; i <= n; i++)
  if( !dfs_num[i] ) tarjanSCC( i, 0 );

    
