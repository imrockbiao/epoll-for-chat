#pragma once

#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/epoll.h>

#include"data.h"

#define PORT 8888
#define MAXONLINE 1024

#define printfLine printf("--%s--%d--", __FILE__, __LINE__);printf

//1. 创建套接字
void sock_create(int* sfd);

//2. 绑定IP地址，端口号
void sock_bind(int* sfd);

//3. 监听
void sock_listen(int *sfd);


//1. 创建树
void epfd_create(int *epfd);

//2. fd上树
void epfd_contrl(int *epfd, int *fd);
//2. fd下数
void epfd_contrl_down(int *epfd, struct epoll_event *pfd);

//3. epfd等待返回
void epfd_wait(int *epfd, struct epoll_event* evs, int *nready);

//4. epfd处理请求连接
void epfd_deal(int *epfd, struct epoll_event* evs, int *nready, int *sfd);