#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
#define GOUP "\033[A\r"
#define CLR "\e[2J\e[H"

#define PORT 42069
#define MAX_SIZE 1024
#define pb push_back 
#define eb emplace_back
using namespace std;
void err(string s)
{
    perror(s.c_str()); exit(1);
}
class connector
{
    sockaddr_in saddr;
    int sockfd;
    socklen_t len;
    public:
    connector(uint16_t port,int socket_type) 
    {
        sockfd=socket(AF_INET,socket_type,0);
        if(!~sockfd)    err("cant create socket");
    }
    void clearstructures(){
        memset(&saddr,0,sizeof(sockaddr));
    }
    void fillserver(){
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(PORT);
        saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    }
    void fillclient(string addr){
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(PORT);
        if(!~inet_pton(AF_INET,addr.c_str(),&saddr.sin_addr))    err("wrong server address");
    }
    void bindsocket(){
        int reuse = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
                perror("setsockopt(SO_REUSEADDR) failed");
        #ifdef SO_REUSEPORT
                if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0) 
                        perror("setsockopt(SO_REUSEPORT) failed");
        #endif
        if(!~bind(sockfd,(sockaddr *)&saddr,sizeof saddr))  err("cannot bind socket");
    }

    //client side functions
    int connectToServer()
    {
        if(!~connect(sockfd,(sockaddr *)&saddr,sizeof saddr))   err("cannot connect");
        return sockfd;
    }

    //server side functions
    void listenForClients()
    {
        if(!~listen(sockfd,5))  err("cannot listen");
        cout<<"Waiting for Connections on port"<<PORT<<endl;
    }
    int acceptNow()
    {
        int new_fd;
        socklen_t a=sizeof(saddr);
        if(!~(new_fd=accept(sockfd,(sockaddr *)&saddr,(socklen_t *)&a))) err("cannot accept");
        return new_fd;
    }
    void closeServer()
    {
        close(sockfd);
    }
    // for UDP sockets
    string recieve()
    {
        memset(&saddr, 0, sizeof(saddr));
        char buf[MAX_SIZE];
        int num=0;
        len=sizeof(saddr);
        if(!~(num=recvfrom(sockfd,buf,MAX_SIZE-1,MSG_WAITALL,(struct sockaddr *)&saddr,&len))) {perror("cannot read"); return string();}
        buf[num]='\0';
        return string(buf);
    }
    bool sendy(string s)
    {
        len=sizeof(saddr);
        if(!~sendto(sockfd,&s[0],s.size(),MSG_CONFIRM,(const struct sockaddr *)&saddr,len)) {perror("cannot send"); return 0;}
        return 1;
    }
};
//common functions()
class comms
{
    int fd;
    public:
    comms(int f) {fd=f;}
    string recieve()
    {
        char buf[MAX_SIZE];
        int num=0;
        if(!~(num=recv(fd,buf,MAX_SIZE-1,0))) {perror("cannot read"); return string();}
        buf[num]='\0';
        return string(buf);
    }
    bool sendy(string s)
    {
        if(!~send(fd,&s[0],s.size(),0)) {perror("cannot send"); return 0;}
        return 1;
    }
    void disconnect()
    {
        close(fd);
    }
};
int main(int argc,char **argv)
{
    string s;
    connector server(PORT,SOCK_DGRAM);
    server.clearstructures();
    server.fillserver();
    server.bindsocket();
    string welcome_message;
    for(int i=1;i<argc;i++)
        welcome_message+=string(argv[i])+" ";
    while(1){
        string req=server.recieve();
        cout<<"Recieved request from client: "<<req<<endl;
        server.sendy(welcome_message);
    }
    server.closeServer();
    return 0;
}	
