#!/usr/bin/python

#/****************************************************
# *Author: Jacob Leno
# *Date: 07/27/18
# *Program: chatmodules.py
# *Description: Recieve a connection from the client on
# * flipX.engr.oregonstate.edu at a given port number
# * once a connection is established the client and server
# * will begin sending messages to one another unil the 
# * command \quit is recieved
# ***************************************************/

#***Basic TCP server implementation adapted from lecture 15 slide 9***

from socket import socket, AF_INET, SOCK_STREAM, gethostname, htonl
import signal
import sys

NAME = 'Compy 386'

#Code for defining signal_handler found on 
#https://stackoverflow.com/questions/27360218/how-to-close-socket-connection-on-ctrl-c-in-a-python-programme/27360648
#Catch SIGINT and exit the program when it is caught
def signal_handler(signal, frame):
	sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)

#Function: sendMessage
#Takes a socket connected to a sending client as its argument
#Send a message from the user at the server to the client
#If the server's user gives the special key phrase '\quit' as input return False
def sendMessage(connectionSocket):
	serverMsg = raw_input(NAME + "> ")

	if serverMsg == "\quit":
		return False
	
	#connectionSocket.send(str(msgLen))
	sent = connectionSocket.send(NAME + "> " + serverMsg)
	#connectionSocket.flush() #Flush the output buffer
	
	if sent == '':
		print("Client has ended connection")

	return True

#Function: recieveMessage
#Takes a socket connected to a sending client as its argument
#Recieves a message of up to 1024 characters from the client
def recieveMessage(connectionSocket):
	message = connectionSocket.recv(1024)
	if message == '':
		print("Client has ended connection")
		return False
	else: 
		print(message)
		return True

#Function: startUp
#Takes a serverPort number to listen at as an argument
#Listens for a new connection and then calls sendMessage and recieveMessage
#to begin sending and recieving text communication
def startUp(serverPort):
	serverSocket = socket(AF_INET, SOCK_STREAM)
	serverSocket.bind((gethostname(), int(serverPort)))	#bind() takes a pair (host, port) where host is a string representing eithe ra hostname or IPv4 address
									#port is an integer port number, gethostname() lets the socket be visible to the outside world
									#'localhost' in the host pair parameter would only allow it to be visible on this machine
	
	serverSocket.listen(1) #1 specifies the number of unaccepted connections that the system will allow before refusing new connections
	while(1):
		print("Starting service on port #" + serverPort)
		print("Waiting for connection from client...")
		(connectionSocket, address) = serverSocket.accept()	#accept() returns a pair, (conn, address), where conn is a new socket object
		commLoop = True				  	#address is the address bound to the socket on the other end of the connection 
		print("Connection recieved, client begins communication")
		while commLoop == True:	#while the user wants to communicate
			commLoop = recieveMessage(connectionSocket)
			if commLoop == True:
				commLoop = sendMessage(connectionSocket) #If sendMessage returns False, stop communication
		connectionSocket.close()




