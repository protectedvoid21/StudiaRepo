.data 
    arr: .space 12
    prompt: .asciiz "Add a number:"

.text
    addi $s0, $zero, 4
    addi $s1, $zero, 5
    addi $s2, $zero, 10

    addi $t0, $zero, 0
    sw $s0, arr($t0)
    addi $t0, $t0, 4
    sw $s1, arr($t0)
    addi $t0, $t0, 4
    sw $s2, arr($t0)

    addi $t0, $zero, 8
    lw $t6, arr($t0)

    li $v0, 1
    addi $a0, $t6, 0
    syscall
    