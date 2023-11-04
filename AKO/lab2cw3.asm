; Przyk�ad wywo�ywania funkcji MessageBoxA i MessageBoxW
.686
.model flat
extern _ExitProcess@4 : PROC
extern _MessageBoxA@16 : PROC
extern _MessageBoxW@16 : PROC
public _main
.data
tytul_Unicode dw 'Z', 'n', 'a', 'k', 'i', ' ', 'U', 'N','I','C', 'O', 'D', 'E', 'a', 0


tekst_Unicode dw 'Z', 'a', 'k', 'a','z'
dw 0D83Dh,0DEB3h, 10
dw 0D83DH, 0DEBBH
dw 'z', 'n', 'a', 'k', ' '
dw 't', 'o', 'a', 'l', 'e', 't', 'a', 0

.code
_main PROC
push 0; stala MB_OK
; adres obszaru zawieraj�cego tytu�
push OFFSET tytul_Unicode
; adres obszaru zawieraj�cego tekst
push OFFSET tekst_Unicode
push 0; NULL
call _MessageBoxW@16
push 0; kod powrotu programu
call _ExitProcess@4
_main ENDP
END