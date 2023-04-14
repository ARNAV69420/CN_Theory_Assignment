## How to Run?
To generate the executables, run:
```
    g++ client.cpp -o client
    g++ server.cpp -o server
```
To run the server, run:
```
    ./server
    #server runs forever... ^C to kill it.
```
To run the client , run
```
    ./client localhost arnav says hi 
    # localhost may be replaced with address of the server and the string following
    # the address is the message
```

#### Client-Side Output:
```
    Sent Message to Server
```
Client just sends one message to server and closes the socket.
#### Server-Side Output:
```
    Waiting for Connections on port42069
    Client 1 sent : 
    arnav says hi 
```
The Server keeps listening for clients and can recieve as many messages as we want.
