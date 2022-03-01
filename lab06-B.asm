.text
	addi $s0, $zero, 5
loop:
	beq $s0, $zero, finish
	
	jal display_dashes
	jal delay_400_msec

	jal display_blanks
	jal delay_400_msec
	
	jal display_digits_21
	jal delay_400_msec
	
	jal display_blanks
	jal delay_400_msec
	
	addi $s0, $s0, -1
	
	beq $zero, $zero, loop
	
finish:
	addi $v0, $zero, 10
	syscall


# Use only $s0 - $s7 for computation in
# this procedure.

display_dashes:	
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	la $a0, 0xffff0010
	la $a1, 0xffff0011
	addi $s1, $zero, 0x40
	sb $s1, 0($a0)
	sb $s1, 0($a1)
	lw $ra, 0($sp)
	
	addi $sp, $sp, 4
	jr $ra
	
	
# Use only $s0 - $s7 for computation in
# this procedure.

display_blanks:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	la $a0, 0xffff0010
	la $a1, 0xffff0011
	addi $s1, $zero, 0
	sb $s1, 0($a0)
	sb $s1, 0($a1)
	lw $ra, 0($sp)
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

		
# Use only $s0 - $s7 for computation in
# this procedure.
		
display_digits_21:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	la $a0, 0xffff0010
	la $a1, 0xffff0011
	addi $s1, $zero, 0x6
	addi $s2, $zero, 0x5B
	sb $s1, 0($a0)
	sb $s2, 0($a1)
	lw $ra, 0($sp)
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
# Nothing needs to be done for the
# delay_400_msec procedure.
	
delay_400_msec:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	addi $a0, $zero, 400
	addi $v0, $zero, 32
	syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
