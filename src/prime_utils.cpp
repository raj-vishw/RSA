#include "../include/prime_utils.h"
#include "../include/math_utils.h"
#include <cstdlib>

/*
 * Function: isPrime
 * Description: Determines if a given large number 'n' is prime. It uses the
 *              Miller-Rabin primality test, a probabilistic algorithm.
 *              It factors out powers of 2 from n-1, then tests the number
 *              against several small prime bases. If 'n' passes the test for
 *              a given number of iterations (or bases), it is highly likely
 *              to be prime. If it fails even once, it is definitely composite.
 */
bool isPrime(cpp_int n, cpp_int iterations){
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    cpp_int d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    
    /*
     * In-built Function: sizeof()
     * Description: A compile-time operator that returns the size, in bytes, of
     *              a variable or data type. Here it's used to calculate the number
     *              of elements in the 'bases' array by dividing the total array
     *              size by the size of its first element.
     */
    int num_bases = sizeof(bases)/sizeof(bases[0]);

    for (int i = 0; i < iterations && i < num_bases; i++) {
        cpp_int a = bases[i];
        if (n <= a) break;

        cpp_int x = modExp(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        cpp_int temp = d;
        while (temp != n - 1) {
            x = (x * x) % n;
            temp *= 2;

            if (x == 1) return false;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

/*
 * Function: generateRandom
 * Description: Generates a random large integer of a specific bit length.
 *              It starts with a value of 1 and iteratively shifts it left
 *              by 1 bit, appending a random bit (0 or 1) at the end using
 *              the standard rand() function. This builds up the large integer
 *              bit by bit until it reaches the desired length.
 */
cpp_int generateRandom(int bits) {
    cpp_int res = 1;
    for (int i = 1; i < bits; i++) {
        /*
         * In-built Function: rand()
         * Description: Included from <cstdlib>. It returns a pseudo-random integer
         *              in the range from 0 to RAND_MAX. Here, rand() % 2 is used
         *              to generate either a 0 or a 1, which represents a single
         *              random bit to append to our large number.
         */
        res = (res << 1) | (rand() % 2);
    }
    return res;
}

/*
 * Function: generatePrime
 * Description: Generates a likely prime number of a specific bit length.
 *              It first calls generateRandom() to get a random large number.
 *              It ensures the number is odd (since even numbers > 2 aren't prime)
 *              by using a bitwise OR with 1. Then it repeatedly tests consecutive
 *              odd numbers using isPrime() until it finds one that passes.
 */
cpp_int generatePrime(int bits){
    cpp_int num = generateRandom(bits);
    num |= 1; // Make it odd
    while(!isPrime(num, 10)){
        num += 2;
    }
    return num;
}
