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
  const T& at(int row, int column) const
  {
    return _rows.at(row).at(column);
  }

  void set(int row, int column, T value)
  {
    _rows.at(row).set(column, value);
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

  template<typename Q, int N, int M, int P>
  friend Matrix<Q, N, P> operator*(const Matrix<Q, N, M>& lhs,
                                   const Matrix<Q, M, P>& rhs);

  template<typename Q, int N, int M>
  friend Vector<Q, M> operator*(const Matrix<Q, N, M>& lhs,
                                const Vector<Q, M>& rhs);

private:
  std::array<Vector<T, columns_count>, rows_count> _rows;
};

template<typename Q, int N, int M, int P>
Matrix<Q, N, P> operator*(const Matrix<Q, N, M>& lhs,
                          const Matrix<Q, M, P>& rhs)
{
  auto res = Matrix<Q, N, P>();
  auto column = std::array<const Q*, M>();
  int k = 0;
  for (auto& row : rhs._rows) {
    column.at(k++) = &row.at(0);
  }

  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < N; ++j) {
      auto val = std::inner_product(lhs._rows.at(j).cbegin(),
                                    lhs._rows.at(j).cend(),
                                    column.cbegin(),
                                    0,
                                    std::plus<Q>(),
                                    [](Q lhs, const Q* rhs) {
                                      return lhs * (*rhs);
                                    });
      res.set(j, i, val);
    }
    std::transform(
      column.begin(), column.end(), column.begin(), [](const Q* p) {
        return ++p;
      });
  }

  return res;
}

template<typename Q, int N, int M>
Vector<Q, M> operator*(const Matrix<Q, N, M>& lhs, const Vector<Q, M>& rhs)
{
  auto res = Vector<Q, M>();

  for (int i = 0; i < M; ++i) {
    auto val = linal::dot(lhs._rows.at(i), rhs);
    res.set(i, val);
  }
  return res;
}

}

using mat3 = linal::Matrix<int, 3, 3>;
