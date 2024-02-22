#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 8080

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        return 1;
    }

    int client_fd, new_socket;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char* server_ip = argv[1];
    char* manipal = "manipal";
    char* at = "@";
    char* num = "123";

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    int bytes_read = read(client_fd, buffer, MAX_BUFFER_SIZE - 1);
    buffer[bytes_read] = '\0';

    char* alpha_file_start = strstr(buffer, "manipal");
    char* spec_file_start = strstr(buffer, "@");
    char* num_file_start = strstr(buffer, "@" + 1);

    if (alpha_file_start && spec_file_start && num_file_start) {
        char alpha_file_name[MAX_BUFFER_SIZE] = {0};
        char spec_file_name[MAX_BUFFER_SIZE] = {0};
        char num_file_name[MAX_BUFFER_SIZE] = {0};

        int alpha_len = spec_file_start - alpha_file_start - 1;
        int spec_len = num_file_start - spec_file_start - 1;
        int num_len = strlen(num) - 1;

        strncpy(alpha_file_name, alpha_file_start, alpha_len);
        strncpy(spec_file_name, spec_file_start + 1, spec_len);
        strncpy(num_file_name, num_file_start + 1 + num_len, strlen(num_file_start + 1 + num_len) - (num_file_start + 1 + num_len - num_file_start));

        printf("Extracted manipal: %s\n", alpha_file_name);
        printf("Extracted number: %s\n", num_file_name);
        printf("Extracted special: %s\n", spec_file_name);
    }

    close(client_fd);
    return 0;
}

 
