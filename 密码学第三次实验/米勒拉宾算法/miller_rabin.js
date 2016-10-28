function mod_pro(a, b, n) {
  return a*b % n;
}

function mod(a, b, c) {
  if (b == 1)
    return a % c;
  a %= c;
  ret = 1;
  while (b) {
    if (b&1)
      ret = mod_pro(ret,a,c);
    a = mod_pro(a,a,c);
    b >>= 1;
  }
  return ret;
}

function check (a, n, m, k) {
    ret = mod(a, m, n);
    last = ret;
    for(var i = 0; i < k; i ++) {
      ret = mod_pro(ret, ret, n);
      if (ret == 1 && last != 1 && last != n-1)  
        return true;
      last = ret;
    }
    if (ret != 1)
      return true;
    return false;
}

function is_prime(n, t) {
  if (n < 2)
    return false;
  if (n == 2)
    return true;
  k = 0;
  m = n - 1;
  while(m&1 == 0) {
    m >>=1;
    k += 1;
  }
  for(var i = 0; i < t; i ++) {
    a = Math.random(0, n);
    if(check(a,n,m,k))
      return false;
  }
  return false;
}

function main() {
  var p ,q;
  while(1) {
    p = Math.random(Math.pow(2,100), Math.pow(2,101));
    if(is_prime(p,20)) {
      console.log(p);
      break;
    }
  }

  while(1) {
    q = Math.random(Math.pow(2,100), Math.pow(2,101));
    if(is_prime(q,20)) {
      console.log(q);
      break;
    }
  }
  console.log(q * p);
}

exports.default = main;



	
