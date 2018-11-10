TITLE Sorting Random Integers     (Program05_Leno_Jacob)

; Author:	Jacob Leno
; Course / Project ID   CS 271-400 / Program 5      Date: 11/18/17
; Description: This program requests an integer from the user in the range of 10-200.
; It then generates an array of that length and stores random integers in the range 
; of 100 to 999 in each element of the array. The integers in the array are then displayed.
; The the program calculates the median integer, sorts the array and displays both the median
; integer and the sorted array.

INCLUDE Irvine32.inc

	MIN = 10
	MAX = 200
	LO = 100
	HI = 999
	TRUE = 1
	FALSE = 0

.data

	introduction		BYTE		"Sorting Random Integers		Programmed by Jacob Leno", 0dh, 0ah,
									"This program generates random numbers in the range [100 .. 999],", 0dh, 0ah,
									"displays the original list, sorts the list, and calculates the", 0dh, 0ah,
									"median value. Finally, it displays the list sorted in descending order.", 0
	askNum				BYTE		"How many numbers should be generated? [10 .. 200]: ", 0
	invalid				BYTE		"Invalid input", 0
	unsortedTitle		BYTE		"The unsorted random numbers: ", 0
	medianTitle			BYTE		"The median is ", 0
	period				BYTE		".", 0
	sortedTitle			BYTE		"The sorted list: ", 0
	space				BYTE		"   ", 0 

	numBuffer			BYTE		10 DUP(?)
	request				DWORD		?
	numArray			DWORD		200 DUP(?)

.code
main PROC

	getData	PROTO, buffer: PTR BYTE, requestPtr: PTR DWORD
	fillArray PROTO, arrLength: DWORD, array: PTR DWORD
	displayMedian PROTO, arrLength: DWORD, array: PTR DWORD
	displayList PROTO, arrLength: DWORD, array: PTR DWORD, displayTitle: PTR BYTE
	sortList PROTO, arrLength: DWORD, array: PTR DWORD


	call		randomize
	call		introductions
	invoke		getData, ADDR numBuffer, ADDR request
	invoke		fillArray, request, ADDR numArray
	invoke		displayList, request, ADDR numArray, ADDR unsortedTitle
	invoke		sortList, request, OFFSET numArray
	invoke		displayMedian, request, ADDR numArray
	invoke		displayList, request, ADDR numArray, ADDR sortedTitle


	exit	
main ENDP

;-----------------------------------------------------------------------------
;Procedure: introduction
;Description: Program introductions
;Recieves: None
;
;Returns: None
;-----------------------------------------------------------------------------

	introductions	PROC

	mov			edx, OFFSET introduction		;Load the introduction message into edx and display
	call		WriteString
	call		CrLf
	call		CrLF
	
	ret
	introductions	ENDP

;-----------------------------------------------------------------------------
;Procedure: getData
;Description: Gets an integer value between 10 and 200 from the user, stores
; the result in its number parameter.
;Recieves: The address of buffer containing the number to be checked and the address
; of a variable to store the number in.
;
;Returns: The correct number stored in the variable it was originally sent.
;-----------------------------------------------------------------------------


	getData	PROC USES edx ecx eax, buffer: PTR BYTE, requestPtr: PTR DWORD
	
	checkInt PROTO, lower: DWORD, upper: DWORD, ;Prototype for the checkInt procedure
	numberBuffer: PTR BYTE, inputLength: DWORD

	BadNum:
	mov			edx, OFFSET askNum				;Move the offset of the askNum title into edx
	call		WriteString
	mov			ecx, 10							;Move the size of the buffer into ecx
	mov			edx, buffer						;and its address into edx
	call		ReadString
	invoke		checkInt, MIN, MAX, buffer, eax	;Call checkInt and pass appropriate arguments
	cmp			eax, TRUE						;Was the number input by the user a good number?
	je			GoodNum
	mov			edx, OFFSET invalid				;If not load the invalid message and display
	call		CrLf
	call		WriteString
	call		CrLf
	jmp			BadNum							;Get a new number because the user entered an invalid one
	GoodNum:		
	mov			edi, requestPtr
	mov			[edi], edx						;The number was good, dereference number and move the good
												;number in.

	ret
	getData		ENDP

;-----------------------------------------------------------------------------
;Procedure: fillArray
;Description: Fills an array with random values between the HI and LO
;Recieves: The length of the array as a DWORD, the address of the first element
; of the array
;
;Returns: The original array filled with random values
;-----------------------------------------------------------------------------

	fillArray PROC USES ecx edi eax,
		arrLength: DWORD, array: PTR DWORD
		LOCAL range: DWORD

	mov			ecx, 0
	mov			ecx, arrLength				;Load the array length into cx
	mov			edi, 0
	mov			edi, array					;Load the address of the first element of the array into edi

	mov			eax, HI
	sub			eax, LO						;Get the range of numbers
	inc			eax
	cld

	fillLoop:
	mov			range, eax					;Load the number range into range
	call		randomRange					;Get a random number
	add			eax, LO						;Add the low value to bring the number up to 100-999
	stosd									;Dereference edi and store the random number at the array location, increase edi by 4
	loop		fillLoop

	ret	
	fillArray ENDP

