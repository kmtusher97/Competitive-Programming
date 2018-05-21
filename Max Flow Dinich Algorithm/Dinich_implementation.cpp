struct dinic_maxFlow
{
        static const int MX_N = 105;
        int nodes, src, snk, dist[MX_N], start[MX_N];

        struct Edge
        {
            int nxt, flw, cap, rev;
        };
        vector<Edge> G[MX_N];

        void initialize( int _n )
        {
            nodes = _n;
            for(int i=0; i<=nodes; i++) G[i].clear();
        }

        void addEdge( int u, int v, int w )
        {
            Edge p = { v, 0, w, (int)G[v].size() };
            Edge q = { u, 0, w, (int)G[u].size() };
            G[u].push_back(p);
            G[v].push_back(q);
        }

        bool bfs() //for finding augmenting path
        {
            for(int i=0; i<=nodes; i++) dist[i] = -1;
            queue<int> Q; Q.push( src ), dist[src] = 0;

            while( !Q.empty() )
            {
                int u = Q.front(); Q.pop();
                for(int i=0; i<(int)G[u].size(); i++)
                {
                    Edge& e = G[u][i];
                    int v = e.nxt;
                    if( dist[v]==-1 && e.flw<e.cap )
                    {
                        dist[v] = dist[u] + 1;
                        Q.push(v);
                    }
                }
            }
            return ~dist[snk];
        }

        int dfs( int u, int flow ) //for findig flow 
        {
            if( u==snk ) return flow;

            for(int i=start[u], sz=G[u].size(); i<sz; i++)
            {
                Edge& e = G[u][i];
                if( e.flw>=e.cap ) continue;

                int v = e.nxt;
                if( dist[v]==dist[u] + 1 )
                {
                    int f = dfs( v, min(flow, e.cap-e.flw) );
                    if( f>0 )
                    {
                        e.flw += f;
                        G[v][e.rev].flw -= f;
                        return f;
                    }
                }
            }
            return 0;
        }

        int maxFlow( int _src, int _snk )
        {
            src = _src, snk = _snk;
            int ret = 0;

            while( bfs() )
            {
                for(int i=0; i<=nodes; i++) start[i] = 0;
                while( int tmp = dfs( src, INT_MAX ) )
                    ret += tmp;
            }
            return ret;
        }
} FLOW;
