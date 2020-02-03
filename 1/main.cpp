#include <iostream>

#include "Text.h"

int main(int argc, char** argv)
{
  auto text = Text("/home/roman/repos/test/1/sample.txt");
  text.remove("ABC");
  text.sort();
  text.toFile();
}
