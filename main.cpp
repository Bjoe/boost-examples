#include <boost/asio.hpp>
#include <list>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 500

int main()
{
    std::string name{"www.heise.de"};


    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // Give only ipv4 back // AF_UNSPEC; /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    int s = ::getaddrinfo(name.c_str(), "", &hints, &result);
    if (s == 0) {
        char ipstr[INET6_ADDRSTRLEN];
        for (struct addrinfo *rp = result; rp != nullptr; rp = rp->ai_next) {
            std::cout << "rp->ai_family: " << rp->ai_family << '\n';
            std::cout << "rp->ai_socktype: " << rp->ai_socktype << '\n';
            std::cout << "rp->ai_protocol: " << rp->ai_protocol << '\n';
            std::cout << "rp->ai_addr: " << rp->ai_addr << '\n';
            std::cout << "rp->ai_addrlen: " << rp->ai_addrlen << '\n';

            void *addr;
            std::string ipver{};

                // get the pointer to the address itself,
                // different fields in IPv4 and IPv6:
                if (rp->ai_family == AF_INET) { // IPv4
                    struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
                    addr = &(ipv4->sin_addr);
                    ipver = "IPv4";
                } else { // IPv6
                    struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
                    addr = &(ipv6->sin6_addr);
                    ipver = "IPv6";
                }

                // convert the IP to a string and print it:
                inet_ntop(rp->ai_family, addr, ipstr, sizeof ipstr);
                printf("  %s: %s\n", ipver.c_str(), ipstr);
        }
    } else {
        std::cerr << "getaddrinfo: " << gai_strerror(s) << '\n';
    }

    std::list<boost::asio::ip::address> resolvedAddresses;
    boost::asio::io_context io_context;
    try
    {
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), name, ""); // boost::asio::ip::tcp::v4() ask only for ipv4 address
        boost::asio::ip::tcp::resolver::iterator end;

        for (
             boost::asio::ip::tcp::resolver::iterator destination = resolver.resolve(query);
             end != destination;
             destination++
             )
        {
            boost::asio::ip::tcp::endpoint endpoint = *destination;
            boost::asio::ip::address ip = endpoint.address();
            std::cout << "DnsResolver::" << __func__ << "(): Resolved " << name << " to " << ip.to_string() << '\n';
        }
    }
    catch (boost::system::system_error& ec)
    {
        std::cerr << "Hostname -" << name <<
                     "- not found. Code = " << ec.code() <<
                     " What = " << ec.what() << '\n';
    }
}
