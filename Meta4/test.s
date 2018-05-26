	.text
	.file	"test.ll"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.globl	teste
	.align	16, 0x90
	.type	teste,@function
teste:                                  # @teste
	.cfi_startproc
# BB#0:
	subq	$24, %rsp
.Ltmp0:
	.cfi_def_cfa_offset 32
	movl	$62, 20(%rsp)
	movabsq	$4617878467915022336, %rax # imm = 0x4016000000000000
	movq	%rax, 8(%rsp)
	movw	$1, 6(%rsp)
	movb	$97, 5(%rsp)
	movl	20(%rsp), %edi
	callq	putchar
	movl	$6, (%rsp)
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
.Lfunc_end1:
	.size	teste, .Lfunc_end1-teste
	.cfi_endproc

	.type	a,@object               # @a
	.comm	a,4,4
	.type	b,@object               # @b
	.comm	b,1,1
	.type	c,@object               # @c
	.comm	c,8,8
	.type	d,@object               # @d
	.comm	d,2,2

	.section	".note.GNU-stack","",@progbits
