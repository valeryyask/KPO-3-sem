.586P                          
.MODEL FLAT, STDCALL                  
includelib kernel32.lib

ExitProcess PROTO :DWORD                                     ; прототип функции для завершения процесса Windows
MessageBoxA PROTO :DWORD, :DWORD, :DWORD, :DWORD             ; прототип API-функции MessageBoxA

.STACK 4096                                                  ; выделение стека

.CONST                                                       ; сегмент констант

.DATA                                                        ; сегмент данных
myArray DWORD 1, 5, 8, 2, 7, 1, 6, 3, 9, 4                  ; Пример массива                        

.CODE                                                        ; сегмент кода


getmin PROC
    mov esi, [esp + 4]                                       ; получаем arr (адрес массива)
    mov ecx, [esp + 8]                                       ; получаем len (длину массива)
    mov eax, esi                                             ; Инициализируем eax первым элементом массива eax - Для минимума
                                                             ; Начинаем цикл по массиву
        loop_count:
            mov edx, [esi]                                   ; Загружаем текущий элемент массива в edx
            cmp edx, eax                                     ; Сравниваем текущий элемент с текущим минимумом (eax)
            jl update_min                                    ; Если текущий элемент меньше текущего минимума, обновляем минимум
            jmp next
            update_min:
            mov eax, edx                                     ; Обновляем минимум
            next:
            add esi, 4                                       ; Переходим к следующему элементу массива (4 байта на DWORD)
        loop loop_count                                      ; Переходим к следующему элементу массива и продолжаем цикл
 
                                                             ; Результат (минимальное значение) возвращаем в eax
        ret 8
getmin ENDP

main PROC
                                                             ; Вызываем getmin
    push 10                                                  ; Количество элементов в массиве
    push OFFSET myArray                                      ; Адрес первого элемента массива
    call getmin
                                                             ; Результат возвращается в eax
    push 0
    call ExitProcess

main ENDP

end main                       