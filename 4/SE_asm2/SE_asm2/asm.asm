.586P
.MODEL FLAT, STDCALL
includelib kernel32.lib

ExitProcess PROTO : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD

.STACK 4096

.CONST

.DATA

OK			EQU	0
TEXT_MESSAGE		DB "SE_Asm04", 0
HW			DD ?

FILECHAR DD 'f', 'f', 'f', 'j', 'f', '5'
CHARSTR DB "char:    ", 0

FILEBOOL DD '0'
BOOLSTR DB "bool:     ", 0

.CODE

main PROC



mov eax, FILECHAR 
mov CHARSTR +8, al


mov eax, FILECHAR  + type FILECHAR
mov CHARSTR +9, al


mov eax, FILECHAR  + type FILECHAR + type FILECHAR
mov CHARSTR +10, al


mov eax, FILECHAR  + type FILECHAR + type FILECHAR + type FILECHAR
mov CHARSTR +11, al


mov eax, FILECHAR  + type FILECHAR + type FILECHAR + type FILECHAR + type FILECHAR
mov CHARSTR +12, al


mov eax, FILECHAR  + type FILECHAR + type FILECHAR + type FILECHAR + type FILECHAR + type FILECHAR
mov CHARSTR +13, al
invoke MessageBoxA, 0, offset CHARSTR, ADDR TEXT_MESSAGE, OK


mov eax, FILEBOOL 
push - 1
call ExitProcess
main ENDP
end main
