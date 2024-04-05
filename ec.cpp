#include "include/bin_con.h"
// using namespace std;

vector<BigInteger> extended_euclid_gcd(BigInteger a, BigInteger b) {
    // Returns a vector `result` of size 3 where:
    // Referring to the equation ax + by = gcd(a, b)
    //     result[0] is gcd(a, b)
    //     result[1] is x
    //     result[2] is y 
    
    BigInteger s = 0; BigInteger old_s = 1;
    BigInteger t = 1; BigInteger old_t = 0;
    BigInteger r = b; BigInteger old_r = a;

    while(r != 0)
    {
        BigInteger quotient = old_r/r;
        // We are overriding the value of r, before that we store it's current
        // value in temp variable, later we assign it to old_r
        BigInteger temp = r;
        r = old_r - quotient*r;
        old_r = temp;

        // We treat s and t in the same manner we treated r
        temp = s;
        s = old_s - quotient*s;
        old_s = temp;

        temp = t;
        t = old_t - quotient*t;
        old_t = temp;
    }
    vector<BigInteger> result;
    result.push_back(old_r);
    result.push_back(old_s);
    result.push_back(old_t);
    return result;
}

BigInteger modulo_multiplicative_inverse(BigInteger A, BigInteger M) {
    // Assumes that A and M are co-prime
    // Returns multiplicative modulo inverse of A under M
    
    // Find gcd using Extended Euclid's Algorithm
    vector<BigInteger> v = extended_euclid_gcd(A, M);
    BigInteger gcd = v[0];
    BigInteger x = v[1];
    BigInteger y = v[2]; // We don't really need this though

    // In case x is negative, we handle it by adding extra M
    // Because we know that multiplicative inverse of A in range M lies
    // in the range [0, M-1]
    if(x < 0) {
        x += M;
    }
    
    return x;
}


BigInteger Inverse(BigInteger a, BigInteger m)
{
    BigInteger prevy(0), y(1), q, m_orig = m, der(0);
    // m = p;
    if (a < 0)
        a = a % m;

    while(a > 1) 
    {
        q = m/a;
        y = (prevy-q)*y;
        prevy = y;
        a = m % a;
        m = a;
    }
    der = y % m_orig;
    return der;
}






// Returns modulo inverse of a with respect to m using extended Euclid Algorithm 
// Assumption: a and m are coprimes, i.e.,  gcd(a, m) = 1 
BigInteger modInverse(BigInteger a, BigInteger m) 
{ 
    BigInteger m0 = m; 
    BigInteger y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        BigInteger q = a / m; // q is quotient 
        BigInteger t = m; 
        m = a % m, a = t; // m is remainder now, process same as Euclid's algo 
        t = y; 
        // Update y and x 
        y = x - q * y; 
        x = t; 
    } 
  
    // Make x positive 
    if (x < 0) 
       x += m0;

    // return x%m0;
    return x;
} 
  





int main()
{
    BigInteger m, a, j, w;
    BigInteger p = stringToBigInteger("115792089237316195423570985008687907853269984665640564039457584007908834671663"); // module factor on curve point
    m = stringToBigInteger("112757557418114203588093402336452206775565751179231977388358956335153294300646");
    a = modulo_multiplicative_inverse(m, p);
    w = Inverse(m, p);
    j = modInverse(m,p);

    cout << m << " % " << p << " = " << a << "\tmodulo_multiplicative_inverse()\n\n\n";
    cout << m << " % " << p << " = " << w << "\tInverse()\n\n\n";
    cout << m << " % " << p << " = " << j << "\tmodInverse()\n\n\n";
    


    BigInteger z, pk, k, s, r, v;
    z = String_2_BigInteger("75402077471587956851360588120356244127735644006942973877340910814730793844683");
    pk = String_2_BigInteger("112757557418114203588093402336452206775565751179231977388358956335153294300646");
    k = String_2_BigInteger("123456789");
    r = String_2_BigInteger("4051293998585674784991639592782214972820158391371785981004352359465450369227");
    // s = (z + (r * pk));
    // cout << "s = " << s << "\n";
    // v = modInverse(k, p);
    // cout << "v = " << v << "\n";
    // s = v * s;

    s = Inverse(k, p) * (z + r * pk);
    cout <<"Signature y point = " << s << "\n\n";

    // cout <<  modulo_multiplicative_inverse(5, 11) << endl;
    // // Output: 9 (Because 5*9 % 11 => 45 % 11 = 1)
    // cout <<  modulo_multiplicative_inverse(3, 8) << endl;
    // // Output: 3 (Because 3*3 % 8 => 9 % 8 = 1)
    // cout <<  modulo_multiplicative_inverse(23, 1000000007) << endl;
    // Output: 739130440 (Because 739130440*23 = 17000000120 and 17000000120 % 1000000007 is 1)
    return 0;
}