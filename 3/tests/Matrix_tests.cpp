#include <gmock/gmock.h>

#include "../Matrix.h"

using namespace linal;
using ::testing::Eq;
using ::testing::FloatEq;
TEST(MatrixDoesntThrow, onValidArguments)
{
  EXPECT_NO_THROW((Matrix<int, 3, 3>(vec3(), vec3(), vec3())));
}

TEST(MatrixDoesntThrow, onEmptyConstructor)
{
  EXPECT_NO_THROW((Matrix<int, 3, 3>()));
}

TEST(MatrixThrow, onIncompleteRowsList)
{
  EXPECT_ANY_THROW((Matrix<int, 3, 3>(vec3(), vec3())));
  EXPECT_ANY_THROW((Matrix<int, 3, 2>(vec2(), vec2())));
}

TEST(MatrixThrow, onInitRectangularMatrixWithIdentityMatrix)
{
  EXPECT_ANY_THROW((Matrix<int, 3, 2>().init(MatrixType::Identity)));
}

TEST(MatrixThrow, onTypeNarrowingWhenMultipliedByScalar)
{
  auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4));
  EXPECT_ANY_THROW((m *= 1.1f));
}

TEST(MatrixThrow, onTypeNarrowingWhenMultipliedMatrix)
{
  EXPECT_ANY_THROW((Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) *
                    Matrix<float, 2, 2>(vecf3(1.1f, 1.1f), vecf3(1.1f, 1.1f))));
}

TEST(MatrixThrow, onTypeNarrowingWhenAdded)
{
  auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4));
  EXPECT_ANY_THROW(
    (m += Matrix<float, 2, 2>(vecf2(0.1f, 0.1f), vecf2(0.1f, 0.1f))));
}

TEST(MatrixInit, withZeroesOnEmptyConstructorArgs)
{
  auto m = Matrix<int, 2, 2>();

  EXPECT_THAT(m.at(0, 0), Eq(0));
  EXPECT_THAT(m.at(0, 1), Eq(0));
  EXPECT_THAT(m.at(1, 0), Eq(0));
  EXPECT_THAT(m.at(1, 1), Eq(0));
}

TEST(MatrixInit, withOnesAfterIdentityMatrixInialization)
{
  auto m = Matrix<int, 2, 2>();
  m.init(MatrixType::Identity);

  EXPECT_THAT(m.at(0, 0), Eq(1));
  EXPECT_THAT(m.at(0, 1), Eq(0));
  EXPECT_THAT(m.at(1, 0), Eq(0));
  EXPECT_THAT(m.at(1, 1), Eq(1));
}

TEST(MatrixMultiplication, ofSquareMatrices)
{
  {
    auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) *
             Matrix<int, 2, 2>(vec2(5, 6), vec2(7, 8));
    EXPECT_THAT(m.at(0, 0), Eq(19));
    EXPECT_THAT(m.at(0, 1), Eq(22));
    EXPECT_THAT(m.at(1, 0), Eq(43));
    EXPECT_THAT(m.at(1, 1), Eq(50));
  }
  {
    auto m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) *
             Matrix<int, 2, 2>(vec2(0, 0), vec2(0, 0));
    EXPECT_THAT(m.at(0, 0), Eq(0));
    EXPECT_THAT(m.at(0, 1), Eq(0));
    EXPECT_THAT(m.at(1, 0), Eq(0));
    EXPECT_THAT(m.at(1, 1), Eq(0));
  }
}

TEST(MatrixMultiplication, ofRectangularMatrices)
{
  {
    Matrix<int, 2, 2> m =
      Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) *
      Matrix<int, 3, 2>(vec2(7, 8), vec2(9, 10), vec2(11, 12));
    EXPECT_THAT(m.at(0, 0), Eq(58));
    EXPECT_THAT(m.at(0, 1), Eq(64));
    EXPECT_THAT(m.at(1, 0), Eq(139));
    EXPECT_THAT(m.at(1, 1), Eq(154));
  }
  {
    Matrix<int, 2, 3> m =
      Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) *
      Matrix<int, 3, 3>(vec3(7, 8, 9), vec3(10, 11, 12), vec3(13, 14, 15));
    EXPECT_THAT(m.at(0, 0), Eq(66));
    EXPECT_THAT(m.at(0, 1), Eq(72));
    EXPECT_THAT(m.at(0, 2), Eq(78));
    EXPECT_THAT(m.at(1, 0), Eq(156));
    EXPECT_THAT(m.at(1, 1), Eq(171));
    EXPECT_THAT(m.at(1, 2), Eq(186));
  }
  {
    Matrix<float, 2, 2> m =
      Matrix<float, 2, 3>(vecf3(1.1f, 2.2f, 3.3f), vecf3(4.4f, 5.5f, 6.6f)) *
      Matrix<int, 3, 2>(vec2(7, 8), vec2(9, 10), vec2(11, 12));
    EXPECT_THAT(m.at(0, 0), FloatEq(63.8f));
    EXPECT_THAT(m.at(0, 1), FloatEq(70.4f));
    EXPECT_THAT(m.at(1, 0), FloatEq(152.9f));
    EXPECT_THAT(m.at(1, 1), FloatEq(169.4f));
  }
}

