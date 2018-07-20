#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define pbk pop_back
#define mk_pr make_pair

typedef long long intl;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<string> vss;
typedef queue<int> qi;

#define read freopen("INPUT.txt", "r", stdin)
#define write freopen("OUTPUT.txt", "w", stdout)
#define FasterIO ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int MX = 200010;
int n, Q, bckt_sz, a[MX], cnt[MX*10], ans[MX];

class qury_node {
public:
  int l, r, id, bckt_id;

  qury_node() : l(0), r(0), id(0), bckt_id(0) { }

  void getdata( int i ) {
    scanf("%d %d", &l, &r);
    id = i;
    bckt_id = l/bckt_sz;
    if( l%bckt_sz ) bckt_id++;
  }

  bool operator < ( qury_node p ) const {
    if( bckt_id!=p.bckt_id ) return ( bckt_id<p.bckt_id );
    if( r!=p.r ) return ( r<p.r );
    else return ( l<p.l );
  }
} qry[MX];

void addition( int st, int ed, int ii ) {
  for(int i=st; i<=ed; i++) {
    cnt[a[i]]++;
    if( cnt[a[i]]==1 ) ans[qry[ii].id]++;
  }
}

void subtract( int st, int ed, int ii ) {
  for(int i=st; i<=ed; i++) {
    if( cnt[a[i]]==1 ) ans[qry[ii].id]--;
    cnt[a[i]]--;
  }
}

int main() {
  /// read, write;
  ///FasterIO
  scanf("%d", &n);
  bckt_sz = sqrt(n);
  if( bckt_sz==0 ) bckt_sz = 1;
  for(int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }
  scanf("%d", &Q);
  for(int i=1; i<=Q; i++) {
    qry[i].getdata( i );
  }

  sort(qry+1, qry+Q+1);
  memset(cnt, 0, sizeof cnt);

  addition( qry[1].l, qry[1].r, 1 );
  int pre_l = qry[1].l, pre_r = qry[1].r, pre_bckt = qry[1].bckt_id;

  for(int i=2; i<=Q; i++) {
    ans[qry[i].id] = ans[qry[i-1].id];

    if( qry[i].bckt_id!=pre_bckt ) {
      subtract( pre_l, qry[i].l-1, i );

      if( pre_r>qry[i].r ) {
        subtract( qry[i].r+1, pre_r, i );
      }
      else {
        addition( pre_r+1, qry[i].r, i );
      }
    }
    else {
      if( pre_l>qry[i].l ) {
        addition( qry[i].l, pre_l-1, i );
      }
      else {
        subtract( pre_l, qry[i].l-1, i );
      }
      addition( pre_r+1, qry[i].r, i );
    }

    pre_l = qry[i].l, pre_r = qry[i].r, pre_bckt = qry[i].bckt_id;
  }

  for(int i=1; i<=Q; i++) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
