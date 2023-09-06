#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int client_sockets[2] = {0, 0};
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int sockfd;
    int client_id;
} ClientData;

void *handle_client(void *arg);

int main() {
    int server_sockfd;
    struct sockaddr_in server_address;
    socklen_t client_len;
    pthread_t thread;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1) {
        perror("socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(50000);

    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server_sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Server is running on 0.0.0.0:50000\n");

    while (1) {
        int client_sockfd;
        struct sockaddr_in client_address;
        client_len = sizeof(client_address);

        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (client_sockfd == -1) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&lock);
        if (client_sockets[0] == 0) {
            client_sockets[0] = client_sockfd;
        } else if (client_sockets[1] == 0) {
            client_sockets[1] = client_sockfd;
        } else {
            close(client_sockfd);
            pthread_mutex_unlock(&lock);
            continue;
        }
        pthread_mutex_unlock(&lock);

        printf("New connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        ClientData *data = malloc(sizeof(ClientData));
        data->sockfd = client_sockfd;
        data->client_id = (client_sockfd == client_sockets[0]) ? 1 : 2;

        if (pthread_create(&thread, NULL, handle_client, data) != 0) {
            perror("pthread_create");
            continue;
        }
    }

    return 0;
}

void *handle_client(void *arg) {
    ClientData *data = (ClientData *)arg;
    int client_sockfd = data->sockfd;
    int client_id = data->client_id;
    char buffer[1024];
    ssize_t bytes_read;

    while (1) {
        bytes_read = recv(client_sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read <= 0) {
            printf("Client %d disconnected\n", client_id);
            break;
        }

        buffer[bytes_read] = '\0';
        printf("Received message from Client %d: %s\n", client_id, buffer);

        pthread_mutex_lock(&lock);

        if (client_sockfd == client_sockets[0] && client_sockets[1] != 0) {
            if (send(client_sockets[1], buffer, bytes_read, 0) == -1) {
                perror("send");
            }
        } else if (client_sockfd == client_sockets[1] && client_sockets[0] != 0) {
            if (send(client_sockets[0], buffer, bytes_read, 0) == -1) {
                perror("send");
            }
        }

        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);
    if (client_sockfd == client_sockets[0]) {
        client_sockets[0] = 0;
    } else if (client_sockfd == client_sockets[1]) {
        client_sockets[1] = 0;
    }
    pthread_mutex_unlock(&lock);

    free(data);
    close(client_sockfd);
    return NULL;
}
