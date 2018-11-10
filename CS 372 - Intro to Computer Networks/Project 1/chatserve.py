#!/usr/bin/python

#/****************************************************
# *Author: Jacob Leno
# *Date: 07/27/18
# *Program: chatserve
# *Description: Recieve a connection from the client on
# * flipX.engr.oregonstate.edu at a given port number
# * once a connection is established the client and server
# * will begin sending messages to one another unil the 
# * command \quit is recieved
# ***************************************************/

#***Basic TCP server implementation adapted from lecture 15 slide 9***

import sys
from chatmodules import * 

def main():
	if len(sys.argv) < 2:
		print('First argument must be a port number')
	else:
		startUp(sys.argv[1]) #Send the port number to the startUp function
	return 0


main();
