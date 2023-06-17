.data
	board: 		.space 400 # 10x10 board
	temp:		.space 400 # 10x10 to override board

.text

j main

count_neighbors:
	li $t5, 0 #neighbor count

	li $t3, -1 #row offset
	horizontal:
		li $t4, -1
		vertical:
			bnez $t3, check_if_outside
			bnez $t4, check_if_outside
			
			j skip_vertical

			check_if_outside:
			
			li $t6, 0
			add $t6, $t1, $t3
			bltz $t6, skip_vertical
			bge $t6, 10, skip_vertical
			
			li $t7, 0
			add $t7, $t2, $t4
			bltz $t7, skip_vertical
			bge $t7, 10, skip_vertical

			#actually check neighbor
			mul $t6, $t6, 40
			mul $t7, $t7, 4
			add $t6, $t6, $t7

			lw $t7, board($t6)
			blt $t7, 1, skip_vertical
			addi $t5, $t5, 1
												
			skip_vertical:
			addi $t4, $t4, 1
			ble $t4, 1, vertical

		addi $t3, $t3, 1
		ble $t3, 1, horizontal	
	
	#actually checking if board[x][y] is true - alive
	li $t6, 0
	lw $t6, board($t0)
	beqz $t6, check_if_dead

	check_if_alive:
	beq $t5, 2, set_alive
	beq $t5, 3, set_alive 
	j set_dead
	
	check_if_dead:
	beq $t5, 3, set_alive
	j set_dead
			
	set_alive:
		li $t8, 1
		sw $t8, temp($t0)
		jr $ra
	set_dead:
		li $t8, 0
		sw $t8, temp($t0)
	jr $ra
	

main:
	li $t0, 0
	create_board:
		sw $zero, board($t0)
		sw $zero, temp($t0)
		addi $t0, $t0, 4
		
		blt $t0, 400, create_board
		
	load_custom_alive:
		li $s0, 1
		li $t0, 204
		sw $s0, board($t0)
		li $t0, 208
		sw $s0, board($t0)
		li $t0, 212
		sw $s0, board($t0)
		li $t0, 160
		sw $s0, board($t0)
		li $t0, 164
		sw $s0, board($t0)
		li $t0, 168
		sw $s0, board($t0)
		li $t0, 116
		sw $s0, board($t0)
	
	loop:
		li $t0, 0
		li $t1, 0 # current row
		row_check:
			li $t2, 0 # current column
			column_check:
				jal count_neighbors
				
				addi $t0, $t0, 4
				addi $t2, $t2, 1
				blt $t2, 10, column_check
		
			addi $t1, $t1, 1
			blt $t1, 10, row_check


		li $v0, 11

		li $t0, 0		
		li $t1, 0
		row_draw:
			li $t2, 0
			column_draw:
				li $t3, 0
				lw $t3, temp($t0)
				sw $t3, board($t0)

				beqz $t3, print_dead

				print_alive:
				li $a0, 'X'
				j write_char

				print_dead:
				li $a0, '.'
				j write_char

				write_char:

				syscall
				addi $t0, $t0, 4
				addi $t2, $t2, 1
				blt $t2, 10, column_draw
			
			li $a0, 10
			syscall

			addi $t1, $t1, 1
			blt $t1, 10, row_draw

		li $v0, 11
		li $a0, 10
		syscall

		li $v0, 32
		li $a0, 1000
		syscall
		j loop