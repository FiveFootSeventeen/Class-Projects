#!/usr/bin/python

#/****************************************************
# *Author: Jacob Leno
# *Date: 08/11/18
# *Program: ftclient
# *Description: This program makes requests to a server
# * based on arguments it is given when started. 1st argument
# * should always be the instance of flip to connect to the 
# * server on. The second argument is always the port number
# * the server is running on. The third argument is either -l
# * which requests the directory or -g which specifies a file
# * is requested. If a directory is requested the port number
# * to return the directory information should be given as the
# * fourth argument. If a file is requested the fourth argument
# * should be the file name and the fifth argument the port number.
# ***************************************************/

import sys
from socket import *
from struct import pack, unpack

#Basic TCP client code adapted from lecture 15 slide 8

def main():
	arguments = len(sys.argv)
	if arguments < 5: #Verify the arguments given as input
		print('Must give at least server host, server port number, command, and client port number')
		return 1
	if validatePort(sys.argv[2]) == -1:
		print('Invalid server port number')	
		return 1
	if arguments == 5:
		if validatePort(sys.argv[4]) == -1:
			print('Invalid client port number')
			return 1
	elif arguments == 6:
		if validatePort(sys.argv[5]) == -1:
			print('Invalid client port number')
			return 1
		

	serverName = sys.argv[1] + '.engr.oregonstate.edu'
	serverPort = int(sys.argv[2])
	
	connectionP = socket(AF_INET, SOCK_STREAM) 
	connectionP.connect((serverName, serverPort)) #Connect to a given server and port number
	
	payload = ""
	for i in range(1, arguments):
		payload += sys.argv[i]
		payload += " "

	length = len(payload)
	val = pack('!H', int(length)) #Convert the size to a string and pack as an unsigned short int
	connectionP.send(val)
	connectionP.send(payload)

	responseNum = connectionP.recv(2); #Get the response number from the server
	num = unpack('!H', responseNum)[0]; #Convert the response into host byte order

	if num == 0: #Decide which function to call based on what response number the server sent back
		recvFile(connectionP, sys.argv[4], serverName, serverPort, arguments, sys.argv)
	elif num == 1:
		recvDir(connectionP, serverName, serverPort, arguments, sys.argv)
	else:
		errorMsg(connectionP, serverName, serverPort)
	

	connectionP.close() #close the connection

	return 0

#This function sets up a new data connection with the server to recieve the directory
# once the directory information has been sent it displays the directory contents as 
# it recieves them
def recvDir(connectionP, servName, portNum, arguments, args = []):
	print("Recieving directory structure from " + servName + ":" + str(portNum))
	serverSocket = recieveConnection(arguments, args)
	val = pack('!H', 200) #Convert the response to a network byte order and send
	connectionP.send(val)
	connectionQ, addr = serverSocket.accept()
	
	incomingSize = connectionQ.recv(2); #Get the incomingSize from the server
	num = unpack('!H', incomingSize)[0]; #Convert the size into host byte order

	while num > 0:
		item = connectionQ.recv(num)
		print(item)
		incomingSize = ""
		incomingSize = connectionQ.recv(2); #Get the incomingSize from the server
		num = unpack('!H', incomingSize)[0]; #Convert the size into host byte order

	connectionQ.close() #Close the data connection


#This function sets up a new data connection with the server to recieve a file specified
# in its arguments. Once the connection has been created is recieves the file contents in chunks
# specified by the server
def recvFile(connectionP, filename, servName, portNum, arguments, args = []):
	print("Recieving \"" + filename + "\" from " + servName + ":" + str(portNum))
	serverSocket = recieveConnection(arguments, args)
	val = pack('!H', 200) #Convert the response to a network byte order and send
	connectionP.send(val)
	connectionQ, addr = serverSocket.accept()
	outFile = open(filename, "w")
	
	incomingSize = connectionQ.recv(2); #Get the incomingSize from the server
	num = unpack('!H', incomingSize)[0]; #Convert the size into host byte order

	while num > 0:
		chunk = connectionQ.recv(num)
		outFile.write(chunk);
		incomingSize = ""
		incomingSize = connectionQ.recv(2); #Get the incomingSize from the server
		num = unpack('!H', incomingSize)[0]; #Convert the size into host byte order

	connectionQ.close() #Close the data connection

#This function displays an error message sent by the server over the control connection
def errorMsg(connectionP, servName, portNum):
	print(servName + ":" + str(portNum) + " says: ")
	responseNum = connectionP.recv(2); #Get the response number from the server
	num = unpack('!H', responseNum)[0]; #Convert the response into host byte order
	serverResponse = connectionP.recv(num)
	print(serverResponse)

#This function validates a given port number sent as a string
def validatePort(portNumStr):
	length = len(portNumStr)

	if length > 5: #If the port is greater the 5 characters it is invalid automatically
		return -1

	for i in range(0, length): #If the port is not a number it is invalid
		if (ord(portNumStr[i]) < 48) or (ord(portNumStr[i]) > 57):
			return -1
	
	portNumInt = int(portNumStr);

	if (portNumInt < 65536) and (portNumInt >= 0): #If the port number does not fall in the range of valid port numbers return -1
		return portNumInt
	else:
		return -1

#Basic TCP server code adapted from lecture 15 slide 9
#
def recieveConnection(arguments, args = []):
	serverSocket = socket(AF_INET, SOCK_STREAM)
	serverSocket.bind(('', int(args[arguments - 1])))
	serverSocket.listen(1)
	return serverSocket

	

main();
