
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<assert.h>
#include"my_assembly_command_info.h"

// Конекшон проца и игры
// pipe - файл гугить!
// читаем пайп - возвращает данные и управление игре
// НЕ ЗАБЫТЬ ДАТЬ СИГНАЛ ЗАВЕРШЕНИЯ
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#define VOID_SKIPPER								\
		while(main_buffer->buffer[cur_poz] == '\0')	\
			cur_poz++;								\


#define SYM_SKIPPER									\
		while(main_buffer->buffer[cur_poz] != '\0')	\
			cur_poz++;								\


#define COPYPASTE_FROM_MY_PRINTF					\
";====================== ascii --> 10-razr ===============================;\n\
;!! Input:	cur_per = curren peremennaya\n\
;!!	Exit: 	Printf 10razr\n\
;!!	Destroy:	rax, rbx, rdx, rsi, r13\n\
;========================================================================;\n\
;rdx:rax / rbx = rax (ost. rdx)\n\
\n\
T_create:\n\
\n\
		xor r13, r13\n\
		xor r15, r15\n\
		mov qword [ten], 0\n\
\n\
		mov rax, qword [cur_per]					; Get symbol\n\
		mov rbx, 0ah			\n\
\n\
T_start:\n\
		xor rdx, rdx\n\
		mov rbx, 0ah\n\
		div rbx								; Get fir cifra\n\
		add r15, 1\n\
\n\
		cmp rax, 0h							; if end of num\n\
		je T_end							; break\n\
\n\
		add [ten], rdx\n\
		mov r14, qword [ten]\n\
		shl r14, 3\n\
		add r14, [ten]\n\
		add r14, [ten]\n\
		mov qword [ten], r14\n\
											; push nums into stack\n\
		jmp T_start\n\
T_end:		\n\
\n\
		add [ten], rdx\n\
		mov r14, qword [ten]\n\
		shl r14, 3\n\
		add r14, [ten]\n\
		add r14, [ten]\n\
		mov qword [ten], r14\n\
\n\
		add r15, 1\n\
		\n\
;----------\n\
\n\
		mov rax, qword [ten]					; Get symbol\n\
		\n\
\n\
T_1start:\n\
		xor rdx, rdx\n\
		mov rbx, 0ah\n\
		div rbx								; Get fir cifra\n\
		sub r15, 1\n\
\n\
		cmp r15, 0h							; if end of num\n\
		je T_1end							; break\n\
\n\
		mov qword [cur_per], rax\n\
\n\
		cmp r13, 0\n\
		je T_fir_per\n\
\n\
		add rdx, '0'\n\
		mov qword [cur_byte], rdx\n\
		mov rcx, cur_byte\n\
		mov rax, 4  	; rax = 4\n\
		mov rbx, 1		; where write? (in terminal)\n\
		mov rdx, 1		; len of write\n\
		int 80h\n\
\n\
T_fir_per:\n\
		mov r13, 1488\n\
											; push nums into stack\n\
\n\
		mov rax, qword [cur_per]\n\
\n\
		jmp T_1start\n\
T_1end:		\n\
\n\
;----------\n\
\n\
		add rdx, '0'\n\
		mov qword [cur_byte], rdx\n\
		mov rcx, cur_byte\n\
		mov rax, 4  	; rax = 4\n\
		mov rbx, 1		; where write? (in terminal)\n\
		mov rdx, 1		; len of write\n\
		int 80h\n\
\n\
		ret\n"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

//==================================================================
//!
//! This programm compile my asm to asm
//!
//! Author: Vladimir Gribanov  	Version 1.0.0
//!
//! UPD 0.0.1 Read file
//! UPD 0.0.2 Work with Compile_pozition = 0 (50%)
//! UPD 0.1.0 Work with 0 - 6, 8 - 9 funcions, but not all pusr & popr (i am too lasy for names)
//! UPD 0.2.0 Now pop and pushr combinations normal work (but not optimized)
//! UPD 0.2.9 Danger ifs worked
//! UPD 0.2.9.9 It is compiling, but ifs & jumps not worked C^:
//! UPD 0.4.0 Ifs & jump work normally and compiling 
//! UPD 0.5.0 Sucsessfull copypast and impliment my %d printf in nasm
//! UPD 0.5.1 Meow implimented
//! UPD 1.0.0 FINNALY functions work & reworked jump system (but in my syntax you must be carefull with stack)
//!
//==================================================================

