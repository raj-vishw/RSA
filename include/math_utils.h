#pragma once
//Header for very large integers
#include<boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

cpp_int modExp(cpp_int base, cpp_int exp, cpp_int mod);
cpp_int gcd(cpp_int a,cpp_int b);
cpp_int modInverse(cpp_int e, cpp_int phi);
