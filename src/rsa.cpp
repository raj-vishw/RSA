#include "../include/rsa.h"
#include "../include/math_utils.h"
#include "../include/prime_utils.h"

/*
 * Function: generateKeys
 * Description: Generates a complete RSA key pair (public and private keys).
 *              It takes the desired bit length for the prime numbers as input.
 *              The steps are:
 *              1. Generate two large, distinct prime numbers, p and q.
 *              2. Compute n = p * q, which is the modulus used in both keys.
 *              3. Compute Euler's totient function, phi = (p-1) * (q-1).
 *              4. Choose a public exponent e (usually 65537) and ensure it
 *                 is coprime with phi (GCD is 1).
 *              5. Calculate the private exponent d as the modular inverse of
 *                 e modulo phi.
 *              Returns a struct containing n, e, and d.
 */
RSAKeyPair generateKeys(int bits){
    cpp_int p = generatePrime(bits);
    cpp_int q = generatePrime(bits);

    cpp_int n = p*q;
    cpp_int phi = (p-1) * (q-1);

    cpp_int e = 65537;

    while(gcd(e,phi)!=1){
        e++;
    }

    cpp_int d = modInverse(e, phi);

    return {n, e, d};
}

/*
 * Function: encrypt
 * Description: Encrypts a plain numeric message into a ciphertext using the RSA
 *              algorithm. It performs modular exponentiation:
 *              ciphertext = (message ^ e) % n
 *              The public exponent 'e' and the modulus 'n' form the public key.
 */
cpp_int encrypt(cpp_int message, cpp_int e, cpp_int n){
    return modExp(message, e, n);
}

/*
 * Function: decrypt
 * Description: Decrypts an encrypted ciphertext back into the original numeric
 *              message using the RSA algorithm. It performs modular exponentiation:
 *              message = (ciphertext ^ d) % n
 *              The private exponent 'd' and the modulus 'n' form the private key.
 */
cpp_int decrypt(cpp_int cipher, cpp_int d, cpp_int n){
    return modExp(cipher, d, n);
}
