// Vulnerable code snippet in uClibc DNS client library

#include <stdint.h>

#include <stdlib.h>

 

#define DNS_PORT 53

 

uint16_t generate_transaction_id() {

    static uint16_t transaction_id = 0;

    return transaction_id++; // Transaction ID increments predictably

}

 

// In the DNS request function

int send_dns_request() {

    struct dns_packet packet;

    packet.transaction_id = generate_transaction_id(); // Predictable ID

 

    // No source port randomization, uses fixed DNS_PORT

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in dest;

    dest.sin_port = htons(DNS_PORT);

    dest.sin_addr.s_addr = inet_addr("8.8.8.8"); // Example DNS server

 

    sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&dest, sizeof(dest));

    close(sock);

}
