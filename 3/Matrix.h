#include "Vector.h"
#include <array>
#include <iostream>

namespace linal
{
enum class MatrixType { Identity };

/**
   * @brief Matrix abstraction
   *
   * @tparam T element type
   * @tparam rows_count
   * @tparam columns_count
   *
   * @details
   * Compilation errors by design:
   * Matrix with wrong dimensions can't be created:
   * @code
   * auto error = linal::Matrix<int, 3, 3>(vec3(), vec3(), vec3(), vec3()); //compilation error
   * auto error = linal::Matrix<int, 3, 3>(vec3(), vec3(), vec2()) // compilation error
   * auto error = linal::Matrix<int, 3, 3>(vec2(), vec2(), vec2()) // compilation error
   * auto bad = linal::Matrix<int, 3, 3>(vec3(), vec3()) // exception thrown
   * @endcode
   */
template<typename T, int rows_count, int columns_count>

class Matrix
{
public:
  typedef T type;

  template<typename... Args>
  Matrix(Args... args) : _rows({ args... })
  {
    if (sizeof...(Args) != rows_count && sizeof...(Args) != 0) {
      throw "can't init Matrix: wrong rows number";
    }
  }

  /**
   * @brief Get (i, j) element
   *
   * @param row ~ i
   * @param column ~ j
   *
   * @return value
   */
  T at(int row, int column) const
  {
    return _rows.at(row).at(column);
  }

  /**
   * @brief Init Matrix of specific type
   *
   * @param t type of Matrix
   */
  void init(MatrixType t)
  {
    if (rows_count != columns_count) {
      throw "can't init non-square matrix with Identity matrix";
    }
    int i = 0;
    for (auto& row : _rows) {
      row.set(i++, 1);
    }
  }

private:
  std::array<Vector<T, columns_count>, rows_count> _rows;
};
}

using mat3 = linal::Matrix<int, 3, 3>;
