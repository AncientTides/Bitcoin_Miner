#include "include/bin_con.h"

// C++ program to find modular inverse of A under modulo M
// This program works only if M is prime.

BigInteger power(BigInteger x, BigInteger y, BigInteger M)// To compute x^y under modulo m
{
    if (y == 0)
        return 1;
    BigInteger p = power(x, y / 2, M) % M;
    p = (p * p) % M;
    return (y % 2 == 0) ? p : (x * p) % M;
}
 

BigInteger gcd(BigInteger a, BigInteger b)// Function to return gcd of a and b

{
    if (a == 0)
        return b;

    return gcd(b % a, a);
}


BigInteger modInverse(BigInteger A, BigInteger M)
{
    BigInteger g = gcd(A, M);

    if (g != 1)
        cout << "Inverse doesn't exist";
    else
    	return power(A, M - 2, M);
}
 


// Driver code
int main()
{
    BigInteger p = stringToBigInteger("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    BigInteger m = stringToBigInteger("112757557418114203588093402336452206775565751179231977388358956335153294300646");
    BigInteger A = String_2_BigInteger("324431234"), M = String_2_BigInteger("435423145243"), c;
    // Function call
    c = modInverse(m, p);
    cout << "Modular multiplicative inverse is " << c << "\n\n";

    return 0;
}
