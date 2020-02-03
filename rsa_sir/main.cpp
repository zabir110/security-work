#include <iostream>
/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <assert.h>
*/
#include<bits/stdc++.h>
#include <gmp.h>
using namespace std;

int main()
{

    int PRIMESIZE;
    mpz_t p;
    mpz_init(p);
    mpz_t q;
    mpz_init(q);
    mpz_t n;
    mpz_init(n);
    mpz_set_ui(n,0);
    mpz_t d;
    mpz_init(d);
    mpz_t e;
    mpz_init(e);
    mpz_t phi;
    mpz_init(phi);
    mpz_t tmp1;
    mpz_init(tmp1);
    mpz_t tmp2;
    mpz_init(tmp2);
    mpz_t msg;
    mpz_init(msg);
    mpz_t cip;
    mpz_init(cip);
    mpz_t dcr;
    mpz_init(dcr);

    cout<<"Enter No of bits for P and Q: ";
    cin>>PRIMESIZE;


    //P Q
    char* p_str = new char[PRIMESIZE+1];
    char* q_str = new char[PRIMESIZE+1];

    while(1)
    {
        p_str[0] = '1';
        q_str[0] = '1';


        for(int i=1; i<PRIMESIZE; i++)
        {
            p_str[i] = char((rand()%2)+48);
        }
        for(int i=1; i<PRIMESIZE; i++)
        {
            q_str[i] = char((rand()%2)+48);
        }

        p_str[PRIMESIZE] = '\0';
        q_str[PRIMESIZE] = '\0';


        mpz_set_str(p,p_str,2);
        mpz_set_str(q,q_str,2);

        mpz_nextprime(p,p);
        mpz_nextprime(q,q);

        if(mpz_cmp(p, q) != 0)
        {
            break;
        }

    }

    //P Q

    cout << endl << "p = ";
    mpz_out_str(stdout,10,p);

    cout << endl << "q = ";
    mpz_out_str(stdout,10,q);
    cout << endl;

    //calculate n = p * q
    mpz_mul(n, p, q);
    cout << "n = ";
    mpz_out_str(stdout,10,n);
    cout << endl;

    // calculate phi(n) = (p - 1) * (q - 1)
    mpz_sub_ui(tmp1, p, 1);
    mpz_sub_ui(tmp2, q, 1);
    mpz_mul(phi, tmp1, tmp2);
    cout << "phi = ";
    mpz_out_str(stdout,10,phi);
    cout << endl;

    //select an integer e such that 1 < e < phi(n)
    mpz_init_set_ui(e, 3);
    //assert(mpz_cmp_ui(e, 1) > 0);
    //assert(mpz_cmp_ui(phi, e) > 0);

    while(1)
    {
        mpz_gcd(tmp1, e, phi);
        if(! mpz_cmp_ui(tmp1, 1))
        {
            break;
        }
        mpz_nextprime(e,e);

    }

    cout << "e = ";
    mpz_out_str(stdout,10,e);
    cout << endl;

    // gcd(e, phi) must be 1


    //calculate d ...
    mpz_invert(d, e, phi);
    cout << "d = ";
    mpz_out_str(stdout,10,d);
    cout << endl;

    // e * d mod phi == 1
    mpz_mul(tmp1, e, d);
    mpz_mod(tmp2, tmp1, phi);
    assert(mpz_cmp_ui(tmp2, 1) == 0);

    // encrypt a message

    mpz_set_ui(msg, 89);
    mpz_powm(cip, msg, e, n);

    //decrypt a message

    mpz_powm(dcr, cip, d, n);

    cout << endl;
    cout << "Original message: ";
    mpz_out_str(stdout,10,msg);
    cout << endl;
    cout << "encrypted message: ";
    mpz_out_str(stdout,10,cip);
    cout << endl;
    cout << "decrypted message: ";
    mpz_out_str(stdout,10,dcr);
    cout << endl;

    return 0;
}