//--------------
// Globals here

const int Start_pos = 0;
const int Pushr_pos = 1;
const int Two_pushrs_pos = 2;
const int Jump_if_pos = 3;
const int End_pos = 4;

int Compile_pozition = 0;
unsigned long int Cur_jump = 0;

//--------------
// Classes here

//-----------------------------------------------
//! This class realize struct with buffer
//-----------------------------------------------
class c_buffer
{
	public:

	char* buffer;
	long int size;
};

//------------------------
// Function declares here

class c_buffer *buffer_get(void);

long int get_file_size(FILE *text);
long int file_read(FILE *text, long int size_of_text, char* my_buff);

long int start_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog); //
long int pushr_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog); //
long int pushr_two_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog); //
long int jump_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog); //
//long int function_printer(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog); // NI

void n_sub(char *my_buff, long int size_of_text);
void compile(class c_buffer *main_buffer);


//========================================
//
//	MMM   MMM      A      II  NNN   NN
//	MMMM MMMM     AAA         NNNN  NN
//	MM MMM MM    AA AA    II  NN NN NN
//	MM     MM   AAAAAAA   II  NN  NNNN
//  MM     MM  AA     AA  II  NN   NNN
//
//========================================
int main()
{
	class c_buffer *main_buffer = NULL;

	main_buffer = buffer_get();
	compile(main_buffer);

	delete main_buffer;
	return 0;
}


//-----------------------------------------------------------------
//!
//! Compile code into asm
//!
//-----------------------------------------------------------------
void compile(class c_buffer *main_buffer)
{
	FILE* asm_prog = fopen("asm_prog.asm", "w");

	Compile_pozition = 0;
	long int cur_poz = 0;
	int is_end = 0;

	//fprintf(asm_prog, "");
	fprintf(asm_prog, "global _start \n");
	fprintf(asm_prog, "SECTION .data \n\n");

	int i = 0;
	int max_faker = 100;

	fprintf(asm_prog, " filename db \"pipe.txt\", 0\n");
	fprintf(asm_prog, " Meow_start	db	");
	fprintf(asm_prog, " \" /\\_/\\\",10,\"(<o.o>)\",10,\" )=*=(\",10,\"(\\|.|/)~~**\",10,\"Meow ^^\", 10\n");
	fprintf(asm_prog, " Meow_len equ $ - Meow_start\n");
	fprintf(asm_prog, " out_print	db	\">>> Output: \" \n");
	fprintf(asm_prog, " length	equ	$ - out_print\n");
	fprintf(asm_prog, " my_enter	db	10\n");
	fprintf(asm_prog, " ten			dq	0\n cur_per		dq	0\n cur_byte		dq	0\n");

	while(i != max_faker)
	{
		fprintf(asm_prog, " faker%d dq 0\n", (i + 1));
		i++;
	}

	/*i = 0;

	while(i != max_faker)
	{
		fprintf(asm_prog, " func_pointer_%d: func_%d\n", (i + 1), (i + 1));
		i++;
	}*/

	long int prev_jmp = -1;
	bool end_jmp_print = false;

	fprintf(asm_prog, "\nSECTION .text \n\n");
	fprintf(asm_prog, COPYPASTE_FROM_MY_PRINTF);
	fprintf(asm_prog, "\n\n");
	fprintf(asm_prog, "_start:\n\n");

	while(cur_poz < main_buffer->size && is_end != 2)
	{
		VOID_SKIPPER

		if(prev_jmp != Cur_jump)
		{
			fprintf(asm_prog, "jump%ld:\n", Cur_jump); 
			prev_jmp = Cur_jump;
		}

		if(is_end == 1 && end_jmp_print == false)
		{
			end_jmp_print = true;
			fprintf(asm_prog, "jmp all_end \n;!!! NOT MAIN FUNCTION UNDER !!!;\n\n");
		}

		switch(Compile_pozition)
		{
			case Start_pos:
				printf("> Start pos active <%d>\n", cur_poz);
				cur_poz = start_moves(main_buffer, cur_poz, asm_prog);
				break;
			case Pushr_pos:
				printf("> One pushr active \n");
				cur_poz = pushr_moves(main_buffer, cur_poz, asm_prog);
				break;
			case Two_pushrs_pos:
				printf("> Two pushr active \n");
				cur_poz = pushr_two_moves(main_buffer, cur_poz, asm_prog);
				break;
			case Jump_if_pos:
				printf("> If-jump active \n");
				cur_poz = jump_moves(main_buffer, cur_poz, asm_prog);
				break;

			case End_pos:
				is_end++;
				Compile_pozition = Start_pos;
				break;
		}
		//Cur_jump++;
	}

	fprintf(asm_prog, "all_end:\n");

	fprintf(asm_prog, " xor rbx, rbx\n");
	fprintf(asm_prog, " mov rax, 1\n");
	fprintf(asm_prog, " int 80h\n\n\n");

	fclose(asm_prog);

	system("nasm -f elf64 asm_prog.asm");
	system("ld -o asm_prog asm_prog.o");

	printf("\n\n\n");
	printf(">>> Compile complete\n>>> Use \"./asm_prog\" if you want to run it\n\n");
}


