#include <iostream>
#include <cstring>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void initOpenSSL() {
    SSL_load_error_strings();   
    OpenSSL_add_ssl_algorithms();
}

void cleanupOpenSSL() {
    EVP_cleanup();
}

// Create and return an SSL_CTX object
SSL_CTX* createContext() {
    const SSL_METHOD* method = SSLv23_client_method();
    SSL_CTX* ctx = SSL_CTX_new(method);
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

// Configure the SSL context to use certificates
void configureContext(SSL_CTX* ctx) {
    // Load the trusted CA file (Change this path as necessary)
    if (SSL_CTX_load_verify_locations(ctx, "/etc/ssl/certs/ca-certificates.crt", nullptr) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }
}

int main() {
    // Initialize OpenSSL
    initOpenSSL();
    SSL_CTX* ctx = createContext();
    configureContext(ctx);

    // Create a new SSL connection
    SSL* ssl = SSL_new(ctx);
    int server;
    struct sockaddr_in addr;

    // Establish a TCP connection to the server
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8443); // Use port 443 for HTTPS
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // Replace with server's address

    server = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(server, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        perror("Unable to connect");
        close(server);
        SSL_CTX_free(ctx);
        cleanupOpenSSL();
        return -1;
    }

    // Associate the SSL structure with the socket
    SSL_set_fd(ssl, server);

    // Perform the SSL handshake
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        std::cout << "Connected to secure server." << std::endl;

        // Send a message to the server
        const char *msg = "Hello secure server!";
        SSL_write(ssl, msg, strlen(msg));

        // Receive a response from the server
        char buf[1024];
        int bytes = SSL_read(ssl, buf, sizeof(buf));
        buf[bytes] = 0; // Null-terminate the received message
        std::cout << "Received from server: " << buf << std::endl;
    }

    // Cleanup
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(server);
    SSL_CTX_free(ctx);
    cleanupOpenSSL();
    return 0;
}
