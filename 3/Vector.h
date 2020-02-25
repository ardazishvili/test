#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>

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
template<typename T, int size>
class Vector
{
public:
  typedef T type;
  template<typename... Args>
  Vector(Args... args) : _arr({ args... })
  {
    if (sizeof...(Args) != size && sizeof...(Args) != 0) {
      throw "can't init Vector: wrong size";
    }
  }

  /**
   * @brief Get 'i' element
   *
   * @param index
   *
   * @return value
   */
  T at(int index) const
  {
    return _arr.at(index);
  }

  /**
   * @brief Set value of Vector by given index
   *
   * @param index
   * @param value
   */
  void set(int index, T value)
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

  template<typename U, int S>
  Vector<T, size>& operator+=(const Vector<U, S>& rhs)
  {
    auto tmp = rhs._arr;
    std::transform(
      _arr.begin(), _arr.end(), tmp.begin(), _arr.begin(), std::plus<T>());
    return *this;
  }

  template<typename U>
  Vector<T, size>& operator*=(const U& value)
  {
    std::transform(
      _arr.begin(),
      _arr.end(),
      _arr.begin(),
      std::bind(std::multiplies<T>(), std::placeholders::_1, value));
    return *this;
  }

  template<typename U, int S>
  friend Vector<U, S> operator+(Vector<U, S> lhs, const Vector<U, S>& rhs);

  template<typename U, int S>
  friend Vector<U, S> operator*(Vector<U, S> lhs, const U& value);

  template<typename U, int S>
  friend std::ostream& operator<<(std::ostream& os, const Vector<U, S>& v);

  template<typename U>
  friend typename U::type dot(const U& a, const U& b);

private:
  std::array<T, size> _arr;
};

template<typename T, int size>
Vector<T, size> operator+(Vector<T, size> lhs, const Vector<T, size>& rhs)
{
  lhs += rhs;
  return lhs;
}

template<typename T, int size>
Vector<T, size> operator*(Vector<T, size> lhs, const T& value)
{
  lhs *= value;
  return lhs;
}

template<typename T, int size>
std::ostream& operator<<(std::ostream& os, const Vector<T, size>& v)
{
  os << "{ ";
  for (const auto& i : v._arr) {
    os << i << " ";
  }
  os << "}" << std::endl;
  return os;
}

template<typename T>
typename T::type dot(const T& a, const T& b)
{
  auto x = a._arr;
  auto y = b._arr;
  std::transform(x.begin(),
                 x.end(),
                 y.begin(),
                 x.begin(),
                 std::multiplies<typename T::type>());
  return std::accumulate(x.begin(), x.end(), 0);
}

template<typename T>
Vector<T, 3> cross(const Vector<T, 3>& x, const Vector<T, 3>& y)
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

#endif
