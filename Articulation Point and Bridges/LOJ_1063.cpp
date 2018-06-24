/*  ~*BISMILLAHIR RAHMANIR RAHIM*~  */

#include <bits/stdc++.h>
using namespace std;

#define MX_N 10002
int n, m;
static int clk, root;
int dfs_num[MX_N], dfs_low[MX_N], child_cnt[MX_N], parent[MX_N];
bool articulation_vertex[MX_N];
vector<int> G[MX_N];

void articulationPointandBridge( int u ) {
  dfs_low[u] = dfs_num[u] = ++clk, child_cnt[u] = 0;
  for(int i=0, sz=G[u].size(); i<sz; i++) {
    int v = G[u][i];
    if( !dfs_num[v] ) {
      parent[v] = u, child_cnt[u]++;
      articulationPointandBridge( v );

      if( dfs_low[v]>=dfs_num[u] ) articulation_vertex[u] = true;
//      if (dfs_low[v]>dfs_num[u])
//        printf(" Edge (%d, %d) is a bridge\n", u, v);
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    else if( v!=parent[u] )
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);
  }
}

void reset() {
  clk = 0;
  for(int i=0; i<MX_N; i++) {
    dfs_low[i] = dfs_num[i] = 0;
    parent[i] = articulation_vertex[i] = 0;
    G[i].clear();
  }
}

int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    scanf("%d %d", &n, &m);
    reset();
    for(int i=0, u, v; i<m; i++) {
      scanf("%d %d", &u, &v);
      G[u].push_back(v);
      G[v].push_back(u);
    }
    int res = 0;
    root = 1,
    articulationPointandBridge( root );
    articulation_vertex[root] = (child_cnt[root]>1);
    for(int i=1; i<=n; i++)
      if( articulation_vertex[i] ) res++;
    printf("Case %d: %d\n", ++caseno, res);
  }
  return 0;
}


