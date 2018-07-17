/*  ~*BISMILLAHIR RAHMARNIR RAHIM *~  */
#include <bits/stdc++.h>
using namespace std;

#define inf 112345
#define MX 102
static int nd;
int N, ttl, info[MX][6];
double D;

double Distance( int x1, int y1, int x2, int y2 ) {
  return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

struct dinich_MaxFlow {
        static const int MX_N = 202;
        int nodes, src, snk, dist[MX_N], start[MX_N];
        struct Edge { int frm, to, flw, cap; };
        vector<Edge> E;
        vector<int> G[MX_N];

        void initialize( int _n ) {
          nodes = _n, E.clear();
          for(int i=0; i<=nodes; i++) G[i].clear();
        }

        void Clear() {
          for(int i=0; i<(int)E.size(); i++) E[i].flw = 0;
        }

        void addEdge( int u, int v, int w ) {
          Edge p = { u, v, 0, w };
          Edge q = { v, u, 0, 0 };
          G[u].push_back( (int)E.size() ), E.push_back(p);
          G[v].push_back( (int)E.size() ), E.push_back(q);
        }

        bool bfs() {
          memset(dist, -1, sizeof dist);
          queue<int> Q; Q.push(src), dist[src] = 0;

          while( !Q.empty() ) {
            int u = Q.front(); Q.pop();
            for(int j=0; j<(int)G[u].size(); j++) {
              int id = G[u][j];
              int v = E[id].to;
              if( ~dist[v] || E[id].flw==E[id].cap ) continue;
              dist[v] = dist[u]+1, Q.push(v);
            }
          }
          return ~dist[snk];
        }

        int dfs( int u, int flow ) {
          if( !flow ) return 0;
          if( u==snk ) return flow;
          for(; start[u]<(int)G[u].size(); ++start[u]) {
            int id = G[u][start[u]];
            int v = E[id].to;
            if( dist[v]!=dist[u]+1 ) continue;
            int df = dfs( v, min(flow, E[id].cap-E[id].flw) );
            if( df>0 ) {
              E[id].flw += df;
              E[id^1].flw -= df;
              return df;
            }
          }
          return 0;
        }

        int maxFlow( int _s, int _t ) {
          int ret = 0;
          Clear();
          src = _s, snk = _t;
          while( bfs() ) {
            memset(start, 0, sizeof start);
            while( int tmp = dfs( src, inf ) ) ret += tmp;
          }
          return ret;
        }
} MF;

int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    scanf("%d %lf", &N, &D), ttl = nd = 0;
    MF.initialize( N*2 );
    for(int i=1; i<=N; i++) {
      for(int j=0; j<4; j++) scanf("%d", &info[i][j]);
      ttl += info[i][2];
      info[i][4] = ++nd; //node split
      info[i][5] = ++nd;
      MF.addEdge( info[i][4], info[i][5], info[i][3] );
    }

    int source = 0;
    for(int i=1; i<=N; i++) {
      MF.addEdge( source, info[i][4], info[i][2] );
    }

    for(int i=1; i<=N; i++) {
      for(int j=i+1; j<=N; j++) {
        double dis = Distance( info[i][0], info[i][1], info[j][0], info[j][1] );
        if( dis>D ) continue;
        MF.addEdge( info[i][5], info[j][4], inf );
        MF.addEdge( info[j][5], info[i][4], inf );
      }
    }

    vector<int> res;
    for(int i=1, flw; i<=N; i++) {
      flw = MF.maxFlow( source, info[i][4] );
      if( flw==ttl ) {
        res.push_back(i-1);
      }
    }

    printf("Case %d: ", ++caseno);
    if( !res.size() ) printf("-1\n");
    else {
      printf("%d", res[0]);
      for(int i=1; i<res.size(); i++) printf(" %d", res[i]);
      printf("\n");
    }
  }
  return 0;
}
