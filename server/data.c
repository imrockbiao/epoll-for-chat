#include"data.h"


//1. 客户端连接
void client_accept(int *epfd, int *sfd)
{
    struct sockaddr_in cliaddr;
    char ip[16] = "";
    socklen_t len = sizeof(cliaddr);
    int cfd = accept((*sfd), (struct sockaddr*)&cliaddr, &len);
    printfLine("new client ip:%s, port:%d\n",
        inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
        ntohs(cliaddr.sin_port)
    );
    epfd_contrl(epfd, &cfd);

}


//2. 处理客户端的数据
void client_data(int *epfd, struct epoll_event *evsi)
{
    char buf[1024] = {0};
    int n = read(evsi->data.fd, buf, sizeof(buf));
    if(n<0)
    {//接收客户端的数据小于0， 说明客户端的cfd出错，此时让客户端下树
        printfLine("client_data出错\n");
        epfd_contrl_down(epfd, evsi);//这个客户端出错了，就让它下树
    }
    else if(n == 0)
    {
        //客户端关闭
        printfLine("client down\n");
        close(evsi->data.fd);//将客户端的fd关闭
        epfd_contrl_down(epfd, evsi);//这个客户端关闭，下树其cfd
    }
    else
    {
        //客户端正常发送数据
        printfLine("%s\n", buf);
        write(evsi->data.fd, buf, n);
    }
    
}