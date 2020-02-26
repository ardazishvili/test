#ifndef TRAITS_H
#define TRAITS_H

#include <type_traits>

template<bool>
struct is_safe_base : std::false_type
{
};
template<>
struct is_safe_base<true> : std::true_type
{
};

template<class TO, class FROM>
struct is_safe_arithmetic_conversion
  : is_safe_base<
      ((((std::is_integral<TO>::value && std::is_integral<FROM>::value) ||
         (std::is_floating_point<TO>::value &&
          std::is_floating_point<FROM>::value)) &&
        sizeof(TO) >= sizeof(FROM)) ||
       (std::is_floating_point<TO>::value && std::is_integral<FROM>::value)) &&
      ((std::is_signed<TO>::value && std::is_signed<FROM>::value) ||
       (std::is_unsigned<TO>::value && std::is_unsigned<FROM>::value))>
{
};

#endif
