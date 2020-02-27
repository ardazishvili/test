#include "Matrix.h"
#include "Vector.h"
#include "traits.h"
#include <iostream>

int main(int argc, char** argv)
{
  auto v = vec3(1, 2, 3);
  /* auto wrong = vec3(1, 2, 3, 4); */
  std::cout << "v= " << v << std::endl;

  /* auto wrong = linal::Matrix<int, 3, 3>(vec3(), vec3(), vec3(), vec3()); */
  std::cout << "ki" << std::endl;

  std::cout << "is_safe_numeric_conversion<float,int>= "
            << is_safe_arithmetic_conversion<float, int>::value << std::endl;
  std::cout << "is_safe_numeric_conversion<int,float>= "
            << is_safe_arithmetic_conversion<int, float>::value << std::endl;

  return 0;
}
