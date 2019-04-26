.code32

SYSEXIT = 1

.section .data

	liczba1: .long 0x50404040, 0xF3030303, 0x20202020, 0x01010101
	liczba2: .long 0xF4040403, 0x40303030, 0x02020202, 0x10101010

	liczba_len = .-liczba2

	counter = ((liczba_len)/4)-1

.section .text
.global _start

_start:

	mov $counter, %ecx	# ustawienie licznika w ecx

	clc			# czyszczenie CF = 0

	pushf			# flagi na stos

loop:

	cmpl $0, %ecx			# porownanie 0 z licznikiem 3,2,1,0...

	jl add_last_carry		# jesli mniejszy od zera skok do ostatniego przeniesienia

	mov liczba1(,%ecx,4), %eax	# eax = liczba1 [ecx]

	mov liczba2(,%ecx,4), %ebx	# ebx = liczba2 [ecx]

	popf				# zdjecie flag ze stosu

	adcl %ebx, %eax			# dodanie liczb

	push %eax			# dodanie eax na stos

	pushf				# flagi na stos

	decl %ecx			# dekrementcja licznika

	jmp loop			# skok na poczatek petli

add_last_carry:

	popf				# zdjecie flag ze stosu

	jnc push_zero			# jesli CF = 0 push_zero

	push $0x1			# jesli CF = 1 dodanie 1 na stos

	jmp exit

push_zero:

	push $0x0			# dodanie 0 na stos

exit:

	mov $SYSEXIT, %eax		# koniec programu

	mov $0, %ebx

	int $0x80
