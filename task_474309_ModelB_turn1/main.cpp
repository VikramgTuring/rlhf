#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define ETHER_ADDR_LEN 6
#define IP_ADDR_STR_LEN 16
#define MAX_PACKET_SIZE 1518 // Maximum Ethernet frame size excluding FCS

typedef struct {
    u_char dest[ETHER_ADDR_LEN];
    u_char src[ETHER_ADDR_LEN];
    u_short type;
} ether_header;

typedef struct {
    u_char version_ihl;
    u_char type_of_service;
    u_short total_length;
    u_short identification;
    u_short flags_fragment_offset;
    u_char time_to_live;
    u_char protocol;
    u_short header_checksum;
    struct in_addr source_address;
    struct in_addr destination_address;
} ip_header;

// Function to print Ethernet header information
void print_ethernet_header(ether_header *ether) {
    char ether_dest[18];
    char ether_src[18];

    // Convert MAC addresses to strings
    snprintf(ether_dest, sizeof(ether_dest), "%02x:%02x:%02x:%02x:%02x:%02x",
             ether->dest[0], ether->dest[1], ether->dest[2], ether->dest[3],
             ether->dest[4], ether->dest[5]);

    snprintf(ether_src, sizeof(ether_src), "%02x:%02x:%02x:%02x:%02x:%02x",
             ether->src[0], ether->src[1], ether->src[2], ether->src[3],
             ether->src[4], ether->src[5]);

    printf("Ethernet Header:\n");
    printf("  Destination: %s\n", ether_dest);
    printf("  Source:      %s\n", ether_src);
    printf("  Type:        0x%04x\n", ether->type);
}

// Function to print IP header information
void print_ip_header(ip_header *ip) {
    char ip_src[IP_ADDR_STR_LEN];
    char ip_dest[IP_ADDR_STR_LEN];

    // Convert IP addresses to strings
    inet_ntop(AF_INET, &ip->source_address, ip_src, IP_ADDR_STR_LEN);
    inet_ntop(AF_INET, &ip->destination_address, ip_dest, IP_ADDR_STR_LEN);

    printf("IP Header:\n");
    printf("  Version/IHL: %d\n", ip->version_ihl >> 4);
    printf("  Type of Service: %d\n", ip->version_ihl & 0xF);
    printf("  Total Length: %d\n", ntohs(ip->total_length));
    printf("  Identification: %d\n", ntohs(ip->identification));
    printf("  Flags: %d\n", (ip->flags_fragment_offset & 0xE000) >> 13);
    printf("  Fragment Offset: %d\n", ntohs(ip->flags_fragment_offset & 0x1FFF));
    printf("  Time to Live: %d\n", ip->time_to_live);
    printf("  Protocol: %d\n", ip->protocol);
    printf("  Header Checksum: 0x%04x\n", ntohs(ip->header_checksum));
    printf("  Source: %s\n", ip_src);
    printf("  Destination: %s\n", ip_dest);
}

int main() {
    // Sample packet data. In a real application, this would be captured using libpcap or another library.
    char packet[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // Destination MAC
        0x00, 0x02, 0x03, 0x04, 0x05, 0x06, // Source MAC
        0x08, 0x00,                          // EtherType: IP
        0x45, 0x00, 0x00, 0x54,             // IP Version, IHL, Total Length
        0x00, 0x00, 0x40, 0x00,             // Identification, Flags, Fragment Offset
        0x40, 0x01, 0x00, 0x00,             // Time to Live, Protocol, Header Checksum
        0xc0, 0xa8, 0x01, 0x64,             // Source IP
        0xc0, 0xa8, 0x01, 0x65,             // Destination IP
        0x08, 0x00, 0x45, 0x00, 0x00, 0x34, // Payload (start with next IP header)
        // ... rest of the packet payload ...
    };

    ether_header *ether = (ether_header *)packet;
    ip_header *ip = (ip_header *)(packet + sizeof(ether_header));

    printf("\n-- Captured Packet --\n");
    print_ethernet_header(ether);

    if (ether->type == htons(ETH_P_IP)) { // Check if EtherType is IP
        print_ip_header(ip);

        // Example: Analyze protocol and payload for potential issues
        switch (ip->protocol) {
            case IPPROTO_TCP:
                printf("\nProtocol: TCP\n");
                // Analyze TCP payload
                break;
            case IPPROTO_UDP:
                printf("\nProtocol: UDP\n");
                // Analyze UDP payload
                break;
            default:
                printf("\nProtocol: %d (Unsupported)\n", ip->protocol);
        }
    } else {
        printf("Unsupported EtherType: 0x%04x\n", ether->type);
    }

    return 0;
}

