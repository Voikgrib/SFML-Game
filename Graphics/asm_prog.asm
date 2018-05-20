global _start 
SECTION .data 

 filename db "pipe.txt", 0
 Meow_start	db	 " /\_/\",10,"(<o.o>)",10," )=*=(",10,"(\|.|/)~~**",10,"Meow ^^", 10
 Meow_len equ $ - Meow_start
 out_print	db	">>> Output: " 
 length	equ	$ - out_print
 my_enter	db	10
 ten			dq	0
 cur_per		dq	0
 cur_byte		dq	0
 faker1 dq 0
 faker2 dq 0
 faker3 dq 0
 faker4 dq 0
 faker5 dq 0
 faker6 dq 0
 faker7 dq 0
 faker8 dq 0
 faker9 dq 0
 faker10 dq 0
 faker11 dq 0
 faker12 dq 0
 faker13 dq 0
 faker14 dq 0
 faker15 dq 0
 faker16 dq 0
 faker17 dq 0
 faker18 dq 0
 faker19 dq 0
 faker20 dq 0
 faker21 dq 0
 faker22 dq 0
 faker23 dq 0
 faker24 dq 0
 faker25 dq 0
 faker26 dq 0
 faker27 dq 0
 faker28 dq 0
 faker29 dq 0
 faker30 dq 0
 faker31 dq 0
 faker32 dq 0
 faker33 dq 0
 faker34 dq 0
 faker35 dq 0
 faker36 dq 0
 faker37 dq 0
 faker38 dq 0
 faker39 dq 0
 faker40 dq 0
 faker41 dq 0
 faker42 dq 0
 faker43 dq 0
 faker44 dq 0
 faker45 dq 0
 faker46 dq 0
 faker47 dq 0
 faker48 dq 0
 faker49 dq 0
 faker50 dq 0
 faker51 dq 0
 faker52 dq 0
 faker53 dq 0
 faker54 dq 0
 faker55 dq 0
 faker56 dq 0
 faker57 dq 0
 faker58 dq 0
 faker59 dq 0
 faker60 dq 0
 faker61 dq 0
 faker62 dq 0
 faker63 dq 0
 faker64 dq 0
 faker65 dq 0
 faker66 dq 0
 faker67 dq 0
 faker68 dq 0
 faker69 dq 0
 faker70 dq 0
 faker71 dq 0
 faker72 dq 0
 faker73 dq 0
 faker74 dq 0
 faker75 dq 0
 faker76 dq 0
 faker77 dq 0
 faker78 dq 0
 faker79 dq 0
 faker80 dq 0
 faker81 dq 0
 faker82 dq 0
 faker83 dq 0
 faker84 dq 0
 faker85 dq 0
 faker86 dq 0
 faker87 dq 0
 faker88 dq 0
 faker89 dq 0
 faker90 dq 0
 faker91 dq 0
 faker92 dq 0
 faker93 dq 0
 faker94 dq 0
 faker95 dq 0
 faker96 dq 0
 faker97 dq 0
 faker98 dq 0
 faker99 dq 0
 faker100 dq 0

SECTION .text 

;====================== ascii --> 10-razr ===============================;
;!! Input:	cur_per = curren peremennaya
;!!	Exit: 	Printf 10razr
;!!	Destroy:	rax, rbx, rdx, rsi, r13
;========================================================================;
;rdx:rax / rbx = rax (ost. rdx)

T_create:

		xor r13, r13
		xor r15, r15
		mov qword [ten], 0

		mov rax, qword [cur_per]					; Get symbol
		mov rbx, 0ah			

T_start:
		xor rdx, rdx
		mov rbx, 0ah
		div rbx								; Get fir cifra
		add r15, 1

		cmp rax, 0h							; if end of num
		je T_end							; break

		add [ten], rdx
		mov r14, qword [ten]
		shl r14, 3
		add r14, [ten]
		add r14, [ten]
		mov qword [ten], r14
											; push nums into stack
		jmp T_start
T_end:		

		add [ten], rdx
		mov r14, qword [ten]
		shl r14, 3
		add r14, [ten]
		add r14, [ten]
		mov qword [ten], r14

		add r15, 1
		
;----------

		mov rax, qword [ten]					; Get symbol
		

T_1start:
		xor rdx, rdx
		mov rbx, 0ah
		div rbx								; Get fir cifra
		sub r15, 1

		cmp r15, 0h							; if end of num
		je T_1end							; break

		mov qword [cur_per], rax

		cmp r13, 0
		je T_fir_per

		add rdx, '0'
		mov qword [cur_byte], rdx
		mov rcx, cur_byte
		mov rax, 4  	; rax = 4
		mov rbx, 1		; where write? (in terminal)
		mov rdx, 1		; len of write
		int 80h

T_fir_per:
		mov r13, 1488
											; push nums into stack

		mov rax, qword [cur_per]

		jmp T_1start
T_1end:		

;----------

		add rdx, '0'
		mov qword [cur_byte], rdx
		mov rcx, cur_byte
		mov rax, 4  	; rax = 4
		mov rbx, 1		; where write? (in terminal)
		mov rdx, 1		; len of write
		int 80h

		ret


_start:

jump0:
 push 1

jump2:
 push 1

jump4:
 pop rbx
 pop rax
 add rax, rbx
 push rax 

jump5:
 pop rax
 mov [faker2], rax

jump7:
 push jump9
 jmp jump15

jump9:
jump11:
 mov rax, [faker4]
 push rax

 pop rcx
 add rcx, 0x30
 mov [cur_per], rcx
 mov rax, 8
	mov rbx, filename
 mov rcx, 0x0700
 int 0x80
 mov rBX, rAX
 mov rAX, 4
 mov rCX, cur_per
 mov rDX, 1
 int 0x80
 mov rAX, 6
 int 0x80

jump12:
jump13:
jmp all_end 
;!!! NOT MAIN FUNCTION UNDER !!!;

 mov rcx, Meow_start
 mov rax, 4
 mov rbx, 1
 mov rdx, Meow_len
 int 80h

jump14:
 mov rcx, Meow_start
 mov rax, 4
 mov rbx, 1
 mov rdx, Meow_len
 int 80h

jump15:
jump17:
 mov rax, [faker2]
 push rax

 push 3

jump19:
 pop rbx
 pop rax
 mul rbx
 push rax 

jump20:
 pop rax
 mov [faker4], rax

jump22:
 ret
jump24:
all_end:
 xor rbx, rbx
 mov rax, 1
 int 80h


