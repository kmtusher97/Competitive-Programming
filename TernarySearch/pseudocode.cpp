ternarySearch( start, end ) :
    l = start
    r = end;

    for( i : 0 to 200 ) :
      l1 = ( l * 2 + r ) / 3
      l2 = ( l + 2 * r ) / 3
      // print l1, l2
      if( f( l1 ) > f( l2 ) ) 
        r = l2
      else 
        l = l1;
    end loop

    x = l
    return f(x)
//////////////////////////////////////////

ll solution() {
  int lo = x[1], hi = x[n];
  ll ret = 1e17;
  while( lo <= hi ) {
    int mid1 = lo + (hi - lo) / 3;
    int mid2 = mid1 + (hi - lo) / 3;
    ll fnL = find_cost( mid1 );
    ll fnR = find_cost( mid2 );
    ret = min(ret, min(fnL, fnR));
    if( fnL < fnR )
      hi = mid2 - 1;
    else 
      lo = mid1 + 1;
  }
  return ret;
}