/*/-----------------------------------------------------------------
//!
//! Print functions in asm  NI
//!
//-----------------------------------------------------------------
long int function_printer(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog)
{
	
	
	return cur_poz;
}*/


//-----------------------------------------------------------------
//!
//! Do jump moves & return cur position 
//!
//-----------------------------------------------------------------
long int jump_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog)// WORK
{
	int jump_type = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER
	VOID_SKIPPER
	int fir_arg = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER
	VOID_SKIPPER
	int sec_arg = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER
	VOID_SKIPPER
	int jump_pos = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER

	printf("JUMP = %d\n", jump_type);
	Cur_jump = Cur_jump + 4;

	switch(jump_type)
	{
		case Je:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n je jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;
			break;
		case Jne:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n jne jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;			
			break;
		case Ja:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n ja jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;			
			break;
		case Jae:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n jae jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;			
			break;
		case Jb:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n jb jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;			
			break;
		case Jbe:
			fprintf(asm_prog, " mov rax, [faker%d]\n mov rbx, [faker%d]\n cmp rax, rbx\n jbe jump%d\n\n", fir_arg, sec_arg, jump_pos);
			Compile_pozition = Start_pos;			
			break;
		default:
			printf("Error in if_jumps!\n");
			delete main_buffer;
			fclose(asm_prog);
			assert(false);
			break;
	}

	return cur_poz;
}


//-----------------------------------------------------------------
//! 
//! Do 2 moves & return mew cur position
//!
//-----------------------------------------------------------------
long int pushr_two_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog)
{
	int reg_num = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER
	VOID_SKIPPER
	int com_num = atoi(main_buffer->buffer + cur_poz);

	switch(com_num)
	{
		case Sub:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n sub rbx, [faker%d]\n push rbx\n\n", reg_num);
			SYM_SKIPPER
			Compile_pozition = Start_pos;
			break;
		case Add:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n add rbx, [faker%d]\n push rbx\n\n", reg_num);
			SYM_SKIPPER
			Compile_pozition = Start_pos;
			break;
		case Mul:
			Cur_jump++;
			fprintf(asm_prog, " pop rax\n mov rbx, [faker%d]\n mul rbx\n\n push rax\n\n", reg_num);
			SYM_SKIPPER
			Compile_pozition = Start_pos;
			break;
		case Div:
			Cur_jump++;
			fprintf(asm_prog, " pop rax\n mov rbx, [faker%d]\n div rbx\n push rax\n\n", reg_num);
			SYM_SKIPPER
			Compile_pozition = Start_pos;
			break;
		default:
			Compile_pozition = Start_pos;
			fprintf(asm_prog, " mov rax, [faker%d]\n push rax\n\n", reg_num);
			break;
	}

	return cur_poz;
}


