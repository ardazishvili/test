#include <gmock/gmock.h>

#include "../Text.h"

TEST(Text, ThrowOnInvalidPath)
{
  EXPECT_ANY_THROW(Text("@#&*"));
}

TEST(Text, ThrowOnDirectoryPath)
{
  EXPECT_ANY_THROW(Text("."));
}
