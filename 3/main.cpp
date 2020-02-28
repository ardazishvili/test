#include "Matrix.h"
#include "Vector.h"
#include "traits.h"
#include <iostream>

int main(int argc, char** argv)
{
  std::cout << "is_safe_numeric_conversion<float,int>= "
            << is_safe_arithmetic_conversion<float, int>::value << std::endl;
  std::cout << "is_safe_numeric_conversion<int,float>= "
            << is_safe_arithmetic_conversion<int, float>::value << std::endl;

  return 0;
}
