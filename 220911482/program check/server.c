#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt error");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    int bytes_read = read(new_socket, buffer, MAX_BUFFER_SIZE - 1);
    buffer[bytes_read] = '\0';

    char* manipal = "manipal";
    char* at = "@";
    char* num = "123";

    char* manipal_ptr = strstr(buffer, manipal);
    char* at_ptr = strstr(buffer, at);
    char* num_ptr = strstr(buffer, num);

    FILE* alpha_file = fopen("alpha.txt", "w");
    fwrite(manipal_ptr, at_ptr - manipal_ptr, 1, alpha_file);
    fclose(alpha_file);

    FILE* spec_file = fopen("spec.txt", "w");
    fwrite(at_ptr, 1, 1, spec_file);
    fclose(spec_file);

    FILE* num_file = fopen("num.txt", "w");
    fwrite(num_ptr, strlen(num_ptr), 1, num_file);
    fclose(num_file);

    close(new_socket);
    close(server_fd);
    return 0;
}


