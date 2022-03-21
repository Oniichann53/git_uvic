# This code assumes the use of the "Bitmap Display" tool.
#
# Tool settings must be:
#   Unit Width in Pixels: 32
#   Unit Height in Pixels: 32
#   Display Width in Pixels: 512
#   Display Height in Pixels: 512
#   Based Address for display: 0x10010000 (static data)
#
# In effect, this produces a bitmap display of 16x16 pixels.


	.include "bitmap-routines.asm"

	.data
TELL_TALE:
	.word 0x12345678 0x9abcdef0	# Helps us visually detect where our part starts in .data section
KEYBOARD_EVENT_PENDING:
	.word	0x0
KEYBOARD_EVENT:
	.word   0x0
BOX_ROW:
	.word	0x0
BOX_COLUMN:
	.word	0x0

	.eqv LETTER_a 97
	.eqv LETTER_d 100
	.eqv LETTER_w 119
	.eqv LETTER_s 115
    .eqv SPACE    32
	.eqv BOX_COLOUR 0x0099ff33
	
	.globl main
	
	.text	
main:
	lw $a0, BOX_ROW
	lw $a1, BOX_COLUMN
	addi $a2, $zero, BOX_COLOUR
	jal draw_bitmap_box
	la $s0, 0xffff0000	
	lb $s1, 0($s0)
	ori $s1, $s1, 0x02
	sb $s1, 0($s0)
	
check_for_event:
	la $s0, KEYBOARD_EVENT_PENDING
	lw $s1, 0($s0)
	
	beq $s1, $zero, check_for_event

key_process:
	lw $s3, 0($s0)
	beq $s3, LETTER_a, control_box_left
	beq $s3, LETTER_d, control_box_right
	beq $s3, LETTER_w, control_box_forward
	beq $s3, LETTER_s, control_box_backward
	beq $s3, SPACE, change_colour
	beq $zero, $zero, reset
	
control_box_left:
	jal reset_box
	addi $a1, $a1, -1
	sw $a1, BOX_COLUMN
	jal draw_bitmap_box
	beq $zero, $zero, reset
	
	
control_box_right:
	jal reset_box
	addi $a1, $a1, 1
	sw $a1, BOX_COLUMN
	jal draw_bitmap_box
	beq $zero, $zero, reset

control_box_forward:
	jal reset_box
	addi $a0, $a0, -1
	sw $a0, BOX_ROW
	jal draw_bitmap_box
	beq $zero, $zero, reset
	
control_box_backward:
	jal reset_box
	addi $a0, $a0, 1
	sw $a0, BOX_ROW
	jal draw_bitmap_box
	beq $zero, $zero, reset
	
change_colour:
	jal reset_box
	beq $a2, BOX_COLOUR, student_ID
	beq $a2, 0x00955869, default
student_ID:
	addi $a2, $zero, 0x00955869
	jal draw_bitmap_box
	beq $zero, $zero, reset

default:
	addi $a2, $zero, BOX_COLOUR
	jal draw_bitmap_box
	beq $zero, $zero, reset

	
reset_box:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a2, 4($sp)
	
	lw $a0, BOX_ROW
	lw $a1, BOX_COLUMN
	addi $a2, $zero, 0
	jal draw_bitmap_box
	lw $a0, BOX_ROW
	lw $a1, BOX_COLUMN
	
	lw $ra, 0($sp)
	lw $a2, 4($sp)
	addi $sp, $sp, 8
	
	jr $ra

reset:
	addi $s1, $zero, 0
	la $s0, KEYBOARD_EVENT_PENDING
	sw $s1, 0($s0)
	beq $zero, $zero, check_for_event
	
	# Should never, *ever* arrive at this point
	# in the code.	

	addi $v0, $zero, 10

.data
    .eqv BOX_COLOUR_BLACK 0x00000000
.text

	addi $v0, $zero, BOX_COLOUR_BLACK
	syscall



# Draws a 4x4 pixel box in the "Bitmap Display" tool
# $a0: row of box's upper-left corner
# $a1: column of box's upper-left corner
# $a2: colour of box

draw_bitmap_box:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	addi $s0, $zero, 0
	addi $s1, $zero, 0
main_loop:
	jal set_pixel
	addi $a0, $a0, 1
	addi $s0, $s0, 1
	bne $s0, 4, main_loop
	bne $s1, 3, next_col
	beq $zero, $zero, end

next_col:
	sub $a0, $a0, 4
	addi $s0, $zero, 0
	addi $a1, $a1, 1
	addi $s1, $s1, 1
	beq $zero, $zero, main_loop

end:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	addi $sp, $sp, 12
	jr $ra


	.kdata

	.ktext 0x80000180
#
# You can copy-and-paste some of your code from part (a)
# to provide elements of the interrupt handler.
#
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


.data

# Any additional .text area "variables" that you need can
# be added in this spot. The assembler will ensure that whatever
# directives appear here will be placed in memory following the
# data items at the top of this file.

.eqv BOX_COLOUR_WHITE 0x00FFFFFF
	
