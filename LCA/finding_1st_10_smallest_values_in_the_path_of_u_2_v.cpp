/**  ~* BISMILLAHIR RAHMANIR RAHIM *~  **/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const int MX = 100005, lg = 17;
int n, m, Q, L[MX], SP[lg+1][MX];
vi G[MX], V[lg+1][MX];

void dfs( int u ) /** to find level and 2^0th parent **/ 
{
  for(auto v : G[u])
  {
    if( !L[v] )
    {
      L[v] = L[u]+1, SP[0][v] = u;
      dfs( v );
    }
  }
}

void _merge( vi& v1, vi &v2 ) /** keeping only first 10 smallest node values **/
{
  for(auto i : v2)
  {
    v1.push_back(i);
  }
  sort(v1.begin(), v1.end());
  while( v1.size()>10 )
  {
    v1.pop_back();
  }
}

void build_sptbl() /** parent sparse table **/
{
  for(int i=1; i<=lg; i++)
  {
    for(int j=1; j<=n; j++)
    {
      SP[i][j] = SP[i-1][SP[i-1][j]];
      V[i][j] = V[i-1][j];
      _merge( V[i][j], V[i-1][SP[i-1][j]] ); 
    }
  }
}

vi query( int u, int v ) /// LCA
{
  vi ret;

  if( L[u]<L[v] ) swap(u, v);
  for(int i=lg; i>=0; i--)
  {
    if( L[SP[i][u]]>=L[v] )
    {
      _merge( ret, V[i][u] );
      u = SP[i][u];
    }
  }

  for(int i=lg; i>=0; i--)
  {
    if( SP[i][u]!=SP[i][v] )
    {
      _merge( ret, V[i][u] );
      _merge( ret, V[i][v] );
      u = SP[i][u], v = SP[i][v];
    }
  }

  if( u!=v ) /** *** */
  {
    _merge( ret, V[0][u] );
    _merge( ret, V[0][v] );
    u = SP[0][u], v = SP[0][v];
  }

  _merge( ret, V[0][u] );
  return ret;
}

int main()
{
  scanf("%d %d %d", &n, &m, &Q);
  for(int i=1, u, v; i<n; i++)
  {
    scanf("%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for(int i=1, a; i<=m; i++)
  {
    scanf("%d", &a);
    V[0][a].push_back(i);
  }
  for(int i=1; i<=n; i++)
  {
    vi dumy;
    _merge( V[0][i], dumy );
  }

  L[1] = 1;
  dfs( 1 );
  build_sptbl();

  while( Q-- )
  {
    int u, v, a;
    scanf("%d %d %d", &u, &v, &a);

    vi ans = query( u, v );
    int sz = min(a, (int)ans.size());
    printf("%d", sz);
    for(int i=0; i<sz; i++)
    {
      printf(" %d", ans[i]);
    }
    printf("\n");
  }

  return 0;
}
