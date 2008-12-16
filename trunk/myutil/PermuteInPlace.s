	.file	"PermuteInPlace.c"
	.section	.rodata
.LC0:
	.string	"%u "
	.text
.globl Permute
	.type	Permute,@function
Permute:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%esp, -32(%ebp)
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, -16(%ebp)
	movl	16(%ebp), %eax
	sall	$2, %eax
	subl	$4, %eax
	addl	$4, %eax
	movl	%eax, %edx
	shrl	$2, %edx
	andl	$3, %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	subl	%eax, %esp
	movl	$0, -24(%ebp)
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
.L2:
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jb	.L4
	jmp	.L3
.L4:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	incl	%eax
	cmpl	%eax, (%edx,%ecx)
	jne	.L5
	leal	-8(%ebp), %eax
	incl	(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	12(%ebp), %eax
	movl	(%eax,%edx), %eax
	movl	%eax, -12(%ebp)
	jmp	.L2
.L5:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	movl	(%eax,%edx), %eax
	leal	0(,%eax,4), %edx
	movl	12(%ebp), %eax
	movl	(%eax,%edx), %eax
	movl	%eax, -20(%ebp)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	movl	(%eax,%edx), %eax
	leal	0(,%eax,4), %ecx
	movl	12(%ebp), %edx
	movl	-12(%ebp), %eax
	movl	%eax, (%edx,%ecx)
	movl	-20(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebp), %eax
	movl	(%eax,%edx), %eax
	movl	%eax, -20(%ebp)
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	incl	%eax
	movl	%eax, (%edx,%ecx)
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	.L2
.L3:
	movl	$0, -28(%ebp)
.L6:
	movl	-28(%ebp), %eax
	cmpl	16(%ebp), %eax
	jb	.L9
	jmp	.L7
.L9:
	subl	$8, %esp
	movl	-28(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	12(%ebp), %eax
	pushl	(%eax,%edx)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	leal	-28(%ebp), %eax
	incl	(%eax)
	jmp	.L6
.L7:
	movl	-32(%ebp), %esp
	leave
	ret
.Lfe1:
	.size	Permute,.Lfe1-Permute
.globl LinearFill
	.type	LinearFill,@function
LinearFill:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	$0, -4(%ebp)
.L11:
	movl	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	jb	.L14
	jmp	.L10
.L14:
	movl	-4(%ebp), %eax
	leal	0(,%eax,4), %ecx
	movl	data_items, %edx
	movl	-4(%ebp), %eax
	movl	%eax, (%edx,%ecx)
	leal	-4(%ebp), %eax
	incl	(%eax)
	jmp	.L11
.L10:
	leave
	ret
.Lfe2:
	.size	LinearFill,.Lfe2-LinearFill
	.section	.rodata
.LC1:
	.string	"Please enter n:"
.LC2:
	.string	"%u"
.LC3:
	.string	"Please enter the permutation\n"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	subl	$12, %esp
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC2
	call	scanf
	addl	$16, %esp
	subl	$12, %esp
	movl	-4(%ebp), %eax
	sall	$2, %eax
	pushl	%eax
	call	malloc
	addl	$16, %esp
	movl	%eax, data_items
	subl	$12, %esp
	pushl	-4(%ebp)
	call	LinearFill
	addl	$16, %esp
	subl	$12, %esp
	movl	-4(%ebp), %eax
	sall	$2, %eax
	pushl	%eax
	call	malloc
	addl	$16, %esp
	movl	%eax, perm
	subl	$12, %esp
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	movl	$0, -8(%ebp)
.L16:
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	jb	.L19
	jmp	.L17
.L19:
	subl	$8, %esp
	movl	-8(%ebp), %eax
	sall	$2, %eax
	addl	perm, %eax
	pushl	%eax
	pushl	$.LC2
	call	scanf
	addl	$16, %esp
	leal	-8(%ebp), %eax
	incl	(%eax)
	jmp	.L16
.L17:
	subl	$4, %esp
	pushl	-4(%ebp)
	pushl	data_items
	pushl	perm
	call	Permute
	addl	$16, %esp
	leave
	ret
.Lfe3:
	.size	main,.Lfe3-main
	.comm	data_items,4,4
	.comm	perm,4,4
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.2.3 20030502 (Red Hat Linux 3.2.3-56)"
