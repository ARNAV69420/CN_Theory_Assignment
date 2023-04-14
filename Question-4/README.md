## How to Run?
To generate the executables, run:
```
    g++ client.cpp -o client
    g++ server.cpp -o server
```
To run the server, run:
```
    ./server welcome to my humble server
    # the string following the executable is the welcome message(anything you want)
    # server runs forever... ^C to kill it.
```
To run the client , run
```
    ./client localhost
    # localhost may be replaced with address of the server
```

#### Client1-Side Output:
```
    Server Says: 
    Welcome to my humble server 
```
#### Client 2-Side  Output:
```
    Server Says: 
    Welcome to my humble server 
```
Clients just one message to server and recieve one message then close the socket.
#### Server-Side Output:
```
    Recieved request from client: Hello Server
    Recieved request from client: Hello Server
```
The Server keeps reciving requests and can respond as many times as we want.
Since we use UDP Sockets, some messages may drop.
