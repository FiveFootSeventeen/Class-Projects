TITLE Program Template     (Program04_Leno_Jacob.asm)

; Author: Jacob Leno
; Course / Project ID CS 271-400 / (Program 4): Composite Numbers   Date: 10/30/17
; Description: This program outputs composite numbers from 1-400 based on the user's
; input. 
;***** EC: This program fulfills extra credit option 1*****

INCLUDE Irvine32.inc

	TRUE = 1
	FALSE = 0
	LOWERLIMIT = 1
	UPPERLIMIT = 400

.data
	nameTitle				BYTE		"Composite Numbers			Programmed by Jacob Leno",0
	enterNum				BYTE		"Enter the number of composite numbers you would like to see.", 0Dh, 0Ah, \
										"I'll accept orders for up to 400 composites.",0
	extraCred				BYTE		"** EC: This program fulfills extra credit option 1", 0
	termsPrompt				BYTE		"Enter the number of composites to display [1 .. 400]: ", 0
	outOfRange				BYTE		"Out of range. Try again.", 0
	certifiedResult			BYTE		"Results certified by Jacob Leno. Goodbye.", 0
	tabSpace				BYTE		09h, 0

	numberBuffer			BYTE		10 DUP(?)

.code
main PROC

	call			introductions
	call			getUserData
	call			showComposites
	call			farewell

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
	mov			edx, OFFSET nameTitle			;Load the title heading into edx and write to the screen
	call		WriteString
	call		CrLf
	call		CrLf
	mov			edx, OFFSET enterNum			;Load the instructions into edx and write to the screen
	call		WriteString
	call		CrLf
	mov			edx, OFFSET extraCred			;Load the extra credit heading into edx and write to the screen
	call		WriteString
	call		CrLf
	call		CrLf
	

	ret
	introductions	ENDP

;-----------------------------------------------------------------------------
;Procedure: getUserData
;Description: This procedure gets an integer input from the user in the range of 
; 1-400. If the user enters invalid input the procedure will output a message
; asking the to input valid data.
;Recieves: None
;
;Returns: A valid integer value in EAX
;-----------------------------------------------------------------------------

	getUserData	PROC	USES	 ecx
	
	DOWHILE:
	mov				edx, OFFSET termsPrompt			;Load the prompt for terms into edx and write to the screen
	call			WriteString
	mov				edx, OFFSET numberBuffer		
	mov				ecx, SIZEOF numberBuffer
	call			ReadString
	call			checkInt
	cmp				eax, FALSE						;Check to see if the value returned by checkInt is good
	jne				GOODNUM							;If it is good dont ask for another number
	mov				edx, OFFSET outOfRange			;Load the term out of range warning into edx and write to the screen
	call			WriteString
	call			CrLf
	GOODNUM:
	cmp				eax, FALSE						;If the number is good exit the loop
	je				DOWHILE

	ret
	getUserData	ENDP

;-----------------------------------------------------------------------------
;Procedure: showComposites
;Description: Displays a range of composite numbers depending on what it is 
;passed in EDX
;Recieves: Integer in the range of 1-400 in EDX
;
;Returns: None
;-----------------------------------------------------------------------------
	showComposites	PROC	USES	ecx eax ebx

	mov			ecx, edx					;loop will run for user specified number of loops
	mov			eax, 3						;Start at 4
	mov			ebx, 0

	call		CrLf

	L2:
	inc			ebx							;Increment compsite number counter
	push		ebx
	
	NotComposite:
	inc			eax							;Increment composite number to the next potential composite	
	call		isComposite					;Check the potential composite number in EAX
	mov			edx, ebx					;isComposite returns TRUE/FALSE in ebx, move it to edx
	cmp			edx, FALSE					;Check to see if the number is good
	je			NotComposite				;Dont write it to the screen if its composite

	mov			edx, eax					;Move composite to edx for writing
	call		WriteDec

	pop			ebx
	push		eax							;Push current composite  number onto the stack
	mov			eax, ebx					;Move the current counter into eax so division can take place
	push		ebx
	mov			ebx, 10
	cdq
	div			ebx							;Divide current counter number by 10
	cmp			edx, 0						;If there is no remainder its time for a new line
	jne			NoNewLine
	call		CrLf
	jmp			NoTab						;Do not add a tab when there is a new line
	NoNewLine:

	mov			edx, OFFSET tabSpace		
	push		ecx
	mov			ecx, SIZEOF tabSpace		;Output a tab to the screen so the numbers are evenly spaced
	call		WriteString
	pop			ecx
	NoTab:

	pop			ebx							;Pop composite counter off of the stack	
	pop			eax							;Pop composite number off of the stack

	
	Loop		L2

	call		CrLf
	ret
	showComposites	ENDP


