struct Suffix_Array {
        static const int MX_N = 112345;
        char T[MX_N];
        int N, c[MX_N];
        int RA[MX_N], tempRA[MX_N];
        int SA[MX_N], tempSA[MX_N];
 
        int Phi[MX_N], PLCP[MX_N], LCP[MX_N]; // for computing LCP
 
        void initialize( char* t ) {
          N = strlen(t);
          for(int i=0; i<N; i++) T[i] = t[i];
          T[N++] = '#';
        }
 
        void countingSort( int k ) {
          memset(c, 0, sizeof c);
          for(int i=0; i<N; i++) c[i+k<N ? RA[i+k] : 0]++;
          for(int i=0, sum=0; i<max(300, N); i++) {
            int t = c[i]; c[i] = sum, sum += t;
          }
          for(int i=0; i<N; i++) {
            tempSA[c[SA[i]+k<N ? RA[SA[i]+k] : 0]++] = SA[i];
          }
          for(int i=0; i<N; i++) SA[i] = tempSA[i];
        }
 
        void constructSA() {
          for(int i=0; i<N; i++) RA[i] = T[i];
          for(int i=0; i<N; i++) SA[i] = i;
          for(int k=1, r; k<N; k<<=1) {
            countingSort( k );
            countingSort( 0 );
            tempRA[SA[0]] = r = 0;
            for(int i=1; i<N; i++) {
              tempRA[SA[i]] = ( RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k] ) ? r : ++r;
            }
            for(int i=0; i<N; i++) RA[i] = tempRA[i];
            if( RA[SA[N-1]]==N-1 ) break;
          }
        }
 
        void computeLCP() {
          Phi[SA[0]] = -1;
          for(int i=1; i<N; i++) Phi[SA[i]] = SA[i-1];
          for(int i=0, L=0; i<N; i++) {
            if( Phi[i]==-1 ) {
              PLCP[i] = 0; continue;
            }
            while( T[i+L]==T[Phi[i]+L] ) L++;
            PLCP[i] = L;
            L = max(L-1, 0);
          }
          for(int i=0; i<N; i++) LCP[i] = PLCP[SA[i]];
        }
 
        void print() {
          for(int i=0; i<N; i++) printf("%2d\t%s\n", SA[i], T + SA[i]);
          for(int i=0; i<N; i++) printf("%2d\t%d\n", SA[i], LCP[i]);
        }
} sa;


////////////////////////////////////////////////////////////
// substring match (felix halim book)
ii stringMatching()
{
    // string matching in O(m log n)
    int lo = 0, hi = n-1, mid = lo;
    // valid matching = [0..n-1]
    while (lo < hi)
    {
        // find lower bound
        mid = (lo + hi) / 2;
        // this is round down
        int res = strncmp(T + SA[mid], P, m); // try to find P in suffix ’mid’
        if (res >= 0) hi = mid;
        // prune upper half (notice the >= sign)
        else
            lo = mid + 1;
        // prune lower half including mid
    }
    // observe ‘=’ in "res >= 0" above
    if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1);
    // if not found
    ii ans;
    ans.first = lo;
    lo = 0;
    hi = n - 1;
    mid = lo;
    while (lo < hi)
    {
        // if lower bound is found, find upper bound
        mid = (lo + hi) / 2;
        int res = strncmp(T + SA[mid], P, m);
        if (res > 0) hi = mid;
        // prune upper half
        else
            lo = mid + 1;
        // prune lower half including mid
    }
    // (notice the selected branch when res == 0)
    if (strncmp(T + SA[hi], P, m) != 0) hi--;
    // special case
    ans.second = hi;
    return ans;
} // return lower/upperbound as first/second item of the pair, respectively
int main()
{
    n = (int)strlen(gets(T));
// input T as per normal, without the ‘$’
    T[n++] = ’$’;
// add terminating character
    constructSA();
    for (int i = 0; i < n; i++) printf("%2d\t%s\n", SA[i], T + SA[i]);
    while (m = (int)strlen(gets(P)), m)
    {
// stop if P is an empty string
        ii pos = stringMatching();
        if (pos.first != -1 && pos.second != -1)
        {
            printf("%s found, SA [%d..%d] of %s\n", P, pos.first, pos.second, T);
            printf("They are:\n");
            for (int i = pos.first; i <= pos.second; i++)
                printf(" %s\n", T + SA[i]);
        }
        else printf("%s is not found in %s\n", P, T);
    }
} // return 0;
