import socket

def start_server(host='127.0.0.1', port=12345):
    """
    Starts a simple TCP server that receives data and sends back a confirmation.

    :param host: The IP address to bind the server (default is localhost).
    :param port: The port to bind the server (default is 12345).
    """
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(5)
        print(f"Server started at {host}:{port}")

        while True:
            # Accept a new client connection
            client_socket, client_address = server_socket.accept()
            print(f"Connection established with {client_address}")

            with client_socket:
                while True:
                    # Receive data from the client
                    data = client_socket.recv(1024)
                    if not data:
                        break

                    print(f"Received from {client_address}: {data.decode('utf-8')}")

                    # Send confirmation back to the client
                    confirmation_message = "Data received successfully"
                    client_socket.sendall(confirmation_message.encode('utf-8'))

if __name__ == "__main__":
    start_server()

