#include <array>
#include <iostream>

namespace linal
{

template<typename T, int rows_count, int columns_count>
class Matrix
{
public:
  /* Matrix(); */

private:
  std::array<std::array<T, columns_count>, rows_count> _arr;
};
}

using mat3 = linal::Matrix<int, 3, 3>;
