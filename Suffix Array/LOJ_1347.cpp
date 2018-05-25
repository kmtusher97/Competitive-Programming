/*  ~*BISMILLAHIR RAHMANIR RAHIM*~  */
 
#include <bits/stdc++.h>
using namespace std;
 
#define MX_N 15123
 
char s[MX_N], t[MX_N];
 
struct Suffix_Array {
        char T[MX_N];
        int n, c[MX_N];
        int SA[MX_N], tempSA[MX_N];
        int RA[MX_N], tempRA[MX_N];
 
        int Phi[MX_N], PLCP[MX_N], LCP[MX_N];
 
        void initialize( char* t ) {
          n = strlen(t);
          for(int i=0; i<n; i++) T[i] = t[i];
          T[n++] = '%';
        }
 
        void countingSort( int k ) {
          memset(c, 0, sizeof c);
          for(int i=0; i<n; i++) c[i+k<n ? RA[i+k] : 0]++;
          for(int i=0, sum=0, t; i<max(300, n); i++)
            t = c[i], c[i] = sum, sum += t;
          for(int i=0; i<n; i++)
            tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
          for(int i=0; i<n; i++) SA[i] = tempSA[i];
        }
 
        void constructSA() {
          for(int i=0; i<n; i++)
            RA[i] = T[i], SA[i] = i;
          for(int k=1, r; k<n; k<<=1) {
            countingSort( k );
            countingSort( 0 );
            tempRA[SA[0]] = r = 0;
            for(int i=1; i<n; i++)
              tempRA[SA[i]] = ( RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k] ) ? r : ++r;
            for(int i=0; i<n; i++) RA[i] = tempRA[i];
            if( RA[SA[n-1]]==n-1 ) break;
          }
        }
 
        void computeLCP() {
          Phi[SA[0]] = -1;
          for(int i=1; i<n; i++) Phi[SA[i]] = SA[i-1];
          for(int i=0, L=0; i<n; i++) {
            if( Phi[i]==-1 ) {
              PLCP[i] = 0; continue;
            }
            while( T[i+L]==T[Phi[i]+L] ) L++;
            PLCP[i] = L;
            L = max(0, L-1);
          }
          for(int i=0; i<n; i++) LCP[i] = PLCP[SA[i]];
        }
 
        void print() {
          for(int i=0; i<n; i++) printf("%2d \t %s\n", SA[i], T+SA[i]);
          for(int i=0; i<n; i++) printf("%2d \t %d\n", SA[i], LCP[i]);
        }
 
        /*--------------------------------------------------*/
        int findID( int x, int* a ) {
          if( x>=a[2] ) return 3;
          if( x>=a[1] ) return 2;
          return 1;
        }
        void solve( int& ret, int* a ) {
          int b[3];
          for(int i=2; i<n; i++) {
            b[0] = SA[i-2], b[1] = SA[i-1], b[2] = SA[i];
            sort(b, b+3);
            int x = findID( b[0], a );
            int y = findID( b[1], a );
            int z = findID( b[2], a );
 
            if( x==y || y==z || x==z ) continue;
            ret = max(ret, min(LCP[i], LCP[i-1]));
          }
        }
        /*--------------------------------------------------*/
} SA;
 
int main() {
  int cases, caseno = 0;
  scanf("%d", &cases);
  while( cases-- ) {
    int a[4];
    t[0] = '\0', a[0]=0;
    for(int i=0; i<3; i++) {
      scanf("%s", s);
      strcat(t, s);
      if( i==0 ) strcat(t, "#");
      else if( i==1 ) strcat(t, "$");
      a[i+1] = strlen(t);
    }
 
    SA.initialize( t );
    SA.constructSA();
    SA.computeLCP();
 
    int res = 0;
    SA.solve( res, a );
    printf("Case %d: %d\n", ++caseno, res);
  }
  return 0;
}
