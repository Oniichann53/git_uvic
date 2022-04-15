# Skeleton file provided to students in UVic CSC 230, Spring 2022
# Original file copyright Mike Zastre, 2022

.include "a4support.asm"


.globl main

.text 

main:
# STUDENTS MAY MODIFY CODE BELOW
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

	la $a0, FILENAME_1
	la $a1, ARRAY_A
	jal read_file_of_ints
	add $s0, $zero, $v0	# Number of integers read into the array from the file
	
	la $a0, ARRAY_A
	add $a1, $zero, $s0
	jal dump_ints_to_console
	
	
	# Part A test
	#
	
	la $a0, ARRAY_A
	la $a1, ARRAY_B
	add $a2, $zero, $s0
	jal accumulate_sum
	
	
	la $a0, ARRAY_B
	add $a1, $zero, $s0
	jal dump_ints_to_console
	
	
	# Part B test
	#
	
	la $a0, ARRAY_A
	la $a1, ARRAY_B
	add $a2, $zero, $s0
	jal accumulate_max
	
	la $a0, ARRAY_B
	add $a1, $zero, $s0
	jal dump_ints_to_console
	
	
	# Part C test
	#
	
	la $a0, ARRAY_A
	la $a1, ARRAY_B
	add $a2, $zero, $s0
	jal reverse_array
	
	la $a0, ARRAY_B
	add $a1, $zero, $s0
	jal dump_ints_to_console
	
	
	# Part D test
	la $a0, FILENAME_1
	la $a1, ARRAY_A
	jal read_file_of_ints
	add $s0, $zero, $v0
	
	la $a0, FILENAME_2
	la $a1, ARRAY_B
	jal read_file_of_ints
	# $v0 should be the same as for the previous call to read_file_of_ints
	# but no error checking is done here...
	
	la $a0, ARRAY_A
	la $a1, ARRAY_B
	la $a2, ARRAY_C
	add $a3, $zero, $s0
	jal pairwise_max
	
	la $a0, ARRAY_C
	add $a1, $zero, $s0
	jal dump_ints_to_console
	
	
	# Get outta here...
	add $v0, $zero, 10
	syscall	
	
	
# Accumulate sum: Accepts two integer arrays where the value to be
# stored at each each index in the *second* array is the sum of all
# integers from the index back to towards zero in the first
# array. The arrays are of the same size; the size is the third
# parameter.
#
accumulate_sum:
	addi $sp, $sp, -12
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $ra, 8($sp)

	lw $s0, 0($a0)
	sw $s0, 0($a1)
	addi $a0, $a0, 4
	addi $t0, $zero, 0
	
loop_as:
	addi $t0, $t0, 1
	lw $s0, 0($a0)
	lw $s1, 0($a1)
	addi $a1, $a1, 4
	add $s0, $s0, $s1
	sw $s0, 0($a1)
	addi $a0, $a0, 4
	bne $t0, $a2, loop_as

end_as:
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra


# Accumulate max: Accepts two integer arrays where the value to be
# stored at each each index in the *second* array is the maximum
# of all integers from the index back to towards zero in the first
# array. The arrays are of the same size;  the size is the third
# parameter.
#
accumulate_max:
	addi $sp, $sp, -12
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $ra, 8($sp)

	lw $s0, 0($a0)
	sw $s0, 0($a1)
	addi $a0, $a0, 4
	addi $t0, $zero, 0
loop_am:
	beq $t0, $a2, end_am
	addi $t0, $t0, 1
	lw $s0, 0($a1)
	addi $a1, $a1, 4
	lw $s1, 0($a0)
	slt $t1, $s0, $s1
	beq $t1, 1, set_max
	sw $s0, 0($a1)
	addi $a0, $a0, 4
	beq $zero, $zero, loop_am

set_max:
	sw $s1, 0($a1)
	addi $a0, $a0, 4
	beq $zero, $zero, loop_am

end_am:
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	lw $ra, 8($sp)
	addi $sp, $sp, 12
	jr $ra
	
	
# Reverse: Accepts an integer array, and produces a new
# one in which the elements are copied in reverse order into
# a second array.  The arrays are of the same size; 
# the size is the third parameter.
#
reverse_array:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	addi $t0, $a2, 0
	mul $t0, $t0, 4
	subi $t0, $t0, 4
	add $a0, $a0, $t0
loop_ra:
	lw $s0, 0($a0)
	sw $s0, 0($a1)
	subi $a0, $a0, 4
	addi $a1, $a1, 4
	subi $t0, $t0, 4
	bne $t0, -4, loop_ra
end_ra:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
# Reverse: Accepts three integer arrays, with the maximum
# element at each index of the first two arrays is stored
# at that same index in the third array. The arrays are 
# of the same size; the size is the fourth parameter.
#	
pairwise_max:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	addi $t0, $zero, 0
loop_pm:
	beq $t0, $a3, end_pm
	addi $t0, $t0, 1
	lw $s0, 0($a0)
	lw $s1, 0($a1)
	addi $a0, $a0, 4
	addi $a1, $a1, 4
	slt $t1, $s0, $s1
	beq $t1, 1, a1_greater
	sw $s0, 0($a2)
	addi $a2, $a2, 4
	beq $zero, $zero, loop_pm
a1_greater:
	sw $s1, 0($a2)
	addi $a2, $a2, 4
	beq $zero, $zero, loop_pm
end_pm:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	addi $sp, $sp, 12
	jr $ra
	
	
	
# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# STUDENTS MAY MODIFY CODE ABOVE
	

.data

.eqv	MAX_ARRAY_SIZE 1024

.align 2

ARRAY_A:	.space MAX_ARRAY_SIZE
ARRAY_B:	.space MAX_ARRAY_SIZE
ARRAY_C:	.space MAX_ARRAY_SIZE

FILENAME_1:	.asciiz "integers-10-314.bin"
FILENAME_2:	.asciiz "integers-10-1592.bin"


# STUDENTS MAY MODIFY CODE BELOW
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv


# In this region you can add more arrays and more
# file-name strings. Make sure you use ".align 2" before
# a line for a .space directive.


# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# STUDENTS MAY MODIFY CODE ABOVE
