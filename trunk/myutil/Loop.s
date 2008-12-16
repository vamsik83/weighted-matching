.data
ask_input:
	.string "Please Enter n followed by n integers\n"
tell_scanning:
	.string "Scanning %u \n"
current_brk_base:
	.string "Current brk_base is 0x%x \n"
scan_unsigned:
	.string "%u"
print_unsigned:
	.string "scanned %u\n"
array_size:
	.long 0
brk_base:
	.long 0
brk_start:
	.long 0
i:
	.long 0
j:
	.long 0

.text
	.globl main 

main:
		pushl $0
		call sbrk
		movl %eax, brk_base
		movl %eax, brk_start
		pushl brk_base
		push $current_brk_base
		call printf
		
		push $ask_input
		call printf
		push $array_size
		push $scan_unsigned 
		call scanf
		push array_size
		push $tell_scanning
		call printf
		sall $2,array_size
		pushl array_size
		sarl $2,array_size
		call sbrk
		
.FORLOOP1:
		pushl brk_base 
		pushl $scan_unsigned
		call scanf
		addl $4,brk_base
		pushl brk_base
		push $print_unsigned
		call printf
		decl array_size
		jne	.FORLOOP1
#Do a bubble sort
		movl $0,i
.bsort1:
		movl $0,j
.bsort2:
		incl j
		cmpl j,array_size
		jne .bsort3
		cmpl 
.bsort3:
	 	incl i
	 	cmpl i,array_size
	 	jne .bsort1

#exit
		mov $1, %eax
		xorl %ebx, %ebx
		int $0x80
