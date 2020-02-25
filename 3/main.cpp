#include "Matrix.h"
#include "Vector.h"
#include <iostream>

int main(int argc, char** argv)
{
  auto v = vec3(1, 2, 3);
  /* auto wrong = vec3(1, 2, 3, 4); */
  std::cout << "v= " << v << std::endl;

  /* auto wrong = linal::Matrix<int, 3, 3>(vec3(), vec3(), vec3(), vec3()); */
  std::cout << "ki" << std::endl;

  return 0;
}
