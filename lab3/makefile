all: float

float: float.o

	ld float.o -o float -m elf_i386

float.o: float.s

	as --gstabs float.s -o float.o --32
