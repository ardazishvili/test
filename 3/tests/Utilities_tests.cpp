#include <gmock/gmock.h>

#include "../Vector.h"

using ::testing::Eq;

TEST(DotProduct, returnScalar)
{
  auto a = linal::dot(linal::Vector<int, 3>(1, 2, 3),
                      linal::Vector<int, 3>(10, 20, 30));
  EXPECT_THAT(a, Eq(140));
}

TEST(CrossProduct, ofCollinearVectorsReturnZeroVector)
{
  auto a = linal::cross(linal::Vector<int, 3>(1, 2, 3),
                        linal::Vector<int, 3>(10, 20, 30));

  EXPECT_THAT(a.dim(), Eq(3));
  EXPECT_THAT(a.at(0), Eq(0));
  EXPECT_THAT(a.at(1), Eq(0));
  EXPECT_THAT(a.at(2), Eq(0));
}

TEST(CrossProduct, SELFreturnZeroVector)
{
  auto a = linal::cross(linal::Vector<int, 3>(1, 2, 3),
                        linal::Vector<int, 3>(1, 2, 3));

  EXPECT_THAT(a.dim(), Eq(3));
  EXPECT_THAT(a.at(0), Eq(0));
  EXPECT_THAT(a.at(1), Eq(0));
  EXPECT_THAT(a.at(2), Eq(0));
}

TEST(CrossProduct, isAnticommutative)
{
  auto a = linal::Vector<int, 3>(1, 2, 3);
  auto b = linal::Vector<int, 3>(10, 20, 30);
  auto x = linal::cross(a, b);
  auto y = linal::cross(b, a);

  EXPECT_THAT(x.at(0), Eq(-y.at(0)));
  EXPECT_THAT(x.at(1), Eq(-y.at(1)));
  EXPECT_THAT(x.at(2), Eq(-y.at(2)));
}
