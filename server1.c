#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
int is_even(int num){
return num % 2 == 0;
}
int main(){
char *ip = "127.0.0.1";
int port = 5566;
int server_sock, client_sock;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
int num;
int n;
server_sock = socket(AF_INET, SOCK_STREAM, 0);
if (server_sock < 0){
perror("[-]Socket error");
exit(1);
}
printf("[+]TCP server socket created.\n");
memset(&server_addr, '\0', sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);
n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
if (n < 0){
perror("[-]Bind error");
exit(1);
}
printf("[+]Bind to the port number: %d\n", port);
listen(server_sock, 5);
printf("Listening...\n");
20Z361
while(1){
addr_size = sizeof(client_addr);
client_sock = accept(server_sock, (struct sockaddr*)&client_addr,
&addr_size);
printf("[+]Client connected.\n");
while(1){
recv(client_sock, &num, sizeof(num), 0);
printf("Client: The number is %d\n", num);
if (num == -1)
break;
printf("The square of %d is %d\n", num, num*num);
}
close(client_sock);
printf("[+]Client disconnected.\n\n");
}
return 0;
}
