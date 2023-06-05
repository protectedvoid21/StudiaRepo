.data
    prompt: .asciiz "Enter a number: "

.text
    li $v0, 4
    la $a0, prompt
    syscall

    li $v0, 5
    syscall
    
    move $t0, $v0	
    
    li $t1, 0
    li $t2, 0
    
    loop:
    	mul $t3, $t0, $t0
    	
		add $t2, $t2, $t3
		add $t1, $t1, $t0
		
		addi $t0, $t0, -1
		bgez $t0, loop
		
	mul $t1, $t1, $t1
	sub $t1, $t1, $t2
	
	li $v0, 1
	move $a0, $t1
	syscall
	
	
	
	
	