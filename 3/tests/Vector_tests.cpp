#include <gmock/gmock.h>

#include "../Vector.h"

using namespace linal;
using ::testing::Eq;
TEST(Vector, doesntThrowOnValidArguments)
{
  EXPECT_NO_THROW((Vector<int, 3>(1, 2, 3)));
  EXPECT_NO_THROW((Vector<float, 3>(1.0f, 2.0f, 3.0f)));
}

TEST(VectorThrow, onIncompleteArgumentList)
{
  EXPECT_ANY_THROW((Vector<int, 3>(1, 2)));
  EXPECT_ANY_THROW((Vector<float, 3>(1.0f, 2.0f)));
}

TEST(VectorThrow, onTypeNarrowingWhenAdded)
{
  auto v = Vector<int, 3>(1, 2, 3);
  EXPECT_ANY_THROW((v += Vector<float, 3>(10.1f, 20.2f, 30.3f)));

  EXPECT_ANY_THROW(
    (Vector<int, 3>(1, 2, 3) + Vector<float, 3>(10.1f, 20.2f, 30.3f)));
}

TEST(VectorThrow, onTypeNarrowingWhenMultipliedByScalar)
{
  auto v = Vector<int, 3>(1, 2, 3);
  EXPECT_ANY_THROW((v *= 1.1f));

  EXPECT_ANY_THROW((Vector<int, 3>(1, 2, 3) * 1.1f));
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
  {
    auto v = Vector<int, 3>(1, 2, 3);
    v += Vector<int, 3>(10, 20, 30);

    EXPECT_THAT(v.at(0), Eq(11));
    EXPECT_THAT(v.at(1), Eq(22));
    EXPECT_THAT(v.at(2), Eq(33));
  }
  {
    // it is OK: 'int' -> 'float' without narrowing
    auto v = Vector<float, 3>(10.1f, 20.2f, 30.3f);
    v += Vector<int, 3>(1, 2, 3);

    EXPECT_THAT(v.at(0), Eq(11.1f));
    EXPECT_THAT(v.at(1), Eq(22.2f));
    EXPECT_THAT(v.at(2), Eq(33.3f));
  }
}

TEST(Vector, returnElementWiseSumWhenAdded)
{
  {
    auto v = Vector<int, 3>(1, 2, 3) + Vector<int, 3>(10, 20, 30);
    EXPECT_THAT(v.at(0), Eq(11));
    EXPECT_THAT(v.at(1), Eq(22));
    EXPECT_THAT(v.at(2), Eq(33));
  }
  {
    // it is OK: 'int' -> 'float' without narrowing
    auto v = Vector<float, 3>(10.1f, 20.2f, 30.3f) + Vector<int, 3>(1, 2, 3);
    EXPECT_THAT(v.at(0), Eq(11.1f));
    EXPECT_THAT(v.at(1), Eq(22.2f));
    EXPECT_THAT(v.at(2), Eq(33.3f));
  }
}

TEST(Vector, returnScalarMultiplicationCompound)
{
  {
    auto v = Vector<int, 3>(1, 2, 3);
    v *= 10;

    EXPECT_THAT(v.at(0), Eq(10));
    EXPECT_THAT(v.at(1), Eq(20));
    EXPECT_THAT(v.at(2), Eq(30));
  }
  {
    // it is OK: 'int' -> 'float' without narrowing
    auto v = Vector<float, 3>(10.11f, 20.22f, 30.33f);
    v *= 10;

    EXPECT_THAT(v.at(0), Eq(101.1f));
    EXPECT_THAT(v.at(1), Eq(202.2f));
    EXPECT_THAT(v.at(2), Eq(303.3f));
  }
}

TEST(Vector, returnScalarMultiplication)
{
  {
    auto v = Vector<int, 3>(1, 2, 3) * 10;

    EXPECT_THAT(v.at(0), Eq(10));
    EXPECT_THAT(v.at(1), Eq(20));
    EXPECT_THAT(v.at(2), Eq(30));
  }
  {
    // it is OK: 'int' -> 'float' without narrowing
    auto v = Vector<float, 3>(10.11f, 20.22f, 30.33f) * 10;

    EXPECT_THAT(v.at(0), Eq(101.1f));
    EXPECT_THAT(v.at(1), Eq(202.2f));
    EXPECT_THAT(v.at(2), Eq(303.3f));
  }
}
