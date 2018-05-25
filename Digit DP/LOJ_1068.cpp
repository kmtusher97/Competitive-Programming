#define MX_K 10002
 
int n, L, R, K, nm[12], ff[10][2][82][82];
 
void tostring( int x ) {
  n = 0;
  memset(nm, 0, sizeof nm);
  while( x>0 ) {
    nm[n++] = x%10, x /= 10;
  }
}
 
int dfs( int pos, int chk, int rmndr1, int rmndr2 ) {
  if( pos==n ) {
    return ( !rmndr1 && !rmndr2 ) ? 1 : 0;
  }
  int& ret = ff[pos][chk][rmndr1][rmndr2];
  if( ~ret ) return ret;
 
  ret = 0;
  if( chk ) {
    for(int dgt=0; dgt<=9; dgt++) {
      ret += dfs( pos+1, 1, (rmndr1*10+dgt)%K, (rmndr2+dgt)%K );
    }
  }
  else {
    for(int dgt=0; dgt<nm[n-pos-1]; dgt++) {
      ret += dfs( pos+1, 1, (rmndr1*10+dgt)%K, (rmndr2+dgt)%K );
    }
    ret += dfs( pos+1, 0, (rmndr1*10+nm[n-pos-1])%K, (rmndr2+nm[n-pos-1])%K );
  }
  return ff[pos][chk][rmndr1][rmndr2] = ret;
}