TEST(MatrixMultiplication, ofSquareMatriceAndVectorOfValidDimension)
{
  {
    vec2 m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) * vec2(5, 6);
    EXPECT_THAT(m.at(0), Eq(17));
    EXPECT_THAT(m.at(1), Eq(39));
  }

  {
    vec2 m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) * vec2(0, 0);
    EXPECT_THAT(m.at(0), Eq(0));
    EXPECT_THAT(m.at(1), Eq(0));
  }
}

TEST(MatrixMultiplication, onScalar)
{
  {
    Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) * 42;
    EXPECT_THAT(m.at(0, 0), Eq(42 * 1));
    EXPECT_THAT(m.at(0, 1), Eq(42 * 2));
    EXPECT_THAT(m.at(1, 0), Eq(42 * 3));
    EXPECT_THAT(m.at(1, 1), Eq(42 * 4));
  }

  {
    Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) * (-42);
    EXPECT_THAT(m.at(0, 0), Eq(-42 * 1));
    EXPECT_THAT(m.at(0, 1), Eq(-42 * 2));
    EXPECT_THAT(m.at(1, 0), Eq(-42 * 3));
    EXPECT_THAT(m.at(1, 1), Eq(-42 * 4));
  }

  {
    Matrix<int, 2, 3> m = Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) * 0;
    EXPECT_THAT(m.at(0, 0), Eq(0));
    EXPECT_THAT(m.at(0, 1), Eq(0));
    EXPECT_THAT(m.at(0, 2), Eq(0));
    EXPECT_THAT(m.at(1, 0), Eq(0));
    EXPECT_THAT(m.at(1, 1), Eq(0));
    EXPECT_THAT(m.at(1, 2), Eq(0));
  }

  {
    Matrix<float, 2, 2> m =
      Matrix<float, 2, 2>(vecf2(1.1f, 2.2f), vecf2(3.3f, 4.4f)) * (-42);
    EXPECT_THAT(m.at(0, 0), FloatEq(-42 * 1.1f));
    EXPECT_THAT(m.at(0, 1), FloatEq(-42 * 2.2f));
    EXPECT_THAT(m.at(1, 0), FloatEq(-42 * 3.3f));
    EXPECT_THAT(m.at(1, 1), FloatEq(-42 * 4.4f));
  }
}

TEST(MatrixMultiplication, onScalarCoumpound)
{
  {
    Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4));
    m *= 42;
    EXPECT_THAT(m.at(0, 0), Eq(42 * 1));
    EXPECT_THAT(m.at(0, 1), Eq(42 * 2));
    EXPECT_THAT(m.at(1, 0), Eq(42 * 3));
    EXPECT_THAT(m.at(1, 1), Eq(42 * 4));
  }

  {
    Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4));
    m *= (-42);
    EXPECT_THAT(m.at(0, 0), Eq(-42 * 1));
    EXPECT_THAT(m.at(0, 1), Eq(-42 * 2));
    EXPECT_THAT(m.at(1, 0), Eq(-42 * 3));
    EXPECT_THAT(m.at(1, 1), Eq(-42 * 4));
  }

  {
    Matrix<int, 2, 3> m = Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6));
    m *= 0;
    EXPECT_THAT(m.at(0, 0), Eq(0));
    EXPECT_THAT(m.at(0, 1), Eq(0));
    EXPECT_THAT(m.at(0, 2), Eq(0));
    EXPECT_THAT(m.at(1, 0), Eq(0));
    EXPECT_THAT(m.at(1, 1), Eq(0));
    EXPECT_THAT(m.at(1, 2), Eq(0));
  }
}

TEST(MatrixAddition, worksForMatricesOfSameDimensions)
{
  {
    Matrix<int, 2, 2> m = Matrix<int, 2, 2>(vec2(1, 2), vec2(3, 4)) +
                          Matrix<int, 2, 2>(vec2(5, 6), vec2(7, 8));
    EXPECT_THAT(m.at(0, 0), Eq(5 + 1));
    EXPECT_THAT(m.at(0, 1), Eq(6 + 2));
    EXPECT_THAT(m.at(1, 0), Eq(7 + 3));
    EXPECT_THAT(m.at(1, 1), Eq(8 + 4));
  }
  {
    Matrix<int, 2, 3> m = Matrix<int, 2, 3>(vec3(1, 2, 3), vec3(4, 5, 6)) +
                          Matrix<int, 2, 3>(vec3(7, 8, 9), vec3(10, 11, 12));
    EXPECT_THAT(m.at(0, 0), Eq(7 + 1));
    EXPECT_THAT(m.at(0, 1), Eq(8 + 2));
    EXPECT_THAT(m.at(0, 2), Eq(9 + 3));
    EXPECT_THAT(m.at(1, 0), Eq(10 + 4));
    EXPECT_THAT(m.at(1, 1), Eq(11 + 5));
    EXPECT_THAT(m.at(1, 2), Eq(12 + 6));
  }
  {
    Matrix<float, 2, 2> m =
      Matrix<float, 2, 2>(vecf2(1.1f, 2.2f), vecf2(3.3f, 4.4f)) +
      Matrix<int, 2, 2>(vec2(5, 6), vec2(7, 8));
    EXPECT_THAT(m.at(0, 0), FloatEq(5 + 1.1));
    EXPECT_THAT(m.at(0, 1), FloatEq(6 + 2.2));
    EXPECT_THAT(m.at(1, 0), FloatEq(7 + 3.3));
    EXPECT_THAT(m.at(1, 1), FloatEq(8 + 4.4));
  }
}
