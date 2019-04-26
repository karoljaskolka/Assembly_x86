all: add subtract

add: add.o

	ld add.o -o add -m elf_i386

add.o: add.s

	as --gstabs add.s -o add.o --32

subtract: subtract.o

	ld subtract.o -o subtract -m elf_i386

subtract.o: subtract.s

	as --gstabs subtract.s -o subtract.o --32
