SYSEXIT = 1
SYSWRITE = 4
SYSREAD = 3
STDOUT = 1
STDIN = 0

size = 32

.section .data

	buf: .space size

	buf_len = .-buf

.section .text

.global _start

_start:

read:

	mov $SYSREAD, %eax
	mov $STDIN, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx

	int $0x80

write:

	mov $SYSWRITE, %eax
	mov $STDOUT, %ebx
	mov $buf, %ecx
	mov $buf_len, %edx

	int $0x80

exit:

	mov $SYSEXIT, %eax
	mov $0, %ebx

	int $0x80
