#include <iostream>

#include <boost/asio.hpp>

void helloFunction()
{
  std::cout << "Hello function\n";
}

int main()
{
  std::cout << "Hello boost\n";

  boost::asio::io_context ioContext;

  std::cout << "Dispatch\n";
  boost::asio::dispatch(ioContext, helloFunction);

  std::cout << "run\n";
  ioContext.run();

  std::cout << "End\n";
  return 0;
}
