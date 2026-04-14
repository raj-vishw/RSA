#pragma once

#include<boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

bool isPrime(cpp_int n, cpp_int iterations = 5);
cpp_int generatePrime(int bits);