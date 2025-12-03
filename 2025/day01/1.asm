; This is an .asm program written in Visual Studio 2022 and made to run in Windows.
; To run this, create an empty project and set the compilation dependencies by checking the "masm" checkbox. Then add this file.
; Afterwards, head to project properties -> linker -> command line, and select the "Win32" platform. Afterwards, add "libcmt.lib" to the textbox at the bottom.
; Then head to linker -> system and ensure the subsystem is set to CONSOLE. Change your solution platform from x64 to x86. You may then run this program.

.686
.model flat
extern _SetFilePointer@16 : PROC ; i am going to die.
extern _CloseHandle@4 : PROC
extern _CreateFileA@28 : PROC
extern _ReadFile@20 : PROC
extern __write : PROC
extern _ExitProcess@4 : PROC

public _main

.data
dialnumber		dd 50				; the dial starts at 50.
zerosfounds1	dd 0				; part 1 solution
zerosfounds2	dd 0				; part 2 solution
puzzleinput		db 5 dup (?)
bytesread		dd ?
readoffset		dd 0

filename		db 'input.txt', 0

.code
halfnumbertonumber PROC
	; parameter must be in eax
	; EAX = 00 06 08 02 -> 682 -> 00 00 02 AA = EAX
	push edx
	push edi ; 10
	push ebp ; 100
	push ecx
	push esi

	mov edi, 10
	mov ebp, 100
	mov ecx, eax

	and eax, 0000FF00h
	shr eax, 8
	mul di
	xor edx, edx
	add al, cl

	mov esi, eax
	mov eax, ecx
	and eax, 00FF0000h
	shr eax, 16
	mul bp
	xor edx, edx
	add eax, esi
	
	pop esi
	pop ecx
	pop ebp
	pop edi
	pop edx
	ret
halfnumbertonumber ENDP

solve1 PROC
	pusha

	mov ebp, 1
	mov edi, 0
	mov al, puzzleinput
	inc readoffset
	cmp al, 'R'
	jne turn_left
	
	; turn right - add to dialnumber
	mov al, 0
	get_values_right:
	lea eax, [puzzleinput+ebp]
	movzx eax, BYTE PTR [eax]
	cmp al, 0dh
	je right_solve
	sub al, 30h ; getting the real number out of the text
	add edi, eax
	shl edi, 8
	inc readoffset
	inc ebp
	jmp get_values_right
	
	right_solve:
	mov ecx, 100
	add readoffset, 2 ; skipping newline

	; calculate the number to shift by
	mov eax, edi
	shr eax, 8
	call halfnumbertonumber

	; shift the dial
	add dialnumber, eax
	mov eax, dialnumber
	cmp eax, 100
	jb finishing
	xor edx, edx
	div ecx
	mov eax, edx
	jmp finishing

	turn_left:
	mov al, 0
	; decrease from dialnumber
	get_values_left:
	lea eax, [puzzleinput+ebp]
	movzx eax, BYTE PTR [eax]
	cmp al, 0dh
	je left_solve
	sub al, 30h ; getting the real number out of the text
	add edi, eax
	shl edi, 8
	inc readoffset
	inc ebp
	jmp get_values_left
	
	left_solve:
	mov ecx, 100
	add readoffset, 2 ; skipping newline

	; calculate the number to shift by
	mov eax, edi
	shr eax, 8
	call halfnumbertonumber

	; shift the dial
	sub dialnumber, eax
	mov eax, dialnumber
	cmp eax, 0
	jge finishing
	add eax, 1000
	xor edx, edx
	div ecx
	mov eax, edx

	finishing:
	mov dialnumber, eax ; save the current dial number
	cmp eax, 0 ; check if the dial number is 0
	jne finished
	inc zerosfounds1

	finished:
	popa
	ret
solve1 ENDP

