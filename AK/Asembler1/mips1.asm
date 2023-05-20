section .data
    dividend dd 13   ; Liczba do podzielenia

section .text
    global _start

_start:
    mov eax, dividend    ; Przeniesienie liczby do rejestru EAX
    mov ebx, 4           ; Przeniesienie dzielnika do rejestru EBX
    xor edx, edx         ; Wyczyœæ rejestr EDX (rejestr reszty)

    div ebx              ; Podziel EAX przez EBX

    mov eax, edx         ; Przenieœ resztê z dzielenia do rejestru EAX

    ; Teraz mo¿esz u¿yæ wartoœci w rejestrze EAX, aby wykonaæ odpowiednie operacje

    ; W tym przypadku, aby wyœwietliæ resztê, skorzystamy z funkcji systemowej

    mov ebx, 1           ; Ustawienie deskryptora pliku na stdout
    mov ecx, eax         ; Przeniesienie reszty do rejestru ECX
    mov edx, 1           ; Liczba bajtów do wyœwietlenia
    mov eax, 4           ; Numer funkcji systemowej dla sys_write
    int 0x80             ; Wywo³anie funkcji systemowej

    ; Zakoñczenie programu

    mov eax, 1           ; Numer funkcji systemowej dla sys_exit
    xor ebx, ebx         ; Kod zakoñczenia (0)
    int 0x80             ; Wywo³anie funkcji systemowej sys_exit