;-----------------------------------------------------------------------------
;Procedure: isComposite
;Description: Checks a number in EAX to see if its composite.
;Recieves: Number to check in EAX
;
;Returns: True or false value in EBX, and the original number in EAX
;-----------------------------------------------------------------------------
	isComposite	PROC	USES	esi ecx edx

	mov			esi, eax			;Move number to be checked into esi
	mov			ecx, 2
	cdq								;Extend sign into EDX
	div			ecx					;Divide number by two
	mov			ecx, eax
	inc			ecx
	mov			ebx, FALSE			;Start of assuming the number is not composite

	L1:								;Loop by half of the value of the number
	mov			eax, esi	
	cdq								;Extend sign into EDX
	div			ecx					;Divide by current counter value
	cmp			edx, 0				;If the remainder is 0 it is divisible and thus composite
	jne			NotDivisible
	mov			ecx, 1				;Since its divisible set ecx to 1 to exit the loop
	mov			ebx, TRUE			;If number ever is divisible by any number checked in the loop
	NotDivisible:					;then set ebx to TRUE and exit the loop
	cmp			ecx, 2				;If ecx has reached two exit the loop
	jne			ContinueLoop
	mov			ecx, 1
	ContinueLoop:
	Loop		L1
	mov			eax, esi			;Move the original value back into eax

	ret
	isComposite	ENDP

;-----------------------------------------------------------------------------
;Procedure: farewell
;Description: This procedure displays a parting message
;Recieves: None
;
;Returns: None
;-----------------------------------------------------------------------------
	farewell	PROC	USES	edx

	mov			edx, OFFSET certifiedResult		;Load parting message into edx and write to screen
	call		WriteString
	call		CrLf

	ret
	farewell	ENDP

;-----------------------------------------------------------------------------
;Procedure: checkInt
;Description: Checks a number to see if its a valid integer returns good integer
;in EDX
;Recieves: A buffer to be checked in EDX, The length of the buffer in EAX
;
;Returns:  If the number is good it will be returned in EDX, EAX will contain
;the value of TRUE/FALSE
;-----------------------------------------------------------------------------
	checkInt	PROC	USES	ecx ebx esi
	mov			ebx, eax						;Move the length into ebx	
	mov			esi, 0							
	mov			ecx, -1							
	
	Do:
	inc			esi
	mov			al, numberBuffer[esi -1]		;Subtract 1 to account for the increment
	cmp			al, 2Dh							;Is AL the negative sign
	je			L1
	call		IsDigit
	jnz			NotANumber						;IsDigit has encountered a non-number, jump to the
	L1:											;end of the prodecure!
	cmp			esi, ebx
	jl			Do


	mov			edx, OFFSET numberBuffer
	mov			ecx, SIZEOF numberBuffer
	call		ParseInteger32					;Extract a number from the buffer
	mov			edx, eax						;Move the number extracted from numberBuffer to edx
	
	mov			ecx, 0
	cmp			edx, 0
	jnl			NotNeg							;If the number is negative add one account for the 
	inc			ecx								;negative sign in the buffer
	NotNeg:

	push		ebx								;Push the length in ebx onto the stack
	push		edx								;Push the user number onto the stack
	mov			ebx, 10

	
	WhileNotZero:								;Find out how many digits in the number extracted from the buffer
	cdq											;Sign extend eax into edx
	idiv		ebx
	inc			ecx
	cmp			eax, 0
	jne			WhileNotZero
	pop			edx								;Pop edx off the stack
	pop			ebx								;Pop the length off the stack into ebx


;*****Alter the comparisons in this part to change what is returned as true in future code****
	NotANumber:
	mov			eax, FALSE						;eax starts off as false
	cmp			ebx, ecx						;	If the length extracted and the length of the buffer 
	jne			EndFunction						;	are not the same end with false
	cmp			edx, LOWERLIMIT					;If the number is less than 1 end with false
	jl			EndFunction
	cmp			edx, UPPERLIMIT					;If the number is greater than 400
	jg			EndFunction						;end with false
	mov			eax, TRUE						;Otherwise the number is good

	EndFunction:
	ret
	checkInt	ENDP



END main