;-----------------------------------------------------------------------------
;Procedure: sortList
;Description: Sorts an array using the bubble sort algorithm
;**This Code was borrowed from Kip Irvine's Assembly Language book pg 375**
;Recieves: The length of the array as a DWORD, a DWORD pointer to the first element
; of the array.
;
;Returns: The original array sorted from lowest to highest
;-----------------------------------------------------------------------------

	sortList PROC USES ecx eax esi,
		arrLength: DWORD, array: PTR DWORD


	mov			ecx, arrLength		;Move the amount of array elements into ecx
	dec			ecx

	L1:	
	push		ecx					;Save ecx
	mov			esi, array			;Move the address of the first element into esi

	L2: 
	mov			eax, [esi]			;Move the value at esi into eax
	cmp			[esi + 4], eax		;If the value at the next element in the array is greater
	jg			L3					;do not exchange it with the value stored in eax
	xchg		eax, [esi + 4]		;If less, exchange the next value with the one stored in eax
	mov			[esi], eax			;and move the one now in eax into what esi is pointing to

	L3:
	add			esi, 4				;Get the next value in the array
	loop		L2

	pop			ecx
	loop		L1
	
	ret
	sortList ENDP


;-----------------------------------------------------------------------------
;Procedure: displayMedian
;Description: Displays the middle value of a sorted array
;Recieves: The length of the array as a DWORD, a DWORD pointer to the first element
; of the array.
;
;Returns: Nothing
;-----------------------------------------------------------------------------

	displayMedian PROC,
		arrLength: DWORD, array: PTR DWORD

	mov			eax, arrLength			;Load the length into eax
	mov			esi, array				;Load the first element into esi
	cdq									;Sign extend into edx
	mov			ebx, 2					
	div			ebx						;Divide eax by half
	dec			eax		
	mov			ebx, TYPE array		
	mul			ebx						;Multiply the mid way point by the size of each element of the array
	add			esi, eax				;and add that value to esi
	mov			eax, [esi]				;Dereference esi and move it to eax
	call		CrLf
	mov			edx, OFFSET medianTitle	;Output the median title
	call		WriteString
	call		WriteDec				;Output the middle value
	mov			edx, OFFSET period		;Add the period
	call		WriteString
	call		CrLf
	call		CrLf

	ret
	displayMedian ENDP

;-----------------------------------------------------------------------------
;Procedure: displayList
;Description: Displays a list of numbers stored in an array
;Recieves: The array length as a WORD, the address of the first element of the array
; and the address of the title to display with the list.
;
;Returns: Nothing
;-----------------------------------------------------------------------------

	displayList PROC USES eax ecx edx esi, 
		arrLength: DWORD, array: PTR DWORD, displayTitle: PTR BYTE
		LOCAL ten: DWORD, counter: DWORD

	mov			ecx, 0
	mov			ecx, arrLength				;Load the array length into cx
	mov			esi, 0
	mov			esi, array		;Load the address of the first element of the array into esi
	mov			eax, 0
	mov			ten, 10						;Initialize the variable ten
	mov			counter, 0					;Initialize the counter
		
	mov			edx, displayTitle			;Load the title and display it
	call		WriteString
	call		CrLf

	cld
	showArray:
	lodsd									;Load array element into ax and increment esi
	call		WriteDec					;Write the element
	mov			edx, OFFSET space
	call		WriteString
	inc			counter						;Increment the counter
	mov			eax, counter				;Load the counter into eax
	cdq										;Sign extend into edx
	div			ten							;Divide eax by 10
	cmp			edx, 0						;If the remainder in edx is zero start a new line
	jnz			noNewLine
	call		CrLf
	noNewLine:
	loop		showArray					;Loop for all the elements in the array
	
	call		CrLf

	ret
	displayList ENDP

;-----------------------------------------------------------------------------
;Description: Checks a number to see if its a valid integer returns good integer
;in EDX
;Recieves: lower limit, upper limit, pointer to the buffer the number is in, and
; the length of the buffer.
;
;Returns:  If the number is good it will be returned in EDX, EAX will contain
;the value of TRUE/FALSE
;-----------------------------------------------------------------------------

	checkInt PROC USES ecx ebx esi,
		lower: DWORD,
		upper: DWORD,
		numberBuffer: PTR BYTE,
		inputLength: DWORD

	mov			ebx, 0
	mov			ecx, 0
	mov			ecx, inputLength				;Move the length into ecx	
	mov			esi, numberBuffer							
				
	Do:
	mov			al, [esi]						;Move value to check into al
	inc			esi	
	cmp			al, 2Dh							;Is AL the negative sign
	je			L1
	call		IsDigit
	jnz			NotANumber						;IsDigit has encountered a non-number, jump to the
	L1:											;end of the prodecure!
	loop		Do


	mov			edx, numberBuffer
	mov			ecx, 0
	mov			ecx, inputLength
	call		ParseInteger32					;Extract a number from the buffer
	mov			edx, eax						;Move the number extracted from numberBuffer to edx
	
	mov			ecx, 0
	cmp			edx, 0
	jnl			NotNeg							;If the number is negative add one account for the 
	inc			ecx								;negative sign in the buffer
	NotNeg:

	push		edx								;Push the user number onto the stack
	mov			ebx, 10

	
	WhileNotZero:								;Find out how many digits in the number extracted from the buffer
	cdq											;Sign extend eax into edx
	idiv		ebx
	inc			ecx
	cmp			eax, 0
	jne			WhileNotZero
	pop			edx								;Pop edx off the stack

	NotANumber:
	mov			eax, 0							;eax starts off as false
	cmp			inputLength, ecx				;	If the length extracted and the length of the buffer 
	jne			EndFunction						;	are not the same end with false
	cmp			edx, lower						;If the number is less than lower end with false
	jl			EndFunction
	cmp			edx, upper						;If the number is greater than upper
	jg			EndFunction						;end with false
	mov			eax, 1							;Otherwise the number is good

	EndFunction:
	ret
	checkInt	ENDP


END main
