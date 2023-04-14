## How to Run?
To generate the executables, run:
```
    g++ client.cpp -o client
    g++ server.cpp -o server
```
To run the server, run:
```
    ./server
    # server runs forever... ^C to kill it.
```
To run the client , run
```
    ./client localhost query
    # localhost may be replaced with address of the server
    # query may be replaced with name or phone number whose other corresponding value 
    # you want to find
```

#### Client1:
###### Command:

```
    ./client localhost 555-3297 
```
###### Output:
```
    corrsponding values of name/phone number are: 
    Joshua Smith
```
#### Client2:
###### Command:

```
    ./client localhost Olivia Johnson 
```
###### Output:
```
    corrsponding values of name/phone number are: 
    555-9843
```
#### Client3:
###### Command:

```
    ./client localhost 555-9247
```
###### Output:
```
    corrsponding values of name/phone number are: 
    Isabella Lee
```
#### Client4:
###### Command:

```
    ./client localhost Leah Kim
```
###### Output:
```
    corrsponding values of name/phone number are: 
    555-1387
```
#### Server-Side Output:
```
    Recieved Request for 555-3297
    Recieved Request for Olivia Johnson
    Recieved Request for 555-9247
    Recieved Request for Leah Kim
```
The Server keeps reciving requests and can respond as many times as we want.
Since we use UDP Sockets, some messages may drop.

## Directory Structure
The Name and Phone numbers are stored in a csv file named ```directory.csv```. It already comes filled with some data. If you want you can add more data or create a new file altogether. Just take care to change the file name in ```server.cpp``` file and make sure that there are no duplicates(every name and phone number is unique)
