/**  ~*BISMILLAHIR RAHMANIR RAHIM*~  **/

#include <bits/stdc++.h>

using namespace std;

typedef long long intl;

const int MX = 4123456;
int n, A[MX], trie[MX][2][2];
static int nd = 1;

void Insert( intl x ) /** inserting into TRIE **/
{
  bitset<32> mask(x);

  for(int i=31, cur=1; i>=0; i--)
  {
    if( !trie[cur][mask[i]][0] ) trie[cur][mask[i]][0] = ++nd;
    cur = trie[cur][mask[i]][0], trie[cur][mask[i]][1]++;
  }
}

intl Query( intl x ) /** find min, *a path can be used at most once **/
{
  bitset<32> mask(x);
  intl res = 0LL;

  for(int i=31, cur=1; i>=0; i--)
  {
    if( trie[cur][mask[i]][0] && trie[trie[cur][mask[i]][0]][mask[i]][1] )
    {
      cur = trie[cur][mask[i]][0];
      trie[cur][mask[i]][1]--;
    }
    else
    {
      cur = trie[cur][!mask[i]][0];
      trie[cur][!mask[i]][1]--;
      res += (1LL<<i);
    }
  }
  return res;
}

int main()
{
  ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  cin>>n;
  for(int i=0; i<n; i++) cin>>A[i];
  for(int i=0, B; i<n; i++)
  {
    cin>>B;
    Insert( B );
  }
  for(int i=0; i<n; i++)
  {
    intl res = Query( A[i] );
    cout<<res<<" ";
  }
  cout<<endl;
  return 0;
}
