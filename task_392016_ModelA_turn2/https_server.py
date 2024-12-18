import socket
import ssl

def handle_client_connection(ssl_socket):
    try:
        # Receive data from the client (similar to SSL_read)
        data = ssl_socket.recv(1024)  # Receive up to 1024 bytes
        if data:
            print(f"Received from client: {data.decode()}")
            
            # Send a response back to the client (similar to SSL_write)
            response = "Message received and processed"
            ssl_socket.sendall(response.encode())
            print(f"Sent to client: {response}")
    except Exception as e:
        print(f"Error handling client connection: {e}")
    finally:
        ssl_socket.close()

def start_https_server():
    # Set up the server's address and port
    server_address = ('127.0.0.1', 8443)
    
    # Create a regular socket for the server
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(server_address)
    server_socket.listen(5)
    print(f"Listening on https://{server_address[0]}:{server_address[1]}")
    
    # Configure SSL context
    ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ssl_context.load_cert_chain(certfile="cert.pem", keyfile="key.pem")
    
    # Accept incoming client connections
    while True:
        # Accept a connection
        client_socket, client_address = server_socket.accept()
        print(f"Accepted connection from {client_address}")
        
        # Wrap the socket with SSL
        ssl_client_socket = ssl_context.wrap_socket(client_socket, server_side=True)
        
        # Handle the client connection
        handle_client_connection(ssl_client_socket)

if __name__ == "__main__":
    start_https_server()

