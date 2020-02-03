#include "Text.h"

namespace nonstd
{
std::basic_ostream<char>& operator<<(
  std::basic_ostream<char>& os,
  const std::basic_string<char, ci_traits> str)
{
  os << str.c_str();
}
}

Text::Text(const std::string& path) : _path(path)
{
  auto file = std::ifstream(path);
  if (!file.good() || std::experimental::filesystem::is_directory(path)) {
    throw "invalid file";
  }
  std::string tmp;
  while (std::getline(file, tmp)) {
    _lines.emplace_back(tmp.c_str());
  }
}

void Text::remove(const std::string& pattern)
{
  for (auto& s : _lines) {
    ::remove(s, pattern);
  }
}

void Text::sort()
{
  ::sort(_lines);
}

void Text::toFile()
{
  auto outFile = std::ofstream(_path + "_processed");
  std::copy(_lines.begin(),
            _lines.end(),
            std::ostream_iterator<nonstd::string>(outFile, "\n"));
}

void remove(nonstd::string& l, const std::string& p)
{
  std::regex specialChars{ R"([-[\]{}()*+?.,\^$|#\s])" };
  auto sanitized = std::regex_replace(p, specialChars, R"(\$&)");
  l = std::regex_replace(l, std::regex(sanitized), "");
}

void sort(Lines& lines)
{
  std::sort(lines.begin(), lines.end());
}

