#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ssl;

class client
{
public:
    client(io_context& io_context, const std::string& host, const std::string& port)
        : context_(io_context, context::tlsv12_client),
          socket_(io_context, context_)
    {
        host_ = host;
        port_ = port;
    }

    void connect()
    {
        io_service::strand strand(context_.get_io_service());
        resolver resolver(context_.get_io_service());

        try
        {
            tcp::resolver::query query(host_, port_);
            tcp::resolver::iterator iterator = resolver.resolve(query);
            tcp::endpoint endpoint = *iterator;

            socket_.set_verify_mode(verify_peer);
            socket_.set_verify_callback(
                [this](bool preverified, boost::asio::ssl::verify_context& ctx) {
                    // Verify the server's certificate
                    string subject_name = ctx.subject_name();
                    cout << "Verifying subject name: " << subject_name << endl;
                    // Add your certificate verification logic here
                    return true;
                });

            socket_.lowest_layer().connect(endpoint);
            socket_.handshake(stream_base::client);

            do_read();
        }
        catch (system_error& e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

private:
    void do_read()
    {
        char buffer[1024];
        socket_.async_read_some(buffer(buffer), [this, buffer](error_code ec, size_t length) {
            if (!ec)
            {
                cout << "Received: " << string(buffer, length) << endl;
                do_write();
            }
            else
            {
                cerr << "Error reading: " << ec.what() << endl;
            }
        });
    }

    void do_write()
    {
        string request = "GET / HTTP/1.1\r\nHost: " + host_ + "\r\n\r\n";
        async_write(socket_, buffer(request), [this](error_code ec, size_t) {
            if (!ec)
            {
                do_read();
            }
            else
            {
                cerr << "Error writing: " << ec.what() << endl;
            }
        });
    }

    io_context& io_context_;
    context context_;
    stream_socket<context> socket_;
    string host_;
    string port_;
};

int main()
{
    io_context io_context;
    client c(io_context, "example.com", "443"); // Replace with your server host and port

    c.connect();

    io_context.run();

    return 0;
}
