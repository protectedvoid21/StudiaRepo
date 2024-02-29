section .data
    dividend dd 13   ; Liczba do podzielenia

section .text
    global _start

_start:
    mov eax, dividend    ; Przeniesienie liczby do rejestru EAX
    mov ebx, 4           ; Przeniesienie dzielnika do rejestru EBX
    xor edx, edx         ; Wyczy�� rejestr EDX (rejestr reszty)

    div ebx              ; Podziel EAX przez EBX

    mov eax, edx         ; Przenie� reszt� z dzielenia do rejestru EAX

    ; Teraz mo�esz u�y� warto�ci w rejestrze EAX, aby wykona� odpowiednie operacje

    ; W tym przypadku, aby wy�wietli� reszt�, skorzystamy z funkcji systemowej

    mov ebx, 1           ; Ustawienie deskryptora pliku na stdout
    mov ecx, eax         ; Przeniesienie reszty do rejestru ECX
    mov edx, 1           ; Liczba bajt�w do wy�wietlenia
    mov eax, 4           ; Numer funkcji systemowej dla sys_write
    int 0x80             ; Wywo�anie funkcji systemowej

    ; Zako�czenie programu

    mov eax, 1           ; Numer funkcji systemowej dla sys_exit
    xor ebx, ebx         ; Kod zako�czenia (0)
    int 0x80             ; Wywo�anie funkcji systemowej sys_exit
