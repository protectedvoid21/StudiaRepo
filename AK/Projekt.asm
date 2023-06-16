.data
	board: 		.space 400 # 10x10 board
	temp:		.space 400 # 10x10 to override board
	alive_char: .ascii "X"
	dead_char:  .ascii "."
	newline:    .ascii "\n"

.text

print_new_line:
	li $t0, 50   # liczba linii do wypisania
    li $t1, 0    # licznik
	new_line_loop:
    	beq $t1, $t0, exit_new_line_loop # jeœli licznik równy liczbie linii, wyjdŸ z pêtli
    	la $a0, newline     # za³aduj adres znaku nowej linii do $a0
    	li $v0, 4           # ustaw kod operacji 4 (wypisz ³añcuch znaków)
    	syscall             # wywo³aj funkcjê systemow¹
    	addi $t1, $t1, 1    # zwiêksz licznik o 1
    	j new_line_loop     # powróæ do pocz¹tku pêtli
    
    exit_new_line_loop:
        sw $ra, 0($sp)
    	addiu $sp, $sp, -4
    	jr $ra

wait:
    li $t0, 100000000  # Liczba iteracji
	wait_loop:
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	nop               # OpóŸnienie
    	addi $t0, $t0, -1  # Dekrementacja licznika iteracji
    	bnez $t0, wait_loop    # Powrót do pêtli, jeœli licznik nie jest równy zero
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
			
			li $t6, 0
			add $t6, $t2, $t4
			bltz $t6, skip_vertical
			bge $t6, 10, skip_vertical
												
			skip_vertical:
			addi $t4, $t4, 1
			blt $t8, 0, vertical

		addi $t3, $t3, 1
	
	
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

	#$t0 - current cell
	#$t1 - current row
	#$t2 - current column
	#$t3 - current row offset
	#$t4 - current column offset
	
	loop:
		li $t0, 0
		li $t1, 0 # current row
		row_check:
			li $t2, 0 # current column
			column_check:
				addi $t0, $t0, 4
				jal count_neighbors
				
				
				
				addi $t2, $t2, 1
				blt $t2, 10, column_check
		
			addi $t1, $t1, 1
			blt $t1, 10, row_check
