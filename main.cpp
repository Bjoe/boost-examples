#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>

int main()
{
  boost::filesystem::path file{"example.csv"};
  boost::filesystem::ifstream infile{file};

  typedef boost::tokenizer<boost::escaped_list_separator<char>> tokenizer;

  for(std::string line; std::getline(infile, line);) {
    tokenizer tok{line};
    for (const auto &t : tok)
        std::cout << t << '\n';
  }
}
