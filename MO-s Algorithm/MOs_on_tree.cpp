#include <bits/stdc++.h>
using namespace std;

#define sc scanf
#define pf printf
#define pb push_back
#define mk_pr make_pair

typedef long long intl;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MX = 100005;
int n, seg_sz, mxf, clr[MX], dpth[MX][2], ordr[MX], frq[MX];
intl ff[MX], ans[MX];
bool vis[MX];
static int clk;
vi g[MX];

class _node {
public:
  int lft, rgt, id, seg_no;

  void inpt( int nd ) {
    lft = dpth[nd][0], rgt = dpth[nd][1];
    id = nd, seg_no = lft/seg_sz + ( (lft%seg_sz) ? 1 : 0 );
  }

  bool operator < ( _node p ) const {
    if( seg_no!=p.seg_no ) return ( seg_no<p.seg_no );
    if( rgt!=p.rgt ) return ( rgt<p.rgt );
    return ( lft<p.lft );
  }
} qq[MX];

void dfs( int u ) {
  dpth[u][0] = ++clk;
  ordr[clk] = u, vis[u] = true;

  for(int i=0, sz=g[u].size(); i<sz; i++) {
    int v = g[u][i];
    if( !vis[v] ) dfs( v );
  }

  dpth[u][1] = clk;
}

void addition( int st, int ed ) {
  for(int i=st; i<=ed; i++) {
    ff[frq[clr[ordr[i]]]] -= clr[ordr[i]];
    mxf = max(mxf, ++frq[clr[ordr[i]]]);
    ff[frq[clr[ordr[i]]]] += clr[ordr[i]];
  }
}

void subtract( int st, int ed ) {
  for(int i=st; i<=ed; i++) {
    ff[frq[clr[ordr[i]]]] -= clr[ordr[i]];
    if( mxf==frq[clr[ordr[i]]] && ff[frq[clr[ordr[i]]]]==0 ) mxf--;
    --frq[clr[ordr[i]]];
    ff[frq[clr[ordr[i]]]] += clr[ordr[i]];
  }
}

void solution() {
  mxf = -1;
  int pre_lft, pre_rgt, cur_lft, cur_rgt;
  for(int i=1; i<=n; i++) {
    cur_lft = qq[i].lft, cur_rgt = qq[i].rgt;
    if( i==1 ) {
      addition( cur_lft, cur_rgt );
    }
    else {
      if( pre_lft>cur_lft ) addition( cur_lft, pre_lft-1 );
      else subtract( pre_lft, cur_lft-1 );

      if( pre_rgt>cur_rgt ) subtract( cur_rgt+1, pre_rgt );
      else addition( pre_rgt+1, cur_rgt );
    }
    ans[qq[i].id] = ff[mxf];
    pre_lft = cur_lft, pre_rgt = cur_rgt;
  }
}

int main() {
  sc("%d", &n);
  for(int i=1; i<=n; i++) {
    sc("%d", clr+i);
  }
  for(int i=1, a, b; i<n; i++) {
    sc("%d %d", &a, &b);
    g[a].pb(b), g[b].pb(a);
  }

  clk = 0;
  dfs( 1 );
  seg_sz = max(1, (int)sqrt(n));
  for(int i=1; i<=n; i++) {
    qq[i].inpt( i );
  }

  sort( qq+1, qq+n+1 );
  solution();

  for(int i=1; i<=n; i++) {
    pf("%lld", ans[i]);
    (i==n) ? pf("\n") : pf(" ");
  }

  return 0;
}
