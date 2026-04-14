#pragma once

#include<boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

struct RSAKeyPair {
    cpp_int n;
    cpp_int e;
    cpp_int d;
};

RSAKeyPair generateKeys(int bits);

cpp_int encrypt(cpp_int message, cpp_int e, cpp_int n);
cpp_int decrypt(cpp_int cipher, cpp_int d, cpp_int n);