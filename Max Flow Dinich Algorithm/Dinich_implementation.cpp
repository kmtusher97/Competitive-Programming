#define MX_N 5003
typedef long long intl;
const intl inf = 1e12;

struct MaxFlow_Dinich
{
    int nodes, src, snk, dist[MX_N], start[MX_N];
    struct Edge
    {
        int nxt, f, cap, rev;
    };
    vector<Edge> G[MX_N];

    void initialize( int _n )
    {
        nodes = _n;
        for(int i=0; i<=_n; i++)
            G[i].clear();
    }

    void addEdge( int u, int v, int w )
    {
        Edge p = { v, 0, w, (int)G[v].size() };
        Edge q = { u, 0, w, (int)G[u].size() };
        G[u].push_back(p);
        G[v].push_back(q);
    }

    bool bfs()
    {
        memset(dist, -1, sizeof dist);
        queue<int> Q;
        Q.push(src), dist[src] = 0;

        while( !Q.empty() )
        {
            int u = Q.front();
            Q.pop();
            for(int i=0; i<(int)G[u].size(); i++)
            {
                Edge& e = G[u][i];
                int v = e.nxt;
                if( ~dist[v] || e.f>=e.cap )
                    continue;
                dist[v] = dist[u]+1;
                Q.push(v);
            }
        }
        return ~dist[snk];
    }

    intl dfs( int u, intl flw )
    {
        if( u==snk )
            return flw;

        for(int& i=start[u]; i<(int)G[u].size(); i++)
        {
            Edge& e = G[u][i];
            if( e.f>=e.cap )
                continue;
            int v = e.nxt;
            if( dist[v]==dist[u]+1 )
            {
                intl _f = dfs( v, min(flw, (intl)(e.cap-e.f)) );
                if( _f )
                {
                    e.f += _f;
                    G[v][e.rev].f -= _f;
                    return _f;
                }
            }
        }
        return 0LL;
    }

    intl maxFlow( int _s, int _t )
    {
        src = _s, snk = _t;
        intl ret = 0;

        while( bfs() )
        {
            memset(start, 0, sizeof start);
            while( intl tmp = dfs( src, inf ) )
                ret += tmp;
        }
        return ret;
    }
} FLOW;
