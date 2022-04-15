# Skeleton file provided to students in UVic CSC 230, Spring 2022 
# Original file copyright Mike Zastre, 2022

.include "a4support.asm"

.data

.eqv	MAX_ARRAY_SIZE 1024

.align 2
ARRAY_1:	.space MAX_ARRAY_SIZE
ARRAY_2:	.space MAX_ARRAY_SIZE
ARRAY_3:	.space MAX_ARRAY_SIZE
ARRAY_4:	.space MAX_ARRAY_SIZE
ARRAY_5:	.space MAX_ARRAY_SIZE
ARRAY_6:	.space MAX_ARRAY_SIZE
ARRAY_7:	.space MAX_ARRAY_SIZE
ARRAY_8:	.space MAX_ARRAY_SIZE

# STUDENTS MAY MODIFY CODE BELOW
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

FILENAME_1:	.asciiz "integers-200-42624.bin"
FILENAME_2:	.asciiz "integers-200-93238.bin"

# ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
# STUDENTS MAY MODIFY CODE ABOVE



.globl main
.text 
main:

# STUDENTS MAY MODIFY CODE BELOW
# vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

	la $a0, FILENAME_1
	la $a1, ARRAY_1
	jal read_file_of_ints
	add $s1, $zero, $v0
	
	la $a0, FILENAME_2
	la $a1, ARRAY_2
	jal read_file_of_ints
	add $s2, $zero, $v0
	
	
	# WRITE YOUR SOLUTION TO THE PART E PROBLEM
	# HERE...
	la $a0, ARRAY_1
	la $a1, ARRAY_3
	add $a2, $zero, $s1
	jal accumulate_max
		
	la $a0, ARRAY_2
	la $a1, ARRAY_4
	add $a2, $zero, $s1
	jal accumulate_max
	
	la $a0, ARRAY_3
	la $a1, ARRAY_5
	add $a2, $zero, $s1
	jal reverse_array
	
	la $a0, ARRAY_4
	la $a1, ARRAY_5
	la $a2, ARRAY_6
	add $a3, $zero, $s1
	jal pairwise_max

	la $a0, ARRAY_6
	la $a1, ARRAY_7
	add $a2, $zero, $s1
	jal accumulate_sum

	la $a0, ARRAY_7
	mul $t0, $s1, 4
	add $a0, $a0, $t0
	lw $t1, -4($a0)
	
	li $v0, 1
	addi $a0, $t1, 0
	syscall
	
	# Get outta here.		
	add $v0, $zero, 10
	syscall	
	

	
# COPY YOUR PROCEDURES FROM PARTS A, B, C, and D BELOW
# THIS POINT.
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
