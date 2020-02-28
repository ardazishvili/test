## Requirements

Matrix and vector classes with the support of multiplication, addition and scalar multiplication.

## Design/efficiency tradeoff

My goal was the maintainable design with type safety support. The next priority was efficiency.

## Type safety

Both Vector and Matrix classed have to be designed in such a way to prevent as most programmer errors as possible."error" means compilation error or at least exception.
1. Type and dimensions of Vector/Matrix classes are immutable, i.e. they don't change in time.

2. Matrix/Vector multiplication should return an object with other dimensions (obviously) and the type which is widest between types of multiplied objects. E.g.:

```c++
Matrix<int, 2, 2> m =
        Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) *
        Matrix<int, 3, 2>(vec2(7, 8), vec2(9, 10), vec2(11, 12)); // result type is int

Matrix<float, 2, 2> m = Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) *
                        Matrix<float, 3, 2>(vecf2(7.1f, 8.2f),
                                            vecf2(9.3f, 10.4f),
                                            vecf2(11.5f, 12.6f)); // result type is float.

Matrix<float, 2, 2> m =
        Matrix<float, 2, 3>(vecf3(1.1f, 2.2f, 3.3f), vecf3(4.4f, 5.5f, 6.6f)) *
        Matrix<int, 3, 2>(vec2(7, 8), vec2(9, 10), vec2(11, 12)); // result type is also float
```

3. Matrix/Vector addition should return the object with the same dimensions and the type which is widest between types of added objects. E.g.:
```c++
Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) +
                      Matrix<int, 2, 2>(vec2(5, 6), vec2(7, 8)); // the result type is int.

Matrix<float, 2, 2> m = Matrix<int, 2, 2>(vec2(5, 6), vec2(7, 8)) +
                        Matrix<float, 2, 2>(vecf2(1.1f, 2.2f), vecf2(3.3f, 4.4f)); // the result type is float.
```

4. Compound adding/scalar multiplication using object of a wider type must be followed by an error, e.g.
```c++
auto v = Vector<int, 3>(1, 2, 3);
v += Vector<float, 3>(10.1f, 20.2f, 30.3f); //  error
auto v = Vector<int, 3>(1, 2, 3) + Vector<float, 3>(10.1f, 20.2f, 30.3f); // OK

auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4));
m *= 1.1f; // error
auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) * 1.1f; // OK
```



5. Matrix/Vector classes must check dimensions at construction. E.g.:
```c++
auto m = Matrix<int, 3, 3>(vec3(), vec3()); // error
auto m = Matrix<int, 3, 3>(vec3(), vec3(), vec3(), vec3()); // error
auto m = Matrix<int, 3, 3>(vec3(), vec3(), vec3()); // OK

auto v = Vector<float, 3>(1.0f, 2.0f); // error
auto v = Vector<float, 3>(1.0f, 2.0f, 3.0f, 4.0f); // error
auto v = Vector<float, 3>(1.0f, 2.0f, 3.0f); // OK
```

## Limitations

Exceptions model have not been designed.
Matrix multiplication is not cache-friendly at all. Faster algorithms, e.g. Strassen, also has not been considered.

## Dependencies

gtest/gmock. Will be downloaded and built by cmake.

## Build and run instructions

```bash
mkdir cbuild && cd cbuild
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
```

Run tests

```bash
./unit_tests
```