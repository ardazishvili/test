#ifndef TEXT_H
#define TEXT_H

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string.h>
#include <vector>

using namespace std::string_literals;

namespace nonstd
{
struct ci_traits : public std::char_traits<char>
{
  static int compare(const char* c1, const char* c2, size_t n)
  {
    return strcasecmp(c1, c2);
  }
};
std::basic_ostream<char>& operator<<(
  std::basic_ostream<char>& os,
  const std::basic_string<char, ci_traits> str);

using string = std::basic_string<char, ci_traits>;
using Lines = std::vector<string>;
void remove(nonstd::string& l, const std::string& p);
void sort(Lines& lines);
}

class Text
{
public:
  explicit Text(const std::string& path);
  Text(const Text&) = delete;
  Text(Text&&) = delete;
  Text& operator=(const Text&) = delete;
  Text& operator=(Text&&) = delete;
  ~Text() = default;

  void remove(const std::string& pattern);
  void sort();
  void toFile();

private:
  nonstd::Lines _lines;
  std::string _path;
};

#endif
