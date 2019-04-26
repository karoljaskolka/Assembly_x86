.code32

SYSEXIT = 1

.section .data

	liczba1: .long 0x55555555, 0x25555555, 0x55555555, 0x55555555
	liczba2: .long 0x22222222, 0x33333333, 0x22222222, 0x33333333

	liczba_len = .-liczba2

	counter = ((liczba_len)/4)-1

.section .text
.global _start

_start:

	mov $counter, %ecx	# ustawienie licznika w ecx

	clc			# czyszczenie CF = 0

	pushf			# dodanie flag na stos

loop:

	cmpl $0, %ecx			# porownanie 0 z licznikiem 3,2,1,0...

	jl clear			# jesli mniejszy od zera skok do ostatniego przeniesienia

	mov liczba1(,%ecx,4), %eax	# eax = liczba1 [ecx]

	mov liczba2(,%ecx,4), %ebx	# ebx = liczba2 [ecx]

	popf				# zdjecie flag ze stosu

	sbbl %ebx, %eax			# dodanie liczb

	push %eax			# dodanie eax na stos

	pushf				# dodanie flag na stos

	decl %ecx			# dekrementcja licznika

	jmp loop			# skok na poczatek petli

clear:

	popf				# zdjecie flag ze stosu

exit:
	mov $SYSEXIT, %eax		# koniec programu

	mov $0, %ebx

	int $0x80
