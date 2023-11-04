;wczytywanie i wy�wietlanie tekstu wielkimi literami
; (inne znaki si� nie zmieniaj�)
.686
.model flat
extern _ExitProcess@4 : PROC
extern __write : PROC ; (dwa znaki podkre�lenia)
extern __read : PROC ; (dwa znaki podkre�lenia)
public _main
.data
tekst_pocz db 10, 'Prosz',0A9H,' napisa',86H,' jaki',98H,' tekst '
db 'i nacisn',0A5H,86H,' Enter', 10
koniec_t db ?
magazyn db 80 dup (?)
polish_chars_small db 0A5H, 086H, 0A9H, 088H, 0E4H, 0A2H, 098H, 0ABH, 0BEH 
polish_chars_huge db 0A4H, 08FH, 0A8H, 9DH, 0E3H, 0E0H, 97H, 8DH, 0BDH  

nowa_linia db 10
liczba_znakow dd ?
.code
_main PROC
; wy�wietlenie tekstu informacyjnego
; liczba znak�w tekstu
mov ecx,(OFFSET koniec_t) - (OFFSET tekst_pocz)
push ecx
push OFFSET tekst_pocz ; adres tekstu
push 1 ; nr urz�dzenia (tu: ekran - nr 1)
call __write ; wy�wietlenie tekstu pocz�tkowego
add esp, 12 ; usuniecie parametr�w ze stosu
 czytanie wiersza z klawiatury
push 80 ; maksymalna liczba znak�w
push OFFSET magazyn
push 0 ; nr urz�dzenia (tu: klawiatura - nr 0)
call __read ; czytanie znak�w z klawiatury
add esp, 12 ; usuniecie parametr�w ze stosu
; kody ASCII napisanego tekstu zosta�y wprowadzone
; do obszaru 'magazyn'
; funkcja read wpisuje do rejestru EAX liczb�
; wprowadzonych znak�w
mov liczba_znakow, eax
; rejestr ECX pe�ni rol� licznika obieg�w p�tli
mov ecx, eax
mov ebx, 0 ; indeks pocz�tkowy



ptl:
cmp eax, 0
jbe koniec
mov dl, magazyn[ebx] ; pobranie kolejnego znaku
cmp dl, 7FH
ja tak_musi_byc
cmp dl, 'a'
jb dalej ; skok, gdy znak nie wymaga zamiany
cmp dl, 'z'
ja dalej ; skok, gdy znak nie wymaga zamiany
sub dl, 20H ; zamiana na wielkie litery
; odes�anie znaku do pami�ci
mov magazyn[ebx], dl
dalej:
inc ebx ; inkrementacja indeksu
dec ecx
dec eax
cmp ecx, 0
ja ptl

tak_musi_byc: 
cmp eax, 1
jbe koniec
mov edi, 0
mov ecx, 9
nested_ptl:
	cmp polish_chars_small[edi], dl
	je switch_polish_to_upper
	inc edi ;
loop nested_ptl

dec eax
mov ecx, eax
inc ebx ; inkrementacja indeksu
cmp eax, 0
ja ptl


switch_polish_to_upper:
cmp eax, 1
jbe koniec
mov dl, polish_chars_huge[edi]
mov magazyn[ebx], dl
dec eax
mov ecx, eax
inc ebx ; inkrementacja indeksu
cmp eax, 1
ja ptl


koniec:
; wy�wietlenie przekszta�conego tekstu
push liczba_znakow
push OFFSET magazyn
push 1
call __write ; wy�wietlenie przekszta�conego tekstu
add esp, 12 ; usuniecie parametr�w ze stosu
push 0
call _ExitProcess@4 ; zako�czenie programu
_main ENDP
END