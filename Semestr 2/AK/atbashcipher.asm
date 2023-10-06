.text
.globl atbash_cipher
atbash_cipher:
    move $t4, $a1   # output pointer
    li $t5, 0       # number of letters in group
    li $t6, ' '     # space for convenient output
    li $t7, 'z'     # to subtract from to cipher
    
    start:
        lb $t0, 0($a0)
        add $a0, $a0, 1
        beq $t0, 0, end
        # $t1 = is_upper($t0)
        sge $t1, $t0, 'A'
        sle $t2, $t0, 'Z'
        and $t1, $t1, $t2
        # $t2 = is_lower($t0)
        sge $t2, $t0, 'a'
        sle $t3, $t0, 'z'
        and $t2, $t2, $t3
        # $t1 = is_alpha($t0)
        or $t1, $t1, $t2
        # Ignore non-alphabetic characters
        beq $t1, 0, start
        # $t0 is index for ith letter
        sub $t0, $t0, 'A'
        mul $t2, $t2, 32
        sub $t0, $t0, $t2
        # $t0 is ciphered letter
        sub $t0, $t7, $t0
        # write ciphered letter
        sb $t0, 0($t4)
        add $t4, $t4, 1
        # increment number of letters in group
        add $t5, $t5, 1
        rem $t5, $t5, 5
        # Add space after group of five
        bne $t5, 0, start
        sb $t6, 0($t4)
        add $t4, $t4, 1
        j start
    end:
    # Remove space from end if present
    bne $t5, 0, return
    beq $t4, $a1, return
    sb $zero, -1($t4)
    
    return:
        jr $ra
