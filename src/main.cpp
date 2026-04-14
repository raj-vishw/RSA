#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "../include/rsa.h"

/*
 * Function: stringToInt
 * Description: Converts an ASCII string into a large integer representation.
 *              It does this by taking each character and shifting the accumulated
 *              integer left by 8 bits (1 byte) before adding the new character.
 *              This bundles the string characters into a single large number
 *              that can be mathematically encrypted by RSA.
 */
cpp_int stringToInt(const std::string& text) {
    cpp_int m = 0;
    for(char c : text) {
        m = (m << 8) + (unsigned char)c;
    }
    return m;
}

/*
 * Function: intToString
 * Description: Reverses the stringToInt process. It takes a large integer
 *              and repeatedly extracts the lowest 8 bits (representing a character)
 *              by using a bitwise AND with 0xFF. It then shifts the integer
 *              right by 8 bits to process the next character, prepending each
 *              extracted character to reconstruct the original string.
 */
std::string intToString(cpp_int m) {
    std::string text = "";
    while(m > 0) {
        text = (char)((unsigned int)(m & 0xFF)) + text;
        m >>= 8;
    }
    return text;
}

/*
 * Function: main
 * Description: The primary entry point of the program. It handles:
 *              1. Seeding the random number generator.
 *              2. Generating the RSA public and private keys.
 *              3. Receiving string input from the user.
 *              4. Converting the string to a large integer format.
 *              5. Encrypting the integer using the public key.
 *              6. Decrypting the integer using the private key.
 *              7. Converting the decrypted integer back to a string.
 */
int main(){
    /*
     * In-built Function: time(NULL)
     * Description: Included from <ctime>. It returns the current calendar time as a
     *              value of type time_t. Passing NULL means we just want the return
     *              value and don't need it stored in a pointer. We use this changing
     *              value to ensure our random numbers are different every time we run.
     * 
     * In-built Function: srand()
     * Description: Included from <cstdlib>. It seeds the pseudo-random number generator
     *              used by rand(). Providing the current time as the seed ensures
     *              that the sequence of random numbers generated is not the same
     *              across different executions of the program.
     */
    srand(time(NULL));
    std::cout << "Generating 512-bit RSA keys... Please wait.\n";
    // Using 256 bits for primes p and q, creating a 512-bit modulus n
    RSAKeyPair keys = generateKeys(256);

    std::cout << "Public Key(n,e):\n" << keys.n << "\n" << keys.e << "\n\n";
    std::cout << "Private Key (d):\n" << keys.d << "\n\n";

    std::string msg;
    std::cout << "Enter text to encrypt: ";
    
    /*
     * In-built Function: std::getline()
     * Description: Included from <string>. It extracts characters from the input
     *              stream (std::cin) and appends them to the string (msg) until a
     *              delimiting character (newline by default) is found. This allows
     *              us to read input containing spaces, unlike the standard >> operator.
     */
    std::getline(std::cin, msg);

    cpp_int num_msg = stringToInt(msg);

    if (num_msg >= keys.n) {
        std::cout << "Message is too long for the key size! (Needs to be numerically smaller than n)\n";
        return 1;
    }

    auto cipher = encrypt(num_msg, keys.e, keys.n);
    std::cout << "\nEncrypted (Cipher):\n" << cipher << "\n";

    auto decrypted = decrypt(cipher, keys.d, keys.n);
    
    std::string decrypted_msg = intToString(decrypted);
    std::cout << "\nDecrypted Text: " << decrypted_msg << "\n";

    return 0;
}
