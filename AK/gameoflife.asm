.data
	board: 		.space 400 # 10x10 board
	temp:		.space 400 # 10x10 to override board
	alive_char: .byte 'X'
	dead_char:  .byte '.'
	newline:    .asciiz "\n"

.text

j main

print_new_line:
	li $t7, 50   # liczba linii do wypisania
    li $t6, 0    # licznik
	new_line_loop:
    	beq $t1, $t7, exit_new_line_loop # je?li licznik r?wny liczbie linii, wyjd? z p?tli
    	la $a0, newline     # za?aduj adres znaku nowej linii do $a0
    	li $v0, 4           # ustaw kod operacji 4 (wypisz ?a?cuch znak?w)
    	syscall             # wywo?aj funkcj? systemow?
    	addi $t6, $t6, 1    # zwi?ksz licznik o 1
    	j new_line_loop     # powr?? do pocz?tku p?tli
    
    exit_new_line_loop:
        sw $ra, 0($sp)
    	addiu $sp, $sp, -4
    	jr $ra

wait:
    li $t8, 1000000  # Liczba iteracji
	wait_loop:
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	nop
    	addi $t8, $t8, -1  # Dekrementacja licznika iteracji
    	bnez $t8, wait_loop    # Powr?t do p?tli, je?li licznik nie jest r?wny zero
    	jr $ra

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
			add $t6, $t6, $t7

			blt $t6, 1, skip_vertical
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
	j set_alive
			
	set_alive:
		li $t8, 1
		sw $t8, temp($t0)
		jr $ra
	set_dead:
		li $t8, 0
		sw $t8, temp($t0)
	jr $ra
	

main:
	addi $s0, $zero, 0
	addi $s1, $zero, 1
	
	addi $t0, $zero, 0
		
	create_board:
		sw $s0, board($t0)
		addi $t0, $t0, 4
		
		blt $t0, 400, create_board
		
	li $t0, 0
	
	loop:
		li $t0, 0
		li $t1, 0 # current row
		row_check:
			li $t2, 0 # current column
			column_check:
				addi $t0, $t0, 4
				jal count_neighbors
				
				addi $t2, $t2, 1
				ble $t2, 10, column_check
		
			addi $t1, $t1, 1
			ble $t1, 10, row_check


		li $t0, 0
		li $t1, 0

		row_draw:
			li $v0, 11
			addi $t1, $t1, 1
			li $t2, 0
			column_draw:
				addi $t2, $t2, 1

				lw $t3, temp($t0)
				sw $t3, board($t0)

				print_alive:
				li $a0, 'X'

				print_dead:
				li $a0, '.'

				syscall
				addi $t0, $t0, 4
				ble $t2, 10, column_draw
			
			li $v0, 4
			la $a0, newline
			syscall
			ble $t1, 10, row_draw

		jal print_new_line
		jal wait
		j loop

				
