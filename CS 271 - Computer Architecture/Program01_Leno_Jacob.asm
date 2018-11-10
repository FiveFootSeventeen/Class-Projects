

TITLE Program Template     (Program01.asm)

;** Author: Jacob Leno
;** Program name: Program 1 / CS271-400
;** Date: 09/30/17
;** Description: This program prompts the user for two numbers and calculates
;** sum, difference, integer quotient and remainder of the numbers. After
;** it is finished it displays each of problem and its solution.

INCLUDE Irvine32.inc

.data

name_title		BYTE	"	Elementary Arithmetic (Program 1)	by Jacob Leno", 0
instruction_1	BYTE	"Enter 2 numbers, and I'll show you the sum, difference,", 0
instruction_2	BYTE	"product, quotient, and remainder.", 0
prompt_1		BYTE	"Enter first number: ", 0
prompt_2		BYTE	"Enter second number: ", 0
num_1			DWORD	?
num_2			DWORD	?
num_add			DWORD	?
num_sub			DWORD	?
num_mul			DWORD	?
num_quo			DWORD	?
num_rem			DWORD	?
good_bye		BYTE	"Impressed? Bye!", 0

plus			BYTE	" + ", 0
minus			BYTE	" - ", 0
multiply		BYTE	" x ", 0
divide			BYTE	" / ", 0
equals			BYTE	" = ", 0
remainder		BYTE	" remainder ", 0

.code
main PROC

;Display the title of the program
mov		edx, OFFSET name_title
call	WriteString
call	CrLf
call	CrLf

;Output instructions to the user
mov		edx, OFFSET instruction_1
call	WriteString
call	CrLf
mov		edx, OFFSET instruction_2
call	WriteString
call	CrLf
call	CrLf

;Prompt the user to enter two numbers
mov		edx, OFFSET prompt_1
call	WriteString
call	ReadInt
mov		num_1, eax
mov		edx, OFFSET prompt_2
call	WriteString
call	ReadInt
mov		num_2, eax
call	CrLf

;Add the two numbers
mov		eax, num_1
mov		ebx, num_2
add		eax, ebx
mov		num_add, eax


;Subtract the two numbers
mov		eax, num_1
mov		ebx, num_2
sub		eax, ebx
mov		num_sub, eax


;Multiply the two numbers
mov		eax, num_1
mov		ebx, num_2
mul		ebx
mov		num_mul, eax


;Divide the two numbers
mov		eax, num_1
mov		ebx, num_2
div		ebx
mov		num_quo, eax
mov		num_rem, edx

;Output the results
;Addition
mov		eax, num_1
call	WriteDec
mov		edx, OFFSET plus
call	WriteString
mov		eax, num_2
call	WriteDec
mov		edx, OFFSET equals
call	WriteString
mov		eax, num_add
call	WriteDec
call	CrLf
;Subtraction
mov		eax, num_1
call	WriteDec
mov		edx, OFFSET minus
call	WriteString
mov		eax, num_2
call	WriteDec
mov		edx, OFFSET equals
call	WriteString
mov		eax, num_sub
call	WriteDec
call	CrLf
;Multiplication
mov		eax, num_1
call	WriteDec
mov		edx, OFFSET multiply
call	WriteString
mov		eax, num_2
call	WriteDec
mov		edx, OFFSET equals
call	WriteString
mov		eax, num_mul
call	WriteDec
call	CrLf
;Division
mov		eax, num_1
call	WriteDec
mov		edx, OFFSET divide
call	WriteString
mov		eax, num_2
call	WriteDec
mov		edx, OFFSET equals
call	WriteString
mov		eax, num_quo
call	WriteDec
mov		edx, OFFSET remainder
call	WriteString
mov		eax, num_rem
call	WriteDec


call	CrLf
call	CrLf
mov		edx, OFFSET good_bye
call	WriteString
call	CrLf

	exit
main ENDP

END main
