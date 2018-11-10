Jacob Leno - Project 1

This program was developed and tested on OSUs flip server

First chatserve must be run then chatclient.

chatserve:

The server is written in Python and can be started with ./chatserve.py <portnumber>
You may have to give the command: $ chmod +x chatserve.py 
to give it executable permissions first

chatclient:

The client is written in C.
First compile it via:  $ gcc -o chatclient chatclient.c -g
Then it can be run via: $ ./chatclient flipX.engr.oregonstate.edu <portnumber>
Where the X in flipX is the instance of flip the server is running on and
<portnumber> is the port number the server was started on.


Once the connection is established the client program will ask for a name from its user.
It will prepend each message with "username"> and the server will recieve the messages
with this handle prepended. The messaging will alternate and start with the client. The server
will not be able to send a message to the client until it gets the client's reply and vice
versa. If either host breaks the connection at anytime a message will be displayed. If the client
breaks the connection the server will simply wait for another connection. If the server
breaks the connection the client will exit the program. Either program can be exited at any time with the command \quit