.data
	board: .space 400 # 10x10 board
	temp: .space 400 # 10x10 to override board
	alive_char: .ascii "X"
	dead_char: .ascii "."
	newline: .ascii "\n"
.text

count_neighbors:
	li $t5, 0 #neighbor count

	li $t3, -2 #row offset
	horizontal:
		addi $t3, $t3, 1
		li $t4, -2
		vertical:
			addi $t4, $t4, 1
			bnez $t3, check
			bnez $t4, check

			li $t8, 0 #checker
			addi $t8, $t1, $t3
			blt $t8, 0, vertical
			
			j vertical

			passed:

			



main:
	addi $s0, $zero, 0
	addi $s1, $zero, 1
	
	addi $t0, $zero, 0
		
	create_board:
		sw $s0, board($t0)
		addi $t0, $t0, 4
		
		blt $t0, 400, create_board
		
	li $t0, 0

	#$t0 - current cell
	#$t1 - current row
	#$t2 - current column
	#$t3 - current row offset
	#$t4 - current column offset
	
	loop:
		li $t1, 0 # current row
		row_check:
			li $t2, 0 # current column
			column_check:

			ble $t2, 40, column_check
		
		addi $t1, $t1, 1
		ble $t1, 400, row_check
						