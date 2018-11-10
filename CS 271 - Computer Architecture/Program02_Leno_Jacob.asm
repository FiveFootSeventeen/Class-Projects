	TITLE Program Template     (template.asm)

; Author: Jacob Leno
; Course / Project ID CS271-400 / Program Assignment #2 (Fibonacci numbers)              
; Date: 10/13/17
; Description: This program displays its title and the programmers name. 
; It then gets the user's name and greets the user. It asks the user to enter
; the number of Fibonacci terms to be displayed (1 - 46), validates the input,
; calculates the result and displays all of the Fibonacci numbers up to and 
; including the nth term.

	INCLUDE Irvine32.inc
;Define constants to be used in the program
	TRUE = 1
	FALSE = 0
	UPPERLIMIT = 46
	LOWERLIMIT = 1

	.data
;Define strings to be used in the program
	nameTitle			BYTE		"Fibonacci Numbers", 0Dh, 0Ah, "Programmed by Jacob Leno", 0
	getUserName			BYTE		"What is your name? ", 0
	termsRange			BYTE		"Enter the number of Fibonacci terms to be displayed", \
									0Dh, 0Ah, "Give the number as an integer in the range [1 .. 46].", 0
	termsRequest		BYTE		"How many Fibonacci terms do you want? ", 0
	termDenied			BYTE		"Out of range. Enter a number in [1 .. 46]", 0
	certifiedResults	BYTE		"Results certified by Jacob Leno", 0
	helloStr			BYTE		"Hello, ", 0		
	goodbyeStr			BYTE		"Goodbye, ", 0
	space				BYTE		"     ", 0
	nameBuffer			BYTE		100 DUP(?)

;Define integer variables to be used in the program
	counter				DWORD		0
	characterCount		DWORD		?
	termsBuffer			BYTE		10 DUP(?)
	temp				DWORD		?

	.code
	main PROC

;--------------------------------------------------------
;Introductions
;--------------------------------------------------------
	mov			edx, OFFSET nameTitle		;Move the greeting into edx
	call		WriteString
	call		Crlf
	call		Crlf
	mov			edx, OFFSET getUserName		;Move the request for a name into edx
	call		WriteString
	mov			edx, OFFSET nameBuffer		;Point to buffer
	mov			ecx, SIZEOF nameBuffer		;Specify the max characters the buffer can hold
	call		ReadString
	mov			edx, OFFSET helloStr		;Move "Hello, " into edx

;--------------------------------------------------------
;User instructions
;--------------------------------------------------------
	call		WriteString
	mov			edx, OFFSET nameBuffer		;Move the user's name into edx
	call		WriteString
	call		Crlf
	mov			edx, OFFSET	termsRange		;Move the number specifications into edx
	call		WriteString
	call		Crlf
	call		Crlf

;--------------------------------------------------------
;Get user data
;--------------------------------------------------------
	USERINPUT:	
	mov			edx, OFFSET termsRequest	;Move the question for quantity of terms into edx
	call		WriteString
	mov			edx, OFFSET termsBuffer		;Point to the buffer
	mov			ecx, SIZEOF termsBuffer		;Specify the max characters the buffer can hold
	call		ReadString
	mov			characterCount, eax			;Pass the amount of characters read by ReadString into characterCount
	call		ParseDecimal32				;Remove decimal from the string in edx, value stored in eax


;--------------------------------------------------------
;Get user data Pt2. (Data validation section)
;--------------------------------------------------------

	mov			ebx, 2
	cmp			eax, 9						;Check to see if the value entered is a single digit
	jg			NotSingleDigit				
	mov			ebx, 1						;If it is set ebx equal to 1
	NotSingleDigit:
	
	cmp			characterCount, 2			;Compare the value in characterCount to see if its 
	jg			BadNum  					;larger than 2 characters (Value too large)

	cmp			characterCount, ebx			;Compare the value in characterCount to see
	jne			BadNum						;if eax has the correct amount of numeric characters

	cmp			eax, 0						;If ParseDecimal32 returned 0 the string is empty, get a new number
	je			BadNum
	mov			ecx, UPPERLIMIT				;Move the upper limit constant into ecx
	mov			ebx, LOWERLIMIT				;Move the lower limit constant into ebx
	call		rightSize					;Call the input validation procedure, truth value will be returned in ebx, number in eax
	cmp			ebx, TRUE
	je			GoodInput					;If rightSize returns true jump to GoodInput

	BadNum:									;If a bad number is found move the value of false into eax
	mov			ebx, FALSE
	mov			edx, OFFSET termDenied	
	call		WriteString					;If the user entered bad input remind them of what they need to input
	call		Crlf

	GoodInput:
	cmp			ebx, FALSE
	je			USERINPUT

;--------------------------------------------------------
;Display Fibs
;--------------------------------------------------------
	mov			ecx, eax					;Set loop counter equal to number of terms 
	mov			eax, 1						;Set eax and ebx equal to the starting values
	mov			ebx, 1
	
	L1:
	mov			edx, 0						;Make sure edx is zero at the start of each loop

	;Check if 5 values have been displayed on a line
	push		eax							;Push eax and ebx onto the stack
	push		ebx
	mov			eax, counter				;Move the current count into eax for division
	mov			ebx, 5
	div			ebx 
	cmp			edx, 0						;If the remainder in edx is not 0 jump past the Crlf
	jne			NoNewLine
	call		Crlf
	NoNewLine:
	pop			ebx							;Pop ebx off the stack (leave eax for now)

	mov			eax, ebx					;Move ebx into eax for writing to console
	call		WriteDec
	mov			edx, OFFSET space			;Write the term onto the screen with a tab
	call		WriteString	
	pop			eax							;Pop eax off the stack

	mov			temp, eax					;Perform the calculation for the next term
	add			eax, ebx
	mov			ebx, temp

	inc			counter						;Increment the counter for the amount of terms displayed
	loop		L1							;and continue to loop if ecx > 0

	NoLoop:
	call		Crlf
	call		Crlf

;--------------------------------------------------------
;Farewell
;--------------------------------------------------------
	mov			edx, OFFSET certifiedResults ;Move certified results message into edx
	call		WriteString
	call		Crlf
	mov			edx, OFFSET goodbyeStr		;Move "Goodbye, " into edx
	call		WriteString
	mov			edx, OFFSET nameBuffer		;Move the user name into edx
	call		WriteString
	call		Crlf


		exit						
	main ENDP

;-----------------------------------------------------------------------------
;Procedure: rightSize
;
;Checks to see if a value is between a high number and a low number
;Recieves: EAX - The value to compare, ECX - The highest value EAX can be
;		   EBX - The lowest value EAX can be.
;
;Returns:  EBX = TRUE(1) if in range, and FALSE(0) if not in the range
;		   EAX = Initial Value
;-----------------------------------------------------------------------------

	rightSize PROC						
	cmp			eax, ecx		;Compare the value in eax and check to see if its between 1 and 46
	jg			BadValue
	cmp			eax, ebx
	jl			BadValue
									
	mov			ebx, TRUE		;If a good value is found move the value of true into ebx
	jmp			GoodValue		;and jump to the end of the procedure.

	BadValue:					;If a bad value is found move the value of false into ebx
	mov			ebx, FALSE

	GoodValue:
	ret							
	rightSize ENDP

	END main
	