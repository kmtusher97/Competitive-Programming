Preprocess:

void dfs(int v,int p = -1){
	if(par + 1)
		h[v] = h[p] + 1;
	par[v] = p;
	if(h[v] % SQRT == 0)
		r[v] = p;
	else
		r[v] = r[p];
	for(auto u : adj[v])	if(p - u)
		dfs(u,v);
}
Query:

int LCA(int v,int u){
	if(v == u)
		return v;
	if(h[v] < h[u])
		swap(v,u);
	if(h[v] == h[u])
		return (r[v] == r[u] ? LCA(par[v], par[u]) : LCA(r[v], r[u]));
	if(h[v] - h[u] < SQRT)
		return LCA(par[v], u);
	return LCA(r[v], u);
}
