#include <gmock/gmock.h>

#include "../Matrix.h"

using namespace linal;
using ::testing::Eq;
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