//-----------------------------------------------------------------
//!
//! Do 1 moves & return new cur position
//!
//-----------------------------------------------------------------
long int pushr_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog)
{
	int com_num = 0;
	int reg_num = atoi(main_buffer->buffer + cur_poz);
	SYM_SKIPPER
	VOID_SKIPPER
	com_num = atoi(main_buffer->buffer + cur_poz);

	switch(com_num)
	{	
		case Pop_reg:
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			VOID_SKIPPER
			com_num = atoi(main_buffer->buffer + cur_poz);
			fprintf(asm_prog, " mov rax, [faker%d]\n mov [faker%d], rax\n\n", reg_num, com_num);
			Compile_pozition = Start_pos;
			SYM_SKIPPER
			break;
		case Push_reg:
			Cur_jump = Cur_jump + 2;
			fprintf(asm_prog, " mov rax, [faker%d]\n push rax\n", reg_num);
			SYM_SKIPPER
			Compile_pozition = Two_pushrs_pos;
			break;
		default:
			Compile_pozition = Start_pos;
			fprintf(asm_prog, " mov rax, [faker%d]\n push rax\n\n", reg_num);
			break;
	}

	return cur_poz;
}


//-----------------------------------------------------------------
//!
//! Do 0 moves & return new buff pozition
//!
//! IMPLIMENTED JUMPS (but error in adress)
//!
//-----------------------------------------------------------------
long int start_moves(class c_buffer *main_buffer, long int cur_poz, FILE* asm_prog)
{
	int com_num = atoi(main_buffer->buffer + cur_poz);

	if(com_num == Je || com_num == Jne || com_num == Jae || com_num == Ja || com_num == Jb || com_num == Jbe)
	{
		Compile_pozition = Jump_if_pos;
		return cur_poz;
	}

	com_num = atoi(main_buffer->buffer + cur_poz);

	switch(com_num)
	{
		case Meow:
			Cur_jump++;
			fprintf(asm_prog, " mov rcx, Meow_start\n mov rax, 4\n mov rbx, 1\n mov rdx, Meow_len\n int 80h\n\n");
			SYM_SKIPPER
			break;
		case Add:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n pop rax\n add rax, rbx\n push rax \n\n");
			SYM_SKIPPER
			break;
		case Sub:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n pop rax\n sub rax, rbx\n push rax \n\n");
			SYM_SKIPPER
			break;
		case Mul:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n pop rax\n mul rbx\n push rax \n\n");
			SYM_SKIPPER
			break;
		case Div:
			Cur_jump++;
			fprintf(asm_prog, " pop rbx\n pop rax\n div rbx\n push rax \n\n");
			SYM_SKIPPER
			break;
		case Push_reg:
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			Compile_pozition = Pushr_pos;
			break;
		case Pop_reg:
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			VOID_SKIPPER
			com_num = atoi(main_buffer->buffer + cur_poz);
			fprintf(asm_prog, " pop rax\n mov [faker%d], rax\n\n", com_num);
			SYM_SKIPPER
			break;
		case Push:
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			VOID_SKIPPER
			com_num = atoi(main_buffer->buffer + cur_poz);
			fprintf(asm_prog, " push %d\n\n", com_num);
			SYM_SKIPPER
			break;
		case Pop:
			Cur_jump++;
			/*fprintf(asm_prog, " pop rcx\n mov [cur_per], rcx\n mov rcx, out_print\n mov rax, 4\n mov rbx, 1\n mov rdx, length\n int 80h\n call T_create\n mov rcx, my_enter\n mov rax, 4\n mov rbx, 1\n mov rdx, 1\n int 80h\n\n");	
			printf("test:<%s>\n\n", main_buffer->buffer + cur_poz);*/
			fprintf(asm_prog, " pop rcx\n add rcx, 0x30\n mov [cur_per], rcx\n");
			fprintf(asm_prog, " mov rax, 8\n");
  			fprintf(asm_prog, "	mov rbx, filename\n");
            fprintf(asm_prog, " mov rcx, 0x0700\n");
            fprintf(asm_prog, " int 0x80\n");
            fprintf(asm_prog, " mov rBX, rAX\n");
            fprintf(asm_prog, " mov rAX, 4\n");
            fprintf(asm_prog, " mov rCX, cur_per\n");
            fprintf(asm_prog, " mov rDX, 1\n");
            fprintf(asm_prog, " int 0x80\n");
            fprintf(asm_prog, " mov rAX, 6\n");
            fprintf(asm_prog, " int 0x80\n\n");
			SYM_SKIPPER
			break;
		case Jum:
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			VOID_SKIPPER
			com_num = atoi(main_buffer->buffer + cur_poz);
			fprintf(asm_prog, " jmp jump%ld\n\n", com_num);
			SYM_SKIPPER
			break;
		case Fcall:		// NW
			Cur_jump = Cur_jump + 2;
			SYM_SKIPPER
			VOID_SKIPPER
			com_num = atoi(main_buffer->buffer + cur_poz);
			fprintf(asm_prog, " push jump%ld\n",Cur_jump);
			fprintf(asm_prog, " jmp jump%ld\n\n", com_num);
			SYM_SKIPPER
			break;
		case Fret:		// NW
			Cur_jump++;
			fprintf(asm_prog, " ret\n");
			SYM_SKIPPER
		case End:
			Cur_jump++;
			SYM_SKIPPER
			Compile_pozition = End_pos;
			break;

		//
	}

	return cur_poz;
}

