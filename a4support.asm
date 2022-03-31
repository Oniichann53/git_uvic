# Some support routines for use in completing
# UVic CSC 230, Spring 2022, Assignment #4
#
# Copyright 2022: Mike Zastre, UVic
#

.text
	j main
	
	
read_file_of_ints:
	add $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	
	add $s0, $zero, $a0	# filename
	add $s1, $zero, $a1	# destination array
	
	li $v0, 13		# open file; file name already in $a0
	addi $a1, $zero, 0	# 0 is "open for reading"
	addi $a2, $zero, 0	# 0 is "ignore more"
	syscall
	
	# Any problems opening the file
	beq $v0, -1, read_file_of_ints_open_error
	
	# If we're here, we successfully opened the file.
	#
	
	add $s2, $zero, $v0	# $s2 is the file-descriptor index
	
	# Fetch the number of integers in the file.
	# We'll make the array bytes do double-duty here
	# as we read in the four bytes (i.e. bytes in an int)
	li $v0, 14
	add $a0, $zero, $s2	# file descriptor
	add $a1, $zero, $s1	# array memory
	addi $a2, $zero, 4	# one integer is stored in four bytes
	syscall
	lw $s3, 0($s1)		# Read in the length. No error checking here.
	
	# We can read all of the integers at once
	li $v0, 14
	add $a0, $zero, $s2
	add $a1, $zero, $s1
	add $a2, $zero, $s3	# This is  the # of integers...
	sll $a2, $a2, 2		# ... which must be multipled by four to get # of bytes
	syscall
	
	beq $zero, $zero, read_file_of_ints_exit
	
	
# Print an error message, and then terminate the program.
#
read_file_of_ints_open_error:
	li $v0, 4
	la $a0, ERROR_MESSAGE
	syscall
	
	li $v0, 4
	add $a0, $zero, $s0
	syscall
	
	li $v0, 4
	la $a0, NEWLINE
	syscall
	
	# Do not pass GO, do not collect $200
	li $v0, 10
	syscall
	

read_file_of_ints_exit:
	addi $v0, $zero, 16	# close file
	add $a0, $zero, $s2	# but we need the file descriptor for this
	syscall
	
	add $v0, $zero, $s3	# Must ensure # of integers read in is also returned.
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	add $sp, $sp, 20
	jr $ra
	
	

dump_ints_to_console:
	add $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	
	add $s0, $zero, $a0	# We'll increment the address by four in a loop
	add $s1, $zero, $a1	# We'll decrement the count by one in a loop
	
	
dump_ints_to_console_loop_head:
	beq $s1, $zero, dump_ints_to_console_exit
	li $v0, 1
	lw $a0, 0($s0)
	syscall
	
	li $v0, 4
	la $a0, SPACE_CHAR
	syscall
	
	add $s0, $s0, 4
	add $s1, $s1, -1
	
	beq $zero, $zero, dump_ints_to_console_loop_head
	

dump_ints_to_console_exit:
	li $v0, 4
	la $a0, NEWLINE
	syscall

	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	add $sp, $sp, 20
	jr $ra
	
	
.data

ERROR_MESSAGE:	.asciiz "Could not open the file with name "
NEWLINE:	.asciiz "\n"
DEBUG:		.asciiz "DEBUG A\n"
SPACE_CHAR:	.asciiz " "
