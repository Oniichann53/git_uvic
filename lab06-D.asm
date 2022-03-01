.data

seven_segment:
	.byte 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x5f, 0x7c, 0x39, 0x5e, 0x79, 0x71
	
.text
	addi $a0, $zero, 0xe
	addi $a1, $zero, 1
	jal display_hex_digit	
	
	
	addi $a0, $zero, 0xa
	addi $a1, $zero, 0
	jal display_hex_digit
	
finish:
	addi $v0, $zero, 10
	syscall


# $a0: hex digit to be displayed
# $a1: 0 == right display; 1 == left display

display_hex_digit:
	addi $sp, $zero, -12
	sw $ra, 8($sp)
	sw $s0, 4($sp)
	sw $s1, 0($sp)
	
	la $s0, seven_segment
	add $s0, $s0, $a0
	lb $s1, 0($s0)
	
	la $s0, 0xffff0010
	add $s0, $s0, $a1
	sb $s1, 0($s0)
	
	lw $ra, 8($sp)
	lw $s0, 4($sp)
	lw $s1, 0($sp)
	addi $sp, $zero, -12
	jr $ra
