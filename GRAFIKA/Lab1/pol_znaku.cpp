/******************************************************************
 Grafika komputerowa, ?rodowisko MS Windows - program  przyk?adowy
 *****************************************************************/

#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <math.h>
using namespace Gdiplus;


//deklaracja funkcji obslugi okna
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
POINT p;
FLOAT rotation = 40.1321;

POINT roadSignPosition{ 500, 500 }; // Pocz�tkowa pozycja znaku "droga jednokierunkowa"
bool isDragging = false; // Flaga wskazuj�ca, czy trwa przeci�ganie znaku
int radians_cout = 0;
// Pozwala na przesuwanie znaku "droga jednokierunkowa" do nowej pozycji
void MoveRoadSign(HWND hwnd, int x, int y) {
	
	roadSignPosition.x = x;
	roadSignPosition.y = y;
	InvalidateRect(hwnd, NULL, TRUE); // Od�wie�enie obszaru okna
}




void RotateElement(HDC hdc, int centerX, int centerY, FLOAT angleDegrees)
{
	// Convert angle from degrees to radians
	FLOAT angleRadians = angleDegrees * 3.141592653589793;
	angleRadians = angleRadians/180;

	//XFORM scaleForm;
	//scaleForm.eM11 = (float)scale;
	//scaleForm.eM22 = (float)scale;

	// Create a transformation matrix for rotation
	XFORM rotateForm{};
	rotateForm.eM11 = cos(angleRadians);  // Cosine of the angle
	rotateForm.eM12 = -sin(angleRadians); // Sine of the angle (negative due to coordinate system)
	rotateForm.eM21 = sin(angleRadians);  // Sine of the angle
	rotateForm.eM22 = cos(angleRadians);   // Cosine of the angle
	rotateForm.eDx = centerX * 0.1;
	rotateForm.eDy = centerY * 0.1;


	// Set the transformation matrix to the device context
	//SetGraphicsMode(hdc, GM_ADVANCED);

	ModifyWorldTransform(hdc, &rotateForm, MWT_LEFTMULTIPLY);
	//SetWorldTransform(hdc, &rotateForm);



}



PAINTSTRUCT paint;
HDC kontekst;






//funkcja Main - dla Windows
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG meldunek;		  //innymi slowy "komunikat"
	WNDCLASS nasza_klasa; //klasa g??wnego okna aplikacji
	HWND okno;
	static char nazwa_klasy[] = "Podstawowa";

	GdiplusStartupInput gdiplusParametry;// parametry GDI+; domy?lny konstruktor wype?nia struktur? odpowiednimi warto?ciami
	ULONG_PTR	gdiplusToken;			// tzw. token GDI+; warto?? uzyskiwana przy inicjowaniu i przekazywana do funkcji GdiplusShutdown

	// Inicjujemy GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusParametry, NULL);

	//Definiujemy klase g??wnego okna aplikacji
	//Okreslamy tu wlasciwosci okna, szczegoly wygladu oraz
	//adres funkcji przetwarzajacej komunikaty
	nasza_klasa.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	nasza_klasa.lpfnWndProc = WndProc; //adres funkcji realizuj?cej przetwarzanie meldunk?w 
	nasza_klasa.cbClsExtra = 0;
	nasza_klasa.cbWndExtra = 0;
	nasza_klasa.hInstance = hInstance; //identyfikator procesu przekazany przez MS Windows podczas uruchamiania programu
	nasza_klasa.hIcon = 0;
	nasza_klasa.hCursor = LoadCursor(0, IDC_ARROW);
	nasza_klasa.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	nasza_klasa.lpszMenuName = "Menu";
	nasza_klasa.lpszClassName = nazwa_klasy;

	//teraz rejestrujemy klas? okna g??wnego
	RegisterClass(&nasza_klasa);

	/*tworzymy okno g??wne
	okno b?dzie mia?o zmienne rozmiary, listw? z tytu?em, menu systemowym
	i przyciskami do zwijania do ikony i rozwijania na ca?y ekran, po utworzeniu
	b?dzie widoczne na ekranie */
	okno = CreateWindow(nazwa_klasy, "Grafika komputerowa", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);


	/* wyb?r rozmiaru i usytuowania okna pozostawiamy systemowi MS Windows */
	ShowWindow(okno, nCmdShow);

	//odswiezamy zawartosc okna
	UpdateWindow(okno);

	// G??WNA P?TLA PROGRAMU
	while (GetMessage(&meldunek, NULL, 0, 0))
		/* pobranie komunikatu z kolejki; funkcja GetMessage zwraca FALSE tylko dla
		komunikatu WM_QUIT; dla wszystkich pozosta?ych komunikat?w zwraca warto?? TRUE */
	{
		TranslateMessage(&meldunek); // wst?pna obr?bka komunikatu
		DispatchMessage(&meldunek);  // przekazanie komunikatu w?a?ciwemu adresatowi (czyli funkcji obslugujacej odpowiednie okno)
	}

	GdiplusShutdown(gdiplusToken);

	return (int)meldunek.wParam;
}

