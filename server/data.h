#pragma once 

#include<string.h>
#include"deal.h"

struct data{

    int cfd;
    int id;

}DataPackage;

//1. 客户端连接
void client_accept(int *epfd, int *sfd);

//2. 处理客户端的数据
void client_data(int *epfd, struct epoll_event *evsi);