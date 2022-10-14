#include"deal.h"

//1. 创建套接字， 绑定IP地址和端口号
void sock_create(int* sfd)
{
    (*sfd) = socket(AF_INET, SOCK_STREAM, 0);
    if((*sfd) < 0 )
    {
        perror("创建失败\n");
        printfLine("sock_create\n");
        exit(0);
    }

}

void sock_bind(int* sfd_)
{
    int sfd = *sfd_;
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //绑定
    int ret_bind = bind(sfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret_bind < 0)
    {
        printf("ret_bind = %d \n", ret_bind);
        printfLine("bind 失败\n");        
        exit(0);
    }
    printfLine;
    printf("binding\n");
}


//3. 监听
void sock_listen(int *sfd_)
{
    int sfd = *sfd_;
    int ret_listen = listen(sfd, MAXONLINE);
    if(ret_listen <0)
    {
        printf("ret_listen = %d\n", ret_listen);
        printfLine("listen失败\n");
        exit(0);
    }
    printfLine;
    printf("listening\n");
}


//1. 创建树
void epfd_create(int *epfd)
{
    (*epfd) = epoll_create(1);
}

//2. sfd上树
void epfd_contrl(int *epfd, int *sfd)
{
    struct epoll_event ev;
    ev.data.fd = *sfd;
    ev.events = EPOLLIN;
    epoll_ctl((*epfd), EPOLL_CTL_ADD, *sfd, &ev);
}


//3. epfd等待返回
void epfd_wait(int *epfd, struct epoll_event* evs, int *nready)
{
    (*nready) = epoll_wait(*epfd, evs, MAXONLINE, -1);
    if((*nready) < 0)
    {
        printfLine("epoll_wait error\n");
        exit(0);
    }
}

//4. epfd处理请求连接
void epfd_deal(int *epfd, struct epoll_event* evs, int *nready, int *sfd)
{
    for(int i = 0; i<(*nready); i++)
        {
            //当有新连接的客户端的时候
            if(evs[i].data.fd == (*sfd) && evs[i].events & EPOLLIN)
            {
                
            }
            else if(evs[i].events & EPOLLIN)
            {//客户端有数据发送

            }
        }
}