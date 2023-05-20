.data
    dividend dd 13

.text
4

_start:
    mov eax, dividend
    mov ebx, 4      
    xor edx, edx       

    div ebx       

    mov eax, edx   

    mov ebx, 1          
    mov ecx, eax   
    mov edx, 1
    mov eax, 4
    int 0x80

    mov eax, 1
    xor ebx, ebx
    int 0x80