/********************************************************************
FUNKCJA OKNA realizujaca przetwarzanie meldunk?w kierowanych do okna aplikacji*/
LRESULT CALLBACK WndProc(HWND okno, UINT kod_meldunku, WPARAM wParam, LPARAM lParam)
{
	HMENU mPlik, mInfo, mGlowne;

	/* PONI?SZA INSTRUKCJA DEFINIUJE REAKCJE APLIKACJI NA POSZCZEG?LNE MELDUNKI */
	switch (kod_meldunku)
	{
	case WM_CREATE:  //meldunek wysy?any w momencie tworzenia okna
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Zapiszcz...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 200, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR)mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR)mInfo, "&Informacja");
		SetMenu(okno, mGlowne);
		DrawMenuBar(okno);

	case WM_COMMAND: //reakcje na wyb?r opcji z menu
		switch (wParam)
		{
		case 100: if (MessageBox(okno, "Zapiszcze??", "Pisk", MB_YESNO) == IDYES)
			MessageBeep(0);
			break;
		case 101: DestroyWindow(okno); //wysylamy meldunek WM_DESTROY
			break;
		case 200: MessageBox(okno, "Imi? i nazwisko:\nNumer indeksu: ", "Autor", MB_OK);
		}
		return 0;


	case WM_LBUTTONUP:
	{
		isDragging = false; // Zako�czenie przeci�gania
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		isDragging = false;
		// Sprawd�, czy klikni�cie myszk� jest w obszarze znaku "droga jednokierunkowa"
		if (x >= roadSignPosition.x - 80 && x <= roadSignPosition.x + 80 && y >= roadSignPosition.y - 65 && y <= roadSignPosition.y + 120) {

			isDragging = true; // Rozpocz�cie przeci�gania
		}
		return 0;
	}

	case WM_MOUSEMOVE:
	{
		if (isDragging) {
			GetCursorPos(&p);
			ScreenToClient(okno, &p);
			int x = p.x;
			int y = p.y;
			std::cout << x << " " << y;
			MoveRoadSign(okno, x, y);
		}
		return 0;

	}
	case WM_RBUTTONUP:
	{
		/*	for (int i = 0; i < 90; i++) {

				Sleep(1000);
			}*/

		radians_cout += 15;
		InvalidateRect(okno, NULL, TRUE);
		return 0;
	}


	case WM_PAINT:
	{


		kontekst = BeginPaint(okno, &paint);

		
		///SetGraphicsMode(kontekst, GM_ADVANCED);

		/// RotateElement(kontekst,okno, roadSignPosition.x, roadSignPosition.y, radians_cout, 0.9);

		// Now you can draw the road sign
		HPEN pioro = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		HPEN pioro2 = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		
		SelectObject(kontekst,pioro);
		RotateElement(kontekst, roadSignPosition.x, roadSignPosition.y - 10, rotation);
		RoundRect(kontekst, roadSignPosition.x - 85, roadSignPosition.y - 65, roadSignPosition.x + 85, roadSignPosition.y + 120, 20, 20);
		SetDCBrushColor(kontekst, RGB(0, 0, 255));
		SelectObject(kontekst, GetStockObject(DC_BRUSH));
		RoundRect(kontekst, roadSignPosition.x - 75, roadSignPosition.y - 55, roadSignPosition.x + 75, roadSignPosition.y + 110, 20, 20);

		POINT points[3] = { { roadSignPosition.x - 25, roadSignPosition.y + 25}, {roadSignPosition.x, roadSignPosition.y - 25}, { roadSignPosition.x + 25, roadSignPosition.y + 25} };
		SelectObject(kontekst, pioro2);
		SetDCBrushColor(kontekst, RGB(255, 255, 255));
		SelectObject(kontekst, GetStockObject(DC_BRUSH));
		Polygon(kontekst, points, 3);
		
		//SelectObject(kontekst, CreatePen(PS_SOLID, 1, RGB(255, 0, 0))); hitbox znaku
		//Rectangle(kontekst, roadSignPosition.x-80, roadSignPosition.y-65, roadSignPosition.x+80, roadSignPosition.y+120); 




		//DeleteObject(pioro);

		// utworzenie obiektu umo?liwiaj?cego rysowanie przy u?yciu GDI+
		// (od tego momentu nie mo?na u?ywa? funkcji GDI
		Graphics grafika(kontekst);



		// grafika.ScaleTransform(1.75f, 0.5f);

		// MIEJSCE NA KOD GDI+


		// utworzenie czcionki i wypisanie tekstu na ekranie
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
		PointF      pointF(100.0f, 400.0f);


		// grafika.DrawString(L"To jest tekst napisany za pomoc? GDI+.", -1, &font, pointF, &solidBrush);

		EndPaint(okno, &paint);

		return 0;

	}

	case WM_DESTROY: //obowi?zkowa obs?uga meldunku o zamkni?ciu okna
		PostQuitMessage(0);
		return 0;

	default: //standardowa obs?uga pozosta?ych meldunk?w
		return DefWindowProc(okno, kod_meldunku, wParam, lParam);
	}
}
