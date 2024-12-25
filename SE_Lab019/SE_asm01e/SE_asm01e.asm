.586P                          
.MODEL FLAT, STDCALL                  
includelib kernel32.lib
includelib SE_asm01d.lib
includelib libucrt.lib

ExitProcess PROTO :DWORD                ; прототип функции для завершения процесса Windows
GetStdHandle PROTO : DWORD
WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD
EXTERN getmin: PROC
EXTERN getmax: PROC
int_to_char PROTO : DWORD, : SDWORD

.STACK 4096                        ; выделение стека

.CONST                          ; сегмент констант

.DATA                          ; сегмент данных
consolehandle dd 0h
myArray DWORD -10, 5, 88, 2, 7, 1, 6, 3, 9, 4 ; Пример массива  
MyStr SDWORD 64 DUP(0) ; Буфер для строкового представления результата

.CODE                          ; сегмент кода
int_to_char PROC pstr : dword, intfield : sdword
  mov edi, pstr            ; копирует из pstr в edi
  mov esi, 0               ; количество символов в результате 
  mov eax, intfield        ; число -> в eax
  cdq                      ; знак числа распространяется с eax на edx
  mov ebx, 10              ; основание системы счисления (10) -> ebx
  idiv ebx                 ; eax = eax/ebx, остаток в edx (деление целых со знаком)
  test eax, 80000000h      ; тестируем знаковый бит
  jz plus                  ; если положительное число - на plus
  neg eax                  ; иначе мнеяем знак eax
  neg edx                  ; edx = -edx
  mov cl, '-'              ; первый символ результата '-'
  mov[edi], cl             ; первый символ результата '-'
  inc edi                  ; ++edi
  plus :                   ; цикл разложения по степеням 10
  push dx                  ; остаток -> стек
  inc esi                  ; ++esi
  test eax, eax            ; eax == ?
  jz fin                   ; если да, то на fin
  cdq                      ; знак распространяется с eax на edx 
  idiv ebx                 ; eax = eax/ebx, остаток в edx
  jmp plus                 ; безусловный переход на plus
  fin :                    ; в ecx кол-во не 0-вых остатков = кол-ву символов результата
  mov ecx, esi
  write :                  ; цикл записи результата
  pop bx                   ; остаток из стека -> bx
  add bl, '0'              ; сформировали символ в bl
  mov[edi], bl             ; bl -> в результат
  inc edi                  ; edi++
  loop write               ; если (--ecx)>0 переход на write
  ret
int_to_char ENDP


main PROC
    ; Вызываем getmin
    push 10               ; Количество элементов в массиве
    push OFFSET myArray   ; Адрес первого элемента массива
    call getmin
    mov ebx, eax
    push 10               ; Количество элементов в массиве
    push OFFSET myArray   ; Адрес первого элемента массива
    call getmax
    add eax, ebx ; Суммируем результаты getmin и getmax

    push eax
    push OFFSET MyStr
    call int_to_char
    push -11
     call GetStdHandle
     mov consolehandle, eax
    push 0
    push 0
    push sizeof MyStr
    push offset MyStr
    push consolehandle
    call WriteConsoleA

    push 0
    call ExitProcess
main ENDP

end main                       