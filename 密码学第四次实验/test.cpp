#include <iostream>  
#include <gmp.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cstring>  
  
using namespace std;  
  
int main(int argc,char **argv)  
{  
  
mpz_t begin, m1, m2;  
    int count;  
   
    //按照10进制初始化begin  
    mpz_init_set_str(begin, "170141183460469231731687303715884105728", 10);  
   
    count = (argc==1)?10:atoi(argv[1]);  
   
   
    while(count--) {  
        mpz_nextprime(begin, begin);  
        gmp_printf("%Zd\n", begin);  
    }  
   
    mpz_clear(begin);  
return 0;  
}  