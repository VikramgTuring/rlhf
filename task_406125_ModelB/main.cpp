#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;
using namespace boost::asio::ssl;

class ssl_client
{
public:
    ssl_client(io_context& io_context, const std::string& host, const std::string& port)
        : io_context_(io_context),
          socket_(io_context),
          resolver_(io_context)
    {
        strand_.reset(new strand(io_context));

        ssl_socket_.emplace(strand_, context::sslv23_client);

        // Load the root certificate authority.
        if (!load_root_certificate("root.crt"))
        {
            std::cerr << "Failed to load root certificate\n";
            return;
        }

        resolve(host, port);
    }

private:
    void resolve(const std::string& host, const std::string& port)
    {
        ip::tcp::resolver::query query(host, port);

        resolver_.async_resolve(
            query,
            boost::bind(&ssl_client::handle_resolve, this, boost::asio::placeholders::error,
                        boost::asio::placeholders::iterator));
    }

    void handle_resolve(const error_code& error, ip::tcp::resolver::iterator endpoint_iterator)
    {
        if (error)
        {
            std::cerr << "Resolution failed: " << error.message() << "\n";
            return;
        }

        socket_.async_connect(
            *endpoint_iterator,
            boost::bind(&ssl_client::handle_connect, this, boost::asio::placeholders::error));
    }

    void handle_connect(const error_code& error)
    {
        if (error)
        {
            std::cerr << "Connection failed: " << error.message() << "\n";
            return;
        }

        ssl_socket_->async_handshake(
            stream_base::client,
            boost::bind(&ssl_client::handle_handshake, this, boost::asio::placeholders::error));
    }

    void handle_handshake(const error_code& error)
    {
        if (error)
        {
            std::cerr << "Handshake failed: " << error.message() << "\n";
            return;
        }

        std::string message;
        std::cout << "Sending request...\n";
        std::cout << "GET / HTTP/1.1\r\n";
        std::cout << "Host: example.com\r\n";
        std::cout << "Connection: close\r\n";
        std::cout << "\r\n";
