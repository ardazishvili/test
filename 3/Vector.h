#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>

#include "traits.h"

namespace linal
{

/**
 * @brief Vector abstraction
 *
 * @tparam T element type
 * @tparam size
 *
 * @details
 * Compilation errors by design:
 * Vector<int, 3> and Vector<int, 1> are different types so can't be added
 * @code
 * auto v = Vector<int, 3>(1, 2, 3);
 * v += Vector<int, 1>(); // error
 * @endcode
 */
template<typename T, size_t size>
class Vector
{
public:
  typedef T type;
  typedef typename std::array<T, size> inner_type;
  typedef typename inner_type::iterator iterator;
  typedef typename inner_type::const_iterator const_iterator;
  inline iterator begin() noexcept
  {
    return _arr.begin();
  }

  inline const_iterator cbegin() const noexcept
  {
    return _arr.cbegin();
  }

  inline iterator end() noexcept
  {
    return _arr.end();
  }

  inline const_iterator cend() const noexcept
  {
    return _arr.cend();
  }

  template<typename... Args>
  Vector(Args... args) : _arr({ args... })
  {
    if (sizeof...(Args) != size && sizeof...(Args) != 0) {
      throw "can't init Vector: wrong size";
    }
  }

  template<typename Q, size_t S>
  Vector(const Vector<Q, S>& other)
  {
    if (!is_safe_arithmetic_conversion<T, Q>::value) {
      throw "vector cannot be initialized: narrowing of type!";
    } else {
      auto tmp = other;
      std::copy(begin(), end(), tmp.begin());
    }
  }

  /**
   * @brief Get 'i' element
   *
   * @param index
   *
   * @return const ref to value
   */
  const T& at(size_t index) const
  {
    return _arr.at(index);
  }

  /**
   * @brief Set value of Vector by given index
   *
   * @param index
   * @param value
   */
  void set(size_t index, T value)
  {
    _arr.at(index) = value;
  }

  /**
   * @brief Get Vector dimension
   *
   * @return dimension
   */
  size_t dim() const
  {
    return size;
  }

  /**
   * @brief Compound assignment operator
   *
   * @tparam U Element type
   * @tparam S Vector size
   * @param rhs Right hand side of operator
   *
   * @return ref to *this
   */
  template<typename U, size_t S>
  Vector<T, size>& operator+=(const Vector<U, S>& rhs)
  {
    if (!is_safe_arithmetic_conversion<T, U>::value) {
      throw "vectors cannot be added: narrowing of type!";
    }
    std::transform(begin(), end(), rhs.cbegin(), begin(), std::plus<T>());
    return *this;
  }

  /**
   * @brief Compound multiplication operator
   *
   * @tparam U Scalar type
   * @param Scalar value
   *
   * @return ref to *this
   */
  template<typename U>
  Vector<T, size>& operator*=(const U& value)
  {
    if (!is_safe_arithmetic_conversion<T, U>::value) {
      throw "vectors cannot be added: narrowing of type!";
    }
    std::transform(
      begin(),
      end(),
      begin(),
      std::bind(std::multiplies<T>(), std::placeholders::_1, value));
    return *this;
  }

  /**
   * @brief Stream insertion operator for a Vector
   *
   * @tparam U Vector type
   * @tparam S Vector dimension
   * @param os ref to stream
   * @param v ref to Vector instance
   *
   * @return ref to stream
   */
  template<typename U, size_t S>
  friend std::ostream& operator<<(std::ostream& os, const Vector<U, S>& v);

private:
  std::array<T, size> _arr;
};

template<typename U, typename Q, size_t S>
Vector<U, S> add(const Vector<U, S>& lhs,
                 const Vector<Q, S>& rhs,
                 Int2Type<true>)
{
  auto res = lhs;
  res += rhs;
  return res;
}

template<typename U, typename Q, size_t S>
Vector<Q, S> add(const Vector<U, S>& lhs,
                 const Vector<Q, S>& rhs,
                 Int2Type<false>)
{
  auto res = rhs;
  res += lhs;
  return res;
}

/**
 * @brief Assignment operator for 2 Vectors of same dimension
 *
 * @tparam U Element type of first Vector
 * @tparam Q Element type of second Vector
 * @tparam S Dimension
 * @param lhs
 * @param rhs
 *
 * @return result Vector
 */
template<typename U, typename Q, size_t S>
auto operator+(const Vector<U, S> lhs, const Vector<Q, S>& rhs)
  -> Vector<typename is_safe_arithmetic_conversion<U, Q>::wider_type, S>
{
  // if U is a wider type add rhs to lhs, because lhs has a wider type
  // else if Q is a wider type add lhs to rhs, because rhs has a wider type
  return add(lhs, rhs, Int2Type<is_safe_arithmetic_conversion<U, Q>::value>());
}

/**
 * @brief Mupliplication operator for a Vector and scalar value
 *
 * @tparam T Vector type
 * @tparam Q Scalar type
 * @tparam S Vector dimension
 * @param lhs
 * @param value Scalar value
 *
 * @return result Vector
 */
template<typename T, typename Q, size_t S>
Vector<T, S> operator*(Vector<T, S> lhs, const Q& value)
{
  lhs *= value;
  return lhs;
}

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const Vector<T, size>& v)
{
  os << "{ ";
  for (const auto& i : v._arr) {
    os << i << " ";
  }
  os << "}" << std::endl;
  return os;
}

/**
 * @brief Dot product of 2 Vectors
 *
 * @tparam U Vector type
 * @tparam S Vector dimension
 * @param a
 * @param b
 *
 * @return dot product
 */
template<typename U, typename Q, size_t S>
auto dot(const Vector<U, S>& a, const Vector<Q, S>& b)
{
  return std::inner_product(
    a.cbegin(),
    a.cend(),
    b.cbegin(),
    static_cast<typename is_safe_arithmetic_conversion<U, Q>::wider_type>(0));
}

template<typename T, typename U>
Vector<T, 3> cross(const Vector<T, 3>& x, const Vector<U, 3>& y)
{
  auto a = x;
  auto b = y;
  return Vector<T, 3>(a.at(1) * b.at(2) - a.at(2) * b.at(1),
                      a.at(2) * b.at(0) - a.at(0) * b.at(2),
                      a.at(0) * b.at(1) - a.at(1) * b.at(0));
}

}

using vec3 = linal::Vector<int, 3>;
using vec2 = linal::Vector<int, 2>;
using vecf2 = linal::Vector<float, 2>;
using vecf3 = linal::Vector<float, 3>;

#endif
