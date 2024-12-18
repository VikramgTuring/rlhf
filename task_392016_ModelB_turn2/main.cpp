#include <iostream>
#include <string>
#include <cstdlib>
#include <openssl/ssl.h>
#include <openssl/err.h>

#ifdef WIN32
    #pragma comment(lib, "libeay32.lib")
    #pragma comment(lib, "ssleay32.lib")
#endif

const char* SERVER_ADDRESS = "example.com";
const int SERVER_PORT = 443;

// SSL/TLS connection class
class SecureConnection {
public:
    SecureConnection()
    {
        SSL_library_init();
        ctx = SSL_CTX_new(TLS_client_method());
        if (!ctx) {
            handleError("Error creating SSL context");
        }
    }

    ~SecureConnection()
    {
        SSL_CTX_free(ctx);
    }

    bool connect()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            handleError("Error creating socket");
            return false;
        }

        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &serverAddr.sin_addr);
        serverAddr.sin_port = htons(SERVER_PORT);

        if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            handleError("Error connecting to server");
            close(sock);
            return false;
        }

        ssl = SSL_new(ctx);
        if (!ssl) {
            handleError("Error creating SSL object");
            close(sock);
            return false;
        }

        SSL_set_fd(ssl, sock);
        int ret = SSL_connect(ssl);
        if (ret <= 0) {
            handleError("Error establishing SSL connection");
            SSL_free(ssl);
            close(sock);
            return false;
        }

        // Validate server certificate
        X509* serverCert = SSL_get_peer_certificate(ssl);
        if (serverCert != nullptr) {
            int verifyResult = SSL_get_verify_result(ssl);
            if (verifyResult != X509_V_OK) {
                handleError("Server certificate verification failed");
                X509_free(serverCert);
                SSL_free(ssl);
                close(sock);
                return false;
            }
            X509_free(serverCert);
        } else {
            handleError("Server certificate not available");
            SSL_free(ssl);
            close(sock);
            return false;
        }

        return true;
    }

    bool writeData(const char* data, size_t len)
    {
        int ret = SSL_write(ssl, data, len);
        if (ret <= 0) {
            handleError("Error writing data");
            return false;
        }
        return true;
    }

    bool readData(char* buf, size_t len)
    {
        int ret = SSL_read(ssl, buf, len);
        if (ret <= 0) {
            handleError("Error reading data");
            return false;
        }
        return true;
    }
