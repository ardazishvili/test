#include <gmock/gmock.h>

#include "../Vector.h"

using namespace linal;
using ::testing::Eq;
TEST(Vector, doesntThrowOnValidArguments)
{
  EXPECT_NO_THROW((Vector<int, 3>(1, 2, 3)));
}

TEST(Vector, throwOnIncompleteArgumentList)
{
  EXPECT_ANY_THROW((Vector<int, 3>(1, 2)));
}

TEST(Vector, fillsZeroesOnEmptyArgumentList)
{
  auto v = Vector<int, 3>();
  EXPECT_THAT(v.at(0), Eq(0));
  EXPECT_THAT(v.at(1), Eq(0));
  EXPECT_THAT(v.at(2), Eq(0));
}

TEST(Vector, fillsValuesOnNonemptyArgumentList)
{
  auto v = Vector<int, 3>(1, 2, 3);
  EXPECT_THAT(v.at(0), Eq(1));
  EXPECT_THAT(v.at(1), Eq(2));
  EXPECT_THAT(v.at(2), Eq(3));
}

TEST(Vector, returnElementWiseSumWhenAddedCompound)
{
  auto v = Vector<int, 3>(1, 2, 3);
  v += Vector<int, 3>(10, 20, 30);

  EXPECT_THAT(v.at(0), Eq(11));
  EXPECT_THAT(v.at(1), Eq(22));
  EXPECT_THAT(v.at(2), Eq(33));
}

TEST(Vector, returnElementWiseSumWhenAdded)
{
  auto v = Vector<int, 3>(1, 2, 3) + Vector<int, 3>(10, 20, 30);
  EXPECT_THAT(v.at(0), Eq(11));
  EXPECT_THAT(v.at(1), Eq(22));
  EXPECT_THAT(v.at(2), Eq(33));
}

TEST(Vector, returnScalarMultiplicationCompound)
{
  auto v = Vector<int, 3>(1, 2, 3);
  v *= 10;

  EXPECT_THAT(v.at(0), Eq(10));
  EXPECT_THAT(v.at(1), Eq(20));
  EXPECT_THAT(v.at(2), Eq(30));
}

TEST(Vector, returnScalarMultiplication)
{
  auto v = Vector<int, 3>(1, 2, 3) * 10;

  EXPECT_THAT(v.at(0), Eq(10));
  EXPECT_THAT(v.at(1), Eq(20));
  EXPECT_THAT(v.at(2), Eq(30));
}
