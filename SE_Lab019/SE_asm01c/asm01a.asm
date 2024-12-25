.586P                          
.MODEL FLAT, STDCALL                  
.CODE                          ; сегмент кода


getmin PROC arr:DWORD, len:DWORD 
    mov ecx, len     ; Количество элементов в массиве
    mov esi, arr    ; Адрес первого элемента массива
    mov eax, [esi] ; Инициализируем eax первым элементом массива eax - Для минимума
    ; Начинаем цикл по массиву
        loop_count:
            mov edx, [esi] ; Загружаем текущий элемент массива в edx
            cmp edx, eax    ; Сравниваем текущий элемент с текущим минимумом (eax)
            jl update_min   ; Если текущий элемент меньше текущего минимума, обновляем минимум
            jmp next
            update_min:
            mov eax, edx    ; Обновляем минимум
            next:
            add esi, 4          ; Переходим к следующему элементу массива (4 байта на DWORD)
        loop loop_count ; Переходим к следующему элементу массива и продолжаем цикл
 
        ; Результат (минимальное значение) возвращаем в eax
        ret 8
getmin ENDP

getmax PROC arr:DWORD, len:DWORD 
    mov ecx, len     ; Количество элементов в массиве
    mov esi, arr    ; Адрес первого элемента массива
    mov eax, [esi] ; Инициализируем eax первым элементом массива eax - Для минимума
    ; Начинаем цикл по массиву
        loop_count:
            mov edx, [esi] ; Загружаем текущий элемент массива в edx
            cmp eax, edx    ; Сравниваем текущий элемент с текущим минимумом (eax)
            jl update_min   ; Если текущий элемент меньше текущего минимума, обновляем минимум
            jmp next
            update_min:
            mov eax, edx    ; Обновляем минимум
            next:
            add esi, 4          ; Переходим к следующему элементу массива (4 байта на DWORD)
        loop loop_count ; Переходим к следующему элементу массива и продолжаем цикл
 
        ; Результат (минимальное значение) возвращаем в eax
        ret 8
getmax ENDP

int_to_char PROC pstr : dword, intfield : sdword
  mov edi, pstr ; копирует из pstr в edi
  mov esi, 0 ; количество символов в результате 
  mov eax, intfield ; число -> в eax
  cdq ; знак числа распространяется с eax на edx
  mov ebx, 10 ; основание системы счисления (10) -> ebx
  idiv ebx ; eax = eax/ebx, остаток в edx (деление целых со знаком)
  test eax, 80000000h ; тестируем знаковый бит
  jz plus ; если положительное число - на plus
  neg eax ; иначе мнеяем знак eax
  neg edx ; edx = -edx
  mov cl, '-' ; первый символ результата '-'
  mov[edi], cl ; первый символ результата '-'
  inc edi ; ++edi
  plus : ; цикл разложения по степеням 10
  push dx ; остаток -> стек
  inc esi ; ++esi
  test eax, eax ; eax == ?
  jz fin ; если да, то на fin
  cdq ; знак распространяется с eax на edx 
  idiv ebx ; eax = eax/ebx, остаток в edx
  jmp plus ; безусловный переход на plus
  fin : ; в ecx кол-во не 0-вых остатков = кол-ву символов результата
  mov ecx, esi
  write : ; цикл записи результата
  pop bx ; остаток из стека -> bx
  add bl, '0' ; сформировали символ в bl
  mov[edi], bl ; bl -> в результат
  inc edi ; edi++
  loop write ; если (--ecx)>0 переход на write
  ret
int_to_char ENDP

END                    