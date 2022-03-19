	.data
KEYBOARD_EVENT_PENDING:
	.word	0x0
KEYBOARD_EVENT:
	.word   0x0
KEYBOARD_COUNTS:
	.space  128
NEWLINE:
	.asciiz "\n"
SPACE:
	.asciiz " "
	
	
	.eqv 	LETTER_a 97
	.eqv	LETTER_b 98
	.eqv	LETTER_c 99
	.eqv 	LETTER_d 100
	.eqv 	LETTER_space 32
	
	
	.text  
main:
	la $s0, 0xffff0000	
	lb $s1, 0($s0)
	ori $s1, $s1, 0x02
	sb $s1, 0($s0)
	

check_for_event:
	la $s0, KEYBOARD_EVENT_PENDING
	lw $s1, 0($s0)
	beq $s1, $zero, check_for_event
	
key_process:
	la $s2, KEYBOARD_COUNTS
	lw $s3, 0($s0)
	lw $s4, 0($s2)
	beq $s3, LETTER_a, key_count
	beq $s3, LETTER_b, key_count
	beq $s3, LETTER_c, key_count
	beq $s3, LETTER_d, key_count
	beq $s3, LETTER_space, print
	beq $zero, $zero, reset
	
key_count:
	addi $s4, $s4, 1
	sw $s4, 0($s2)
	beq $zero, $zero, reset

print:
	la $a0, KEYBOARD_COUNTS
		

reset:
	addi $s1, $zero, 0
	sw $s1, 0($s0)
	beq $zero, $zero, check_for_event

	.kdata

	.ktext 0x80000180
__kernel_entry:
	mfc0 $k0, $13		
	andi $k1, $k0, 0x7c	
	srl  $k1, $k1, 2
		
	beq $zero, $k1, __is_interrupt
	
__is_exception:
	beq $zero, $zero, __exit_exception
	
__is_interrupt:
	andi $k1, $k0, 0x0100	
	bne $k1, $zero, __is_keyboard_interrupt
	
	beq $zero, $zero, __exit_exception
	
__is_keyboard_interrupt:
	la $k0, 0xffff0004
	lw $k1, 0($k0)
	la $k0, KEYBOARD_EVENT_PENDING
	sw $k1, 0($k0)
	
	beq $zero, $zero, __exit_exception
__exit_exception:
	eret
	
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# STUDENTS MAY MODIFY CODE ABOVE

	
