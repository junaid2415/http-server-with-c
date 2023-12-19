#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CONNECTIONS 10

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t address_size = sizeof(server_address);

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept incoming connections
    while (1) {
        // Accept a connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size)) == -1) {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        // Handle the connection (this is where you'll implement the logic for handling HTTP requests)
        // For now, let's just print a message indicating the connection
        printf("Connection accepted from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        // Close the client socket (in a real server, you would handle the connection here)
        close(client_socket);
    }

    // Close the server socket (this part will not be reached in this basic example)
    close(server_socket);

    return 0;
}
