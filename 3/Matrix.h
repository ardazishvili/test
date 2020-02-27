#include "Vector.h"
#include "traits.h"
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
template<typename T, size_t rows_count, size_t columns_count>

class Matrix
{
public:
  typedef T type;
  typedef typename std::array<Vector<T, columns_count>, rows_count> inner_type;
  typedef typename inner_type::iterator iterator;
  typedef typename inner_type::const_iterator const_iterator;
  inline iterator begin() noexcept
  {
    return _rows.begin();
  }

  inline const_iterator cbegin() const noexcept
  {
    return _rows.cbegin();
  }

  inline iterator end() noexcept
  {
    return _rows.end();
  }

  inline const_iterator cend() const noexcept
  {
    return _rows.cend();
  }

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
  const T& at(size_t row, size_t column) const
  {
    return _rows.at(row).at(column);
  }

  void set(size_t row, size_t column, T value)
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
    size_t i = 0;
    for (auto& row : _rows) {
      row.set(i++, 1);
    }
  }

  template<typename Q, size_t N, size_t M>
  Matrix<T, rows_count, columns_count>& operator+=(const Matrix<Q, N, M>& rhs)
  {
    auto t = *this;
    std::transform(begin(),
                   end(),
                   rhs.cbegin(),
                   begin(),
                   [](const Vector<T, columns_count>& lhs,
                      const Vector<Q, columns_count>& rhs) {
                     return lhs + rhs;
                   });
    auto r = *this;

    return *this;
  }

  template<typename S>
  Matrix<T, rows_count, columns_count>& operator*=(const S& scalar)
  {
    for (auto& row : _rows) {
      row *= scalar;
    }
    return *this;
  }

  template<typename Q, typename L, size_t N, size_t M>
  friend auto operator+(const Matrix<Q, N, M>& lhs, const Matrix<L, N, M>& rhs)
    -> Matrix<typename is_safe_arithmetic_conversion<Q, L>::wider_type, N, M>;

  template<typename Q, typename L, size_t N, size_t M, size_t P>
  friend auto operator*(const Matrix<Q, N, M>& lhs, const Matrix<L, M, P>& rhs)
    -> Matrix<typename is_safe_arithmetic_conversion<Q, L>::wider_type, N, P>;

  template<typename Q, size_t N, size_t M>
  friend Vector<Q, M> operator*(const Matrix<Q, N, M>& lhs,
                                const Vector<Q, M>& rhs);

private:
  std::array<Vector<T, columns_count>, rows_count> _rows;
};

template<typename Q, typename L, size_t N, size_t M, size_t P>
auto operator*(const Matrix<Q, N, M>& lhs, const Matrix<L, M, P>& rhs)
  -> Matrix<typename is_safe_arithmetic_conversion<Q, L>::wider_type, N, P>
{
  auto res =
    Matrix<typename is_safe_arithmetic_conversion<Q, L>::wider_type, N, P>();
  auto column = std::array<const L*, M>();
  size_t k = 0;
  for (auto& row : rhs._rows) {
    column.at(k++) = &row.at(0);
  }

  for (size_t i = 0; i < P; ++i) {
    for (size_t j = 0; j < N; ++j) {
      auto val = std::inner_product(
        lhs._rows.at(j).cbegin(),
        lhs._rows.at(j).cend(),
        column.cbegin(),
        static_cast<typename is_safe_arithmetic_conversion<Q, L>::wider_type>(
          0),
        std::plus<typename is_safe_arithmetic_conversion<Q, L>::wider_type>(),
        [](const Q& lhs, const L* rhs) {
          return lhs * (*rhs);
        });
      res.set(j, i, val);
    }
    std::transform(
      column.begin(), column.end(), column.begin(), [](const L* p) {
        return ++p;
      });
  }

  return res;
}

template<typename Q, size_t N, size_t M>
Vector<Q, M> operator*(const Matrix<Q, N, M>& lhs, const Vector<Q, M>& rhs)
{
  auto res = Vector<Q, M>();

  for (size_t i = 0; i < M; ++i) {
    auto val = linal::dot(lhs._rows.at(i), rhs);
    res.set(i, val);
  }
  return res;
}

template<typename Q, typename S, size_t N, size_t M>
Matrix<Q, N, M> operator*(const Matrix<Q, N, M>& lhs, const S& scalar)
{
  auto res = lhs;
  res *= scalar;
  return res;
}

template<typename Q, typename L, size_t N, size_t M>
Matrix<Q, N, M> add(const Matrix<Q, N, M>& lhs,
                    const Matrix<L, N, M>& rhs,
                    Int2Type<true>)
{
  auto res = lhs;
  res += rhs;
  return res;
}

template<typename Q, typename L, size_t N, size_t M>
Matrix<L, N, M> add(const Matrix<Q, N, M>& lhs,
                    const Matrix<L, N, M>& rhs,
                    Int2Type<false>)
{
  auto res = rhs;
  res += lhs;
  return res;
}

template<typename Q, typename L, size_t N, size_t M>
auto operator+(const Matrix<Q, N, M>& lhs, const Matrix<L, N, M>& rhs)
  -> Matrix<typename is_safe_arithmetic_conversion<Q, L>::wider_type, N, M>
{
  // if Q is a wider type add rhs to lhs, because lhs has a wider type
  // else if L is a wider type add lhs to rhs, because rhs has a wider type
  return add(lhs, rhs, Int2Type<is_safe_arithmetic_conversion<Q, L>::value>());
}

}

using mat3 = linal::Matrix<int, 3, 3>;
