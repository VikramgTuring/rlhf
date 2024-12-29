
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void log_latency_at_each_stage(const char *stage_name, struct timespec *time_passed) {
    clock_gettime(CLOCK_MONOTONIC, time_passed);
    
    long latency_ns = (time_passed->tv_sec - timer_sent_packet.tv_sec) * 1e9 +
                      (time_passed->tv_nsec - timer_sent_packet.tv_nsec);

    printf("Latency at %s stage: %ld ns\n", stage_name, latency_ns);
}

int main() {
    // Initialise time variables
    struct timespec timer_sent_packet = {0}, timer_post_send, timer_pre_recv, timer_received_packet = {0};

    // Socket setup (psuedo-code)
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Socket error");
        return 1;
    }
    
    log_latency_at_each_stage("Initialisation", &timer_sent_packet); // Handle socket creation cost
    
    const char *data_to_send = "Hello, packet!";
    size_t data_len = strlen(data_to_send) + 1;

    // The server could be residing locally or at a remote host.
    struct sockaddr_in server_addr = { 0 };
    server_addr.sin_family = AF_INET;
    
    // Task 1: For production level code 
    // handle the connect () sys call non-blocking
    // using Async I/O calls, epoll, select.
    // Similarly for send, recv and measuring time   

    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        perror("Connect error");
        goto cleanup;
    }

    log_latency_at_each_stage("Connection", &timer_sent_packet);

    // Send data
    log_latency_at_each_stage("Packet Sending-Pre", &timer_post_send);
    ssize_t sent_bytes = send(socket_fd, data_to_send, data_len, 0);
    log_latency_at_each_stage("Packet Sending-Post", &timer_pre_recv);
    if (sent_bytes < 0) {
        perror("Send error");
        goto cleanup;
    }

    // Receive response
    char buffer[1024];
    log_latency_at_each_stage("Response-Receive-Pre", &timer_received_packet);
    ssize_t received_bytes = recv(socket_fd, buffer, sizeof(buffer), 0);
    log_latency_at_each_stage("Response-Receive-Post", &timer_received_packet);
    if (received_bytes < 0) {
        perror("Receive error");
        goto cleanup;
    }
    buffer[received_bytes] = '\0';
    printf("Received: %s\n", buffer);

cleanup:
    close(socket_fd);
    return 0;
}
    
