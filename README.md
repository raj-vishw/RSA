# RSA Cryptography Implementation in C++

This project provides a fully functional, from-scratch implementation of the RSA (Rivest-Shamir-Adleman) public-key cryptosystem in C++. It supports generating large prime numbers, creating 512-bit RSA key pairs, and encrypting/decrypting both numeric data and text strings.

## Features

*   **Custom Prime Generation:** Uses the Miller-Rabin primality test to securely generate large prime numbers.
*   **Large Integer Arithmetic:** Utilizes the `Boost.Multiprecision` library (`cpp_int`) to handle the extremely large integers required for 512-bit keys and ciphertext without integer overflow.
*   **Mathematical Utilities:** Implements core cryptographic algorithms natively:
    *   **Modular Exponentiation:** Exponentiation by squaring for fast `(base^exp) % mod` operations.
    *   **Extended Euclidean Algorithm (EEA):** Used to calculate the greatest common divisor (GCD) and the modular multiplicative inverse for generating the private key `d`.
*   **String Encryption:** Converts plain text ASCII strings into large integer representations before encrypting, and cleanly decodes them back to text upon decryption.

## How It Works (Brief Overview)

1.  **Key Generation (`rsa.cpp`):** Generates two 256-bit prime numbers (p and q) to form a 512-bit modulus n = p * q. It calculates Euler's totient function phi(n) = (p-1)(q-1) and sets the public exponent e = 65537. The private key d is calculated such that (d * e) % phi(n) = 1.
2.  **String to Integer (`main.cpp`):** The input text string is sequentially converted into a single large `cpp_int` using bitwise left-shifts.
3.  **Encryption (`rsa.cpp`):** Ciphertext = (Message^e) % n
4.  **Decryption (`rsa.cpp`):** Message = (Ciphertext^d) % n
5.  **Integer to String (`main.cpp`):** The decrypted large integer is unpacked bit by bit (using bitwise right-shifts and masking) to restore the original ASCII string.
