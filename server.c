#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return 1; }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); close(s); return 1;
    }

    if (listen(s, 1) < 0) {
        perror("listen"); close(s); return 1;
    }

    struct stat file_stat;
    if (stat("index.html", &file_stat) < 0) {
        perror("stat"); close(s); return 1;
    }

    printf("Server running on port 8080...\n");

    while(1) {
        int client = accept(s, 0, 0);
        if (client < 0) { perror("accept"); continue; }

        char buf[1024];
        recv(client, buf, 1024, 0);

        int fd = open("index.html", O_RDONLY);
        if (fd < 0) { perror("open"); close(client); continue; }

        char header[128];
        int header_len = sprintf(header,
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: %ld\r\n"
            "Content-Type: text/html\r\n"
            "\r\n", file_stat.st_size);

        send(client, header, header_len, 0);
        sendfile(client, fd, 0, file_stat.st_size);

        close(fd);
        close(client);
    }
}