; this parts solution is goblin mode.
; we are basically going to be simulating each and every single click
; i n d i v i d u a l l y .
solve2 PROC
	pusha

	; determine which way we are turning the dial
	mov ebp, 1
	mov edi, 0
	mov al, puzzleinput
	inc readoffset
	cmp al, 'R'
	jne turn_left
	
	; turn right - add to dialnumber
	mov al, 0
	get_values_right:
	lea eax, [puzzleinput+ebp]
	movzx eax, BYTE PTR [eax]
	cmp al, 0dh
	je right_solve
	sub al, 30h ; getting the real number out of the text
	add edi, eax
	shl edi, 8
	inc readoffset
	inc ebp
	jmp get_values_right
	
	right_solve:
	mov ecx, 100
	add readoffset, 2 ; skipping newline

	; calculate the number to shift by
	mov eax, edi
	shr eax, 8
	call halfnumbertonumber

	; shift the dial (adding)
	mov ecx, eax
	shiftingright:
	inc dialnumber
	cmp dialnumber, 100
	jne contr
	sub dialnumber, 100
	inc zerosfounds2
	contr:
	loop shiftingright
	jmp finish

	turn_left:
	mov al, 0
	; decrease from dialnumber
	get_values_left:
	lea eax, [puzzleinput+ebp]
	movzx eax, BYTE PTR [eax]
	cmp al, 0dh
	je left_solve
	sub al, 30h ; getting the real number out of the text
	add edi, eax
	shl edi, 8
	inc readoffset
	inc ebp
	jmp get_values_left
	
	left_solve:
	mov ecx, 100
	add readoffset, 2 ; skipping newline

	; calculate the number to shift by
	mov eax, edi
	shr eax, 8
	call halfnumbertonumber

	; shift the dial (subtracting)
	mov ecx, eax
	cmp dialnumber, 0
	jne shiftingleft
	add dialnumber, 100
	shiftingleft:
	dec dialnumber
	cmp dialnumber, 0
	jne contl
	inc zerosfounds2
	add dialnumber, 100
	contl:
	loop shiftingleft
	cmp dialnumber, 100
	jne finish
	sub dialnumber, 100

	finish:
	popa
	ret
solve2 ENDP

_main PROC
	; HANDLE h = CreateFileA("input.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	push 0
	push 128 ; FILE_ATTRIBUTE_NORMAL
	push 3 ; OPEN_EXISTING
	push 0
	push 0
	push 80000000h ; GENERIC_READ
	push OFFSET filename
	call _CreateFileA@28

	; ebx = h;
	mov ebx, eax

	readdatas1:
	; DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
	push 0
	push 0
	push readoffset
	push ebx
	call _SetFilePointer@16
	; BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nBytesToRead, LPDWORD lpBytesRead, LPOVERLAPPED lpOverlapped );
	push 0
	push OFFSET bytesread
	push 5
	push OFFSET puzzleinput
	push ebx
	call _ReadFile@20

	mov eax, bytesread
	cmp al, 0
	je timeforpart2
	xor eax, eax
	call solve1
	jmp readdatas1

	; begin part 2 solution here
	timeforpart2:
	; reset the file pointer and the dial number
	mov readoffset, DWORD PTR 0
	mov dialnumber, DWORD PTR 50
	readdatas2:
	; DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
	push 0
	push 0
	push readoffset
	push ebx
	call _SetFilePointer@16
	; BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nBytesToRead, LPDWORD lpBytesRead, LPOVERLAPPED lpOverlapped );
	push 0
	push OFFSET bytesread
	push 5
	push OFFSET puzzleinput
	push ebx
	call _ReadFile@20

	mov eax, bytesread
	cmp al, 0
	je finished
	xor eax, eax
	call solve2
	jmp readdatas2

	finished:
	push ebx
	call _CloseHandle@4

	; return the answer
	push zerosfounds2 ; or: push zerosfounds1 for the first solution. im too lazy to print it to terminal properly.
	call _ExitProcess@4
_main ENDP
END