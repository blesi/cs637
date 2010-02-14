# PURPOSE: TO CREATE A RANDOM NUMBER GENERATOR
#
#


# INPUT: I DONT REALLY KNOW
#
#	ARG PASSED THROUGH %EBX 
#	$8 = %EBX
#	$2 = %EDX
#
.TEXT

.globl fastrand
fastrand:
	PUSH 	%EBP
	MOV	%ESP,		%EBP
	MOVL 	8(%EBP), 	%EAX			# COMMENTS
	MOVL 	$33614,		%EDX	
	MULL	%EDX
	ADDL	%EDX,		%EAX
	CMPL	$0,		%EAX	
	JGE	OVERFLOW
#	movl	%edx,		%eax
	MOVL	%EBP,		%ESP
	POPL	%EBP
	RET


OVERFLOW:

	shll	$1,	%eax
	shrl	$1,	%eax
	incl	%eax
#	movl	%edx,	%eax
	movl	%ebp,	%esp
	popl	%ebp
	ret
