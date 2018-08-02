/*  ~*BISMILLAHIR RAHMANIR RAHIM*~  */
#include <bits/stdc++.h>
using namespace std;
 
struct hvyLgtDcmpsn {
        static const int MX_N = 30005;
        int n, pos_base, chn_no, vlu[MX_N];
        int prnt[MX_N], big_child[MX_N], sz[MX_N], hgt[MX_N]; // tree
        int chn_ID[MX_N], chn_head[MX_N], chn_pos[MX_N]; //HLD
        int ara[MX_N], tree[MX_N * 4]; // segment tree
        vector<int> G[MX_N];
 
        void initialize( int _n ) {
          n = _n, pos_base = 0, chn_no = 1;
          for(int i = 0; i < MX_N; i++)
            G[i].clear(), prnt[i] = chn_head[i] = big_child[i] = -1;
          memset(tree, 0, sizeof tree);
        }
 
        void dfs( int u, int p ) {
          prnt[u] = p, sz[u] = 1;
          hgt[u] = hgt[p] + 1;
          int mx = -1;
 
          for(int i = 0; i < (int)G[u].size(); i++) {
            int v = G[u][i];
            if( v != p ) {
              dfs( v, u ), sz[u] += sz[v];
              if( sz[v] > mx )
                mx = sz[v], big_child[u] = v;
            }
          }
        }
 
        void decompose( int u, int p ) {
          chn_ID[u] = chn_no;
          chn_pos[u] = ++pos_base;
          ara[pos_base] = vlu[u];
          if( chn_head[chn_no] == -1 ) chn_head[chn_no] = u;
 
          if( ~big_child[u] )
            decompose( big_child[u], u );
 
          for(int i = 0; i < (int)G[u].size(); i++) {
            int v = G[u][i];
            if( v != p && v != big_child[u] )
              chn_no++, decompose( v, u );
          }
        }
 
        void build( int node, int lo, int hi ) {
          if( lo == hi ) {
            tree[node] = ara[lo];
            return;
          }
          int mid = lo + (hi - lo) / 2, lft = node << 1, rgt = lft | 1;
          build( lft, lo, mid );
          build( rgt, mid + 1, hi );
          tree[node] = tree[lft] + tree[rgt];
        }
 
        void update( int node, int lo, int hi, int pos, int v ) {
          if( lo == hi ) {
            tree[node] = v;
            return;
          }
          int mid = lo + (hi - lo) / 2, lft = node << 1, rgt = lft | 1;
          if( pos <= mid ) update( lft, lo, mid, pos, v );
          else update( rgt, mid + 1, hi, pos, v );
          tree[node] = tree[lft] + tree[rgt];
        }
 
        int query( int node, int lo, int hi, int L, int R ) {
          if( lo > R || hi < L ) return 0;
          if( lo >= L && hi <= R ) return tree[node];
          int mid = lo + (hi - lo) / 2, lft = node << 1, rgt = lft | 1;
          int pp = query( lft, lo, mid, L, R );
          int qq = query( rgt, mid + 1, hi, L, R );
          return pp + qq;
        }
 
        void updateHLD( int u, int x ) {
          update( 1, 1, pos_base, chn_pos[u], x );
        }
 
        int queryHLD( int u, int v ) {
          int ret = 0;
          while( chn_ID[u] != chn_ID[v] ) {
            int hu = chn_head[chn_ID[u]];
            int hv = chn_head[chn_ID[v]];
 
            if( hgt[hu] > hgt[hv] )
              ret += query( 1, 1, pos_base, chn_pos[hu], chn_pos[u] ), u = prnt[hu];
            else
              ret += query( 1, 1, pos_base, chn_pos[hv], chn_pos[v] ), v = prnt[hv];
          }
          int L, R;
          if( hgt[u] < hgt[v] ) L = chn_pos[u], R = chn_pos[v];
          else L = chn_pos[v], R = chn_pos[u];
          ret += query( 1, 1, pos_base, L, R );
          return ret;
        }
} hld;
 
int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    int n, Q;
    scanf("%d", &n);
    hld.initialize( n );
    for(int i = 1; i <= n; i++)
      scanf("%d", hld.vlu + i);
    for(int i = 1, u, v; i < n; i++) {
      scanf("%d %d", &u, &v), u++, v++;
      hld.G[u].push_back(v);
      hld.G[v].push_back(u);
    }
 
    hld.dfs( 1, 0 );
    hld.decompose( 1, 0 );
    hld.build( 1, 1, hld.pos_base );
 
    scanf("%d", &Q);
    printf("Case %d:\n", ++caseno);
    for(int i = 1, p, q, o; i <= Q; i++) {
      scanf("%d %d %d", &o, &p, &q);
      if( !o )
        printf("%d\n", hld.queryHLD( p + 1, q + 1 ));
      else
        hld.updateHLD( p + 1, q );
    }
  }
  return 0;
}
