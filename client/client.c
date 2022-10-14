#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>


#define PORT 8888
#define SERV_IP "192.168.109.129"
#define LEN 20

int main(int argc, char *argv[])
{
    printf("启动客户端!\n");
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd < 0 )
    {
        printf("cfd创建失败，直接退出\n");
        exit(0);
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    inet_pton(AF_INET, SERV_IP, &server_addr.sin_addr.s_addr); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    int ret_connect = connect(cfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret_connect<0)
    {
        printf("连接错误！\n");
        printf("ret_connect = %d\n", ret_connect);
        exit(0);
    }

    
    fd_set allfds;
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_ZERO(&allfds);

    FD_SET(0, &allfds);
    FD_SET(cfd, &allfds);    
    
    char buf[LEN]="";
    memset(buf, 0, sizeof(buf));

    while (1)
    {   
        readfds = allfds;
        int ret_select = select(5, &readfds, NULL, NULL, NULL);
        if(ret_select<0)
        {
            perror("select错误\n");
            exit(0);
        }
        else if(ret_select == 0)
        {
            continue;
        }
        else
        {
            if(FD_ISSET(0, &readfds))
            {
                read(0, buf, sizeof(buf)); 
                write(cfd, buf, sizeof(buf));
            }
            else if(FD_ISSET(cfd, &readfds))
            {
                read(cfd, buf, sizeof(buf)); 
                printf("收到消息 : %s", buf);
                memset(buf, 0, sizeof(buf));
            }
        }     
    }    
    close(cfd);
    return 0;
}
