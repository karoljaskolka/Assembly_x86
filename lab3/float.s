SYSEXIT = 1

.section .data

	dodatnia: .float 15
	ujemna: .float -5.5
	zero: .float 0

.section .text

.global _start

_start:

	FINIT

	#  NaN -> pierwiastek z liczby ujemnej
	FLDS ujemna
	FSQRT

	#  Inf -> dzielenie liczby dodatniej przez 0
	FLDS dodatnia
	FDIV zero

	# -Inf -> dzielenie liczby ujemnej przez 0
	FLDS ujemna
	FDIV zero

	#  0 -> dzielenie 0 przez liczbe dodatnia
	FLDS zero
	FDIV dodatnia

	# -0 -> dzielenie 0 przez liczbe ujemna
	FLDS zero
	FDIV ujemna

exit:

	mov $SYSEXIT, %eax
	mov $0, %ebx
	int $0x80
