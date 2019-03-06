#include <iostream>

#include <boost/optional.hpp>
#include <boost/signals2.hpp>

class Foo {};

int main()
{
  boost::signals2::signal<Foo(bool)> s{};
  boost::signals2::connection c = s.connect(
    [] (bool isThrow) -> Foo {

      std::cout << "Hello, world!\n";

      if(isThrow)
        throw std::exception{};

      return Foo{};
    });

  try {
    boost::optional<Foo> r = s(true);
    if(r)
    {
      Foo f = r.get();
      std::cout << "Hello, Foo!\n";
    }
    else
    {
      std::cout << "Empty\n";
    }
  }
  catch(std::exception& ex)
  {
    std::cout << "Exception is thrown!\n";
  }
  c.disconnect();
}
