Project 2 	CS372 Intro to Computer Networks	Jacob Leno

This assignment has been written on OSU's flip server.
All programs run on OSU's flip server.

ftclient does not need to be compiled and can be run with $ ./ftclient.py
ftserver can be compiled via the makefile $ make 

ftclient:
This program is started via $ ./ftclient.py
And given command lines based on which version of flip the server
is running on. If the is running on flip1 it can be started via:
$ ./ftclient.py flip1 40790 -g shortfile.txt 40791

40790 - the port number the server is running on
-g - is the command to request a file from the server
shortfile.txt - is the name of the file requested
40791 - is the port to send the file contents back on

Also:
-l - can be given as the 3rd argument, in place of -g, which requests the directory
	structure. In this case the 4th argument should be the port to return
	the directory structure on.

ftserver:
This program is started via $ ./ftserver
after it has been compiled with make
It is given command lines based on what port it should start on.
Example $ ./ftserver 40790
- This will start the server running on port 40790
Note what version of flip this server is running on and give it as the first
argumetn to ftclient