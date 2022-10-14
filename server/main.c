#include "main.h"

int main()
{
    printf("the Server start ...\n");

    //1.创建套接字，绑定，监听
    int sfd;    
    sock_create(&sfd);
    sock_bind(&sfd);
    sock_listen(&sfd);

    printfLine("sfd = %d\n", sfd);

    //2. 创建根
    int epfd;
    struct epoll_event evs[MAXONLINE];//根节点发生了变化就把节点存储到这个数组里面
    epfd_create(&epfd);         //创建树
    epfd_contrl(&epfd, &sfd);   //sfd上树，用于侦听客户端的连接

    //3. 等待某个根节点发生变化
    while(1)
    {
        int nready =0;
        epfd_wait(&epfd, evs, &nready);
        epfd_deal(&epfd, evs, &nready, &sfd);        
    }
    printf("the Server done ...\n");
    return 0;
}