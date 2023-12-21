#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CONNECTIONS 2

char *get_nth_substring(const char *input, int n) {
    // Find the start and end positions of the nth substring
    int substring_start = 0;
    int substring_end = 0;
    int substring_count = 0;

    while (input[substring_end] != '\0') {
        if (input[substring_end] == ' ') {
            ++substring_count;
            if (substring_count == n) {
                break;  // Found the end of the nth substring
            }
            substring_start = substring_end + 1;  // Move to the start of the next substring
        }
        ++substring_end;
    }

    // If n is greater than the number of substrings, or if n is 0, return NULL
    if (substring_count < n || n == 0) {
        return NULL;
    }

    // Allocate memory for the nth substring
    int substring_length = substring_end - substring_start;
    char *substring = (char *)malloc(substring_length + 1);
    if (substring == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the nth substring
    strncpy(substring, input + substring_start, substring_length);
    substring[substring_length] = '\0';  // Null-terminate the substring

    return substring;
}



void handle_request(int client_socket, char *buffer) {
    // sleep(2);
    char *method = get_nth_substring(buffer, 1);
    char *protocol = get_nth_substring(buffer,3);
    const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!\n";

    if(strcmp(protocol, "HTTP/1.1") != 0) {
        response = "Not a valid HTTP request";
        write(client_socket, response, strlen(response));
        return ;
    }
    else{

        if(strcmp("GET", method) == 0){
            response = "HTTP/1.1 200 OK\r\nContent-Length: 50\r\n\r\nHello, World! from GET request\n";
            write(client_socket, response, strlen(response));
        }
        else if(strcmp("PUT", method) == 0){
            response = "HTTP/1.1 200 OK\r\nContent-Length: 50\r\n\r\nHello, World! from PUT request\n";
            write(client_socket, response, strlen(response));
        }
        else if(strcmp("POST", method) == 0){
            response = "HTTP/1.1 200 OK\r\nContent-Length: 50\r\n\r\nHello, World! from POST request\n";
            write(client_socket, response, strlen(response));
        }
        else if(strcmp("DELETE", method) == 0){
            response = "HTTP/1.1 200 OK\r\nContent-Length: 50\r\n\r\nHello, World! from DELETE request\n";
            write(client_socket, response, strlen(response));
        }
        else{
            response = "HTTP/1.1 200 OK\r\nContent-Length: 50\r\n\r\nHello, World! Not a GET/POST/PUT/DELETE request\n";
            write(client_socket, response, strlen(response));
        }

    }




}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t address_size = sizeof(server_address);
    char buffer[256];

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
        read(client_socket, buffer, sizeof(buffer));
        printf("%s", buffer);
        handle_request(client_socket, buffer);
        // write(client_socket, "Hello", strlen("Hello"));
        printf("\n %d \n", client_socket);
        // Close the client socket (in a real server, you would handle the connection here)
        // close(client_socket);
    }

    // Close the server socket (this part will not be reached in this basic example)
    close(server_socket);

    return 0;
}