//const int Start_pos = 0;
//const int Pushr_pos = 1;
//const int Two_pushrs_pos = 2;
//const int Jump_if_pos = 3;
//const int End_pos = 4;
//Compile_pozition


//-----------------------------------------------------------------
//!
//! Считывает файл в буфер, удаляя пробелы, табы и энтеры
//!
//! @param[out] char* - указатель на полученный массив
//!
//-----------------------------------------------------------------
class c_buffer *buffer_get(void)
{
	class c_buffer *main_buffer = NULL;
	main_buffer = new class c_buffer;
	FILE* text = fopen("compile.txt","r");

	main_buffer->size = get_file_size(text);
	main_buffer->buffer = new char [main_buffer->size];
	
	file_read(text, main_buffer->size, main_buffer->buffer);

	fclose(text);

	return main_buffer;
}


//-----------------------------------------------------------------
//!
//! Считывает размер файла для записи в буфер
//!
//! @param[in] FILE *text - файл, размер которого надо узнать
//!
//! @param[out] size_of_text - Размер текста
//!
//-----------------------------------------------------------------
long int get_file_size(FILE *text)
{
    long int size_of_text = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_END);
    size_of_text = ftell(text);

    return size_of_text;
}


//-----------------------------------------------------------------
//!
//! Функция находит '\n', ' ', '\t'  в буфере и заменяет их на '\0'
//!
//! @param[in] char *my_buff - указатель на буфер
//! @param[in] long int size_of_text - длина буфера
//!
//-----------------------------------------------------------------
void n_sub(char *my_buff, long int size_of_text)
{
    int cur_poz = 0;

    while(cur_poz != size_of_text)
    {
        if(my_buff[cur_poz] == '\n' || my_buff[cur_poz] == ' ' || my_buff[cur_poz] == '\t')
            my_buff[cur_poz] = '\0';

        cur_poz++;
    }
}


//------------------------------------------------------------------
//!
//! Считывает файл и записывает в буфер + возвращает количество строк
//!
//! @param[in] FILE *text - файл
//! @param[in] long int size_of_text - размер файла
//! @param[in] char* my_buff - буфер
//!
//! @param[out] num_of_str - количество строк
//!
//------------------------------------------------------------------
long int file_read(FILE *text, long int size_of_text, char* my_buff)
{
    long int num_of_str = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_SET);
    fread(my_buff, sizeof(char), size_of_text, text);
    n_sub(my_buff, size_of_text);

    return num_of_str;
}











