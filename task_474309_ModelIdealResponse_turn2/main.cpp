#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h> // For sockaddr_in
#include <unistd.h>    // For close()

typedef struct {
    struct timespec send_time;
    struct timespec transport_process_time;
    struct timespec link_process_time;
    struct timespec receive_time;
} PacketTiming;

void log_time_diff(const char *stage, struct timespec start, struct timespec end) {
    long diff_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    printf("%s latency: %ld ns\n", stage, diff_ns);
}

void send_packet(int socket, const char *data, size_t data_len) {
    PacketTiming timing;

    // Time when the packet is sent from the application layer
    clock_gettime(CLOCK_MONOTONIC, &timing.send_time);

    // Simulating the application sending the packet
    printf("Sending packet: %s\n", data);

    // Send the packet
    ssize_t sent_bytes = send(socket, data, data_len, 0);
    if (sent_bytes < 0) {
        perror("Send error");
        return;
    }

    // Timing simulated transport layer processing
    clock_gettime(CLOCK_MONOTONIC, &timing.transport_process_time);

    // Simulating transport layer processing delay
    printf("Transport layer processing complete.\n");

    // Timing simulated Link layer processing
    clock_gettime(CLOCK_MONOTONIC, &timing.link_process_time);

    // Typical network send call would now occur. Here we simulate it
    printf("Link layer processing complete, waiting for response.\n");

    // Simulating receive response
    char buffer[1024];
    ssize_t received_bytes = recv(socket, buffer, sizeof(buffer), 0);
    if (received_bytes < 0) {
        perror("Receive error");
        return;
    }
    buffer[received_bytes] = '\0'; // Null-terminate the received data
    printf("Received response: %s\n", buffer);

    // Capture reception time in application
    clock_gettime(CLOCK_MONOTONIC, &timing.receive_time);

    // Log the latency measurements
    log_time_diff("Application to Transport", timing.send_time, timing.transport_process_time);
    log_time_diff("Transport Processing", timing.transport_process_time, timing.link_process_time);
    log_time_diff("Link Processing to Reception", timing.link_process_time, timing.receive_time);
    printf("Total round-trip latency: %ld ns\n",
           (timing.receive_time.tv_sec - timing.send_time.tv_sec) * 1e9 +
           (timing.receive_time.tv_nsec - timing.send_time.tv_nsec));
}

int main() {
    int sock;
    struct sockaddr_in server_addr;

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set server details
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345); // Server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        close(sock);
        return 1;
    }

    printf("Connected to server.\n");

    // Send a packet
    const char *message = "Hello, Network!";
    send_packet(sock, message, strlen(message));

    // Close socket
    close(sock);

    return 0;
}

