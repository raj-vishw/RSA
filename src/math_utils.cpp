#include "../include/math_utils.h"

/*
 * Function: modExp
 * Description: Computes modular exponentiation efficiently: (base ^ exp) % mod.
 *              Instead of multiplying the base 'exp' times (which is too slow
 *              for huge RSA exponents), it uses the "Exponentiation by Squaring"
 *              method. It processes the exponent bit by bit, squaring the base
 *              and taking the modulo at each step to keep the numbers manageable.
 */

cpp_int modExp(cpp_int base , cpp_int exp, cpp_int mod){
    cpp_int result = 1;
    base %= mod;
    while(exp > 0){
        if(exp % 2 ==1 ){
            result = (result * base) % mod;
        }
        exp >>=1;
        base = (base * base) % mod;
    }
    return result;
}

/*
 * Function: gcd
 * Description: Computes the Greatest Common Divisor (GCD) of two numbers 'a' and 'b'.
 *              It utilizes the standard Euclidean algorithm, repeatedly replacing
 *              'a' with 'b' and 'b' with the remainder of 'a' divided by 'b',
 *              until 'b' becomes 0. The remaining non-zero value 'a' is the GCD.
 */

cpp_int gcd(cpp_int a, cpp_int b){
    while(b!=0){
        cpp_int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/*
 * Function: modInverse
 * Description: Computes the modular multiplicative inverse of 'e' modulo 'phi'.
 *              This is used to find the private key 'd' such that (d * e) % phi = 1.
 *              It implements the Extended Euclidean Algorithm (EEA), which not
 *              only finds the GCD but also the coefficients (Bézout coefficients)
 *              needed to express the GCD as a linear combination of 'e' and 'phi'.
 */
 
cpp_int modInverse(cpp_int e, cpp_int phi){
    cpp_int t = 0, new_t = 1;
    cpp_int r = phi, new_r = e;

    while(new_r != 0){
        cpp_int q = r / new_r;
        
        cpp_int temp = new_t;

        new_t = t - q * new_t;
        t = temp;

        temp = new_r;
        new_r = r - q * new_r;
        r = temp;
    }
    
    if(t < 0){
        t += phi;
    }
    return t;
}
