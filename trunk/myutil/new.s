.data
x1:
     .long   2
.text
     .global _start
_start:
      movl    $6, %eax
      #%eax is now 6
      movw    %eax, x1 
      #value is now 6
      movl    0, %ebx
	  #%ebx is now 0 
	  movb    %al, %bl 
	  #%ebx is now 6 
	  movl    value, %ebx 
	  # %ebx is now 2 
	  movl    $value, %esi 
	  # %esi is now the address of value 
	  movw    value(, %ebx, 1), %bx 
	  # %ebx is now 0
# Linux sys_exit 
        mov     $1, %eax 
		xorl    %ebx, %ebx 
		int     $0x80
