#
# YOU ARE NOT PERMITTED TO MODIFY **ANY** CODE IN THIS ASSEMBLY FILE
#

# DID YOU READ THAT? I SAID:
#
#  YOU ARE ABSOTIVELY, POSOLUTELY NOT PERMITTED TO MODIFY ANY PART
#  OF THIS FILE!
#	
		
	# Best to keep these next few lines all together
	#
	# Settings for "Bitmap Display" given the following .eqv directives...
	#
	# Unit width in pixels: 32; unit height in pixels: 32
	# Display width in pixels: 512; display height in pixels: 512
	# Base address for display: 0x10010000
	
	.eqv WIDTH_IN_PIXELS 16
	.eqv WIDTH_IN_SHIFTS 4 
	.eqv HEIGHT_IN_PIXELS 16
	.eqv HEIGHT_IN_SHIFTS 4
	.eqv PIXEL_WIDTH 1
	.eqv PIXEL_WIDTH_IN_SHIFTS 2
	.eqv PIXEL_HEIGHT 1
	.eqv PIXEL_HEIGHT_IN_SHIFTS 0
	.eqv FRAME_BUFFER_SIZE 1024  # 16 * 16 * 4 (that is, one word per pixel)
	
		
	.data 0x10014000	# room for activation frames in this file
SET_PIXEL_SAVES:
	.space 16
RENDER_FRAME_SAVES:
	.space 12
	
	.data 0x10010000	# All pixel operations go directly to area mapped by Bitmap tool
FRAME_BUFFER:
	.space FRAME_BUFFER_SIZE
	

	.data
	
	.text
	# Assumption here is that thie file is "included" into some other file
	# and we want control to begin in that other file's own code. We
	# assume, therefore, that the other file begins the program
	# at "main".
	j	main

	# Should never, ever, **ever** return to this spoint in the code.
	

						
# $a0: row (counting from the top as row 0)
# $a1: column (counting from the left as column 0)
# $a2: colour (24-bit RGB value)
#
# Note that this code does *not* use the stack to save and
# restore register. This is pretty much a consequence of
# paranoia -- that is, by separating the following code
# from any other routines that use the stack, we isolate
# the following code from any bugs in stack-maintenance
# operations.
#
set_pixel:
	la $t1, SET_PIXEL_SAVES
	sw $ra, 0($t1)
	sw $s0, 4($t1)
	sw $s1, 8($t1)
	sw $s2, 12($t1)
	
	# sanity check: 0 <= row < HEIGHT_IN_PIXELS? 0 <= col < WIDTH_IN_PIXELS?
	bltz $a0, set_pixel_exit
	bge $a0, HEIGHT_IN_PIXELS, set_pixel_exit
	bltz $a1, set_pixel_exit
	bge $a1, WIDTH_IN_PIXELS, set_pixel_exit
	
	# Need byte address of row
	add $s0, $zero, $a0
	sll $s0, $s0, PIXEL_WIDTH_IN_SHIFTS
	sll $s0, $s0, PIXEL_HEIGHT_IN_SHIFTS
	sll $s0, $s0, WIDTH_IN_SHIFTS
	
	# Now need offset for column in that row
	addi $s1, $zero, 1
	sll $s1, $s1, PIXEL_WIDTH_IN_SHIFTS
	sll $s1, $s1, PIXEL_HEIGHT_IN_SHIFTS
	mult $s1, $a1
	mflo $s1
	
	# Finally, compute the address of the first byte
	# in that pixel.
	la $s2, FRAME_BUFFER
	add $s2, $s2, $s0
	add $s2, $s2, $s1
	
	addi $s0, $zero, PIXEL_HEIGHT
set_pixel_row:
	addi $s1, $zero, PIXEL_WIDTH
set_pixel_column:
	sw $a2, 0($s2)
	addi $s2, $s2, 4
	addi $s1, $s1, -1
	bne $s1, $zero, set_pixel_column
	
	addi $s1, $zero, 1
	sll $s1, $s1, PIXEL_WIDTH_IN_SHIFTS
	sll $s1, $s1, WIDTH_IN_SHIFTS
	add $s2, $s2, $s1
	add $t0, $zero, PIXEL_WIDTH		# wee tweak
	sub $s2, $s2, $t0
	
	addi $s0, $s0, -1
	bne $s0, $zero, set_pixel_row
	
set_pixel_exit:
	la $t1, SET_PIXEL_SAVES
	lw $ra, 0($t1)
	lw $s0, 4($t1)
	lw $s1, 8($t1)
	lw $s2, 12($t1)
	jr $ra
