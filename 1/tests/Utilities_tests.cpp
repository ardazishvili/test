#include <gmock/gmock.h>

#include <regex>

#include "../Text.h"

using ::testing::ContainerEq;
using ::testing::Eq;
using ::testing::StartsWith;

std::string substr = "AbC";
using namespace nonstd;

TEST(RemoveReturn, BlankLineIfLineConsistsOfPattern)
{
  auto l = nonstd::string(substr.c_str());
  remove(l, substr);
  EXPECT_THAT(l, Eq(""));
}

TEST(RemoveReturn, BlankLineIfLineConsistsOfMultiplePatterns)
{
  auto l = nonstd::string(substr.c_str()) + nonstd::string(substr.c_str());
  remove(l, substr);
  EXPECT_THAT(l, Eq(""));
}

TEST(RemoveReturn, SameStringIfNoPatternsFound)
{
  auto l = nonstd::string("No patterns found");
  remove(l, substr);
  EXPECT_THAT(l, Eq("No patterns found"));
}

TEST(RemoveReturn, ValidStringIfItContainOnePatternSubstr)
{
  {
    auto l = nonstd::string("LongCamelAbCCaseString");
    remove(l, substr);
    EXPECT_THAT(l, Eq("LongCamelCaseString"));
  }

  {
    auto l = nonstd::string("String AbC with only one pattern substr");
    remove(l, substr);
    EXPECT_THAT(l, Eq("String  with only one pattern substr"));
  }

  {
    auto l = nonstd::string("AbC String with only one pattern substr");
    remove(l, substr);
    EXPECT_THAT(l, Eq(" String with only one pattern substr"));
  }

  {
    auto l = nonstd::string("String with only one pattern substr AbC");
    remove(l, substr);
    EXPECT_THAT(l, Eq("String with only one pattern substr "));
  }
}

TEST(RemoveReturn, ValidStringIfItContainMultiplePatternSubstr)
{

  {
    auto l = nonstd::string("LAbCongCamelAbCCaseString");
    remove(l, substr);
    EXPECT_THAT(l, Eq("LongCamelCaseString"));
  }

  {
    auto l = nonstd::string("StrAbCing AbC with only one pattern substr");
    remove(l, substr);
    EXPECT_THAT(l, Eq("String  with only one pattern substr"));
  }

  {
    auto l = nonstd::string("AbC StrAbCing with only one pattern substr");
    remove(l, substr);
    EXPECT_THAT(l, Eq(" String with only one pattern substr"));
  }

  {
    auto l = nonstd::string("StrAbCing with only one pattern substr AbC");
    remove(l, substr);
    EXPECT_THAT(l, Eq("String with only one pattern substr "));
  }
}

TEST(Remove, IsCaseSensitive)
{
  auto l = nonstd::string("ABC Check if abC remove is case aBc sensitive abc");
  remove(l, substr);
  EXPECT_THAT(l, Eq("ABC Check if abC remove is case aBc sensitive abc"));
}

TEST(RemoveCanAccept, SpecialCharsAsPattern)
{
  auto l = nonstd::string("exa.[]*&mple");
  remove(l, std::string(".[]*&"));
  EXPECT_THAT(l, Eq("example"));
}

TEST(RemoveCanAccept, SpacesAsPattern)
{
  auto l = nonstd::string("exa   mple");
  remove(l, "   ");
  EXPECT_THAT(l, Eq("example"));
}

TEST(Sort, IsNotCaseSensitive)
{
  {
    auto lines = Lines{ "one", "One" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "one", "One" }));
  }
  {
    auto lines = Lines{ "one", "onE" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "one", "onE" }));
  }
}

TEST(Sort, UseLexicalOrderComparison)
{
  {
    auto lines = Lines{ "abd", "abc" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "abc", "abd" }));
  }
  {
    auto lines = Lines{ "aBcDe1235", "abcde1234" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "abcde1234", "aBcDe1235" }));
  }
  {
    auto lines = Lines{ "aBcDe1235", "abcde123" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "abcde123", "aBcDe1235" }));
  }
}

TEST(Sort, CanProcessEqualStrings)
{
  {
    auto lines = Lines{ "abc", "aBc", "abc", "AbC", "abc", "ABC" };
    sort(lines);
    EXPECT_THAT(lines,
                ContainerEq(Lines{ "abc", "aBc", "abc", "AbC", "abc", "ABC" }));
  }
  {
    auto lines = Lines{ "abc", "def", "abc" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "abc", "abc", "def" }));
  }
}

TEST(Sort, CanProcessBlankStrings)
{
  {
    auto lines = Lines{ "", "aBc", "", "AbC", "", "ABC" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "", "", "", "aBc", "AbC", "ABC" }));
  }
  {
    auto lines = Lines{ "", "def", "" };
    sort(lines);
    EXPECT_THAT(lines, ContainerEq(Lines{ "", "", "def" }));
  }
}
