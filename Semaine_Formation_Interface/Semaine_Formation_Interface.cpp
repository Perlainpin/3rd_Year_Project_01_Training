// Semaine_Formation_Interface.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "Semaine_Formation_Interface.h"
#include <string>

#define MAX_LOADSTRING 100

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale


// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND Show;
__int64 valeurA;
__int64 valeurB;
__int64 result;
char sign;
TCHAR Screen;

#define BTN_ADD 100
#define BTN_MINUS 101
#define BTN_TIME 102
#define BTN_DIVIDE 103
#define BTN_0 0
#define BTN_1 1
#define BTN_2 2
#define BTN_3 3
#define BTN_4 4
#define BTN_5 5
#define BTN_6 6
#define BTN_7 7
#define BTN_8 8
#define BTN_9 9
#define BTN_RESET 114
#define BTN_DOT 115
#define BTN_BACK 116
#define BTN_EQUAL 117


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

   // TODO: Placez le code ici.

    // Initialise les chaînes globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SEMAINEFORMATIONINTERFACE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEMAINEFORMATIONINTERFACE));

    MSG msg;

    // Boucle de messages principale :
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEMAINEFORMATIONINTERFACE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SEMAINEFORMATIONINTERFACE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Stocke le handle d'instance dans la variable globale

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 195, 425, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

  

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void UpdateNumber(int value) {
    wchar_t buffer[256];
    wsprintfW(buffer, L"%d", value);
    SetWindowText(Show, buffer);

};

void Calcul(int value) {

    if (sign == NULL) {
        if (valeurA == NULL) {
            valeurA = value;
            UpdateNumber(valeurA);
        }
        else {
            std::string a = std::to_string(value);
            std::string b = std::to_string(valeurA);
            valeurA = _atoi64((b + a).c_str());
            UpdateNumber(valeurA);
        }
        result = valeurA;
    }
    else {
        valeurA = result;
        if (valeurB == NULL) {
            valeurB = value;
            UpdateNumber(valeurB);
        }
        else {
            std::string a = std::to_string(value);
            std::string b = std::to_string(valeurB);
            valeurB = _atoi64((b+a).c_str());
            UpdateNumber(valeurB);
        }
    }

}

void RemoveNumber() {
    if (sign == NULL) {
        if (valeurA == NULL) {
            valeurA = 0;
            UpdateNumber(valeurA);
        }
        else {
            std::string a = std::to_string(valeurA);
            a.erase(a.end()-1);
            valeurA = _atoi64((a).c_str());
            UpdateNumber(valeurA);
        }
    }
    else {
        if (valeurB == NULL) {
            valeurB = 0;
            UpdateNumber(valeurB);
        }
        else {
            std::string a = std::to_string(valeurB);
            a.erase(a.end()-1);
            valeurB = _atoi64((a).c_str());
            UpdateNumber(valeurB);
        }
    }
}

void Result() {
    if (sign == '+') {
        result = valeurA + valeurB;
        valeurA = result;
        valeurB = NULL;
        UpdateNumber(result);
    }
    else if (sign == '-') {
        result = valeurA - valeurB;
        valeurA = result;
        valeurB = NULL;
        UpdateNumber(result);
    }
    else if (sign == '*') {
        result = valeurA * valeurB;
        valeurA = result;
        valeurB = NULL;
        UpdateNumber(result);
    }
    else if (sign == '/') {
        if (valeurB == 0) {
            SetWindowText(Show, L"undef");
        }
        else {
            result = valeurA / valeurB;
            valeurA = result;
            valeurB = NULL;
            UpdateNumber(result);
        }
        
    }
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE :{

        

            Show = CreateWindow(
                L"STATIC",
                L"0",
                WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER ,
                10,
                10,
                160,
                50,
                hWnd,
                NULL,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND AddButton = CreateWindow(
                L"BUTTON",
                L"+",
                WS_VISIBLE | WS_CHILD,
                65,
                110,
                50,
                50,
                hWnd,
                (HMENU)BTN_ADD,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND MinusButton = CreateWindow(
                L"BUTTON",
                L"-",
                WS_VISIBLE | WS_CHILD,
                65,
                60,
                50,
                50,
                hWnd,
                (HMENU)BTN_MINUS,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND TimeButton = CreateWindow(
                L"BUTTON",
                L"x",
                WS_VISIBLE | WS_CHILD,
                120,
                110,
                50,
                50,
                hWnd,
                (HMENU)BTN_TIME,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND DivideButton = CreateWindow(
                L"BUTTON",
                L"/",
                WS_VISIBLE | WS_CHILD,
                10,
                110,
                50,
                50,
                hWnd,
                (HMENU)BTN_DIVIDE,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND DotButton = CreateWindow(
                L"BUTTON",
                L".",
                WS_VISIBLE | WS_CHILD,
                10,
                310,
                50,
                50,
                hWnd,
                (HMENU)BTN_DOT,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button0 = CreateWindow(
                L"BUTTON",
                L"0",
                WS_VISIBLE | WS_CHILD,
                65,
                310,
                50,
                50,
                hWnd,
                (HMENU)BTN_0,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button1 = CreateWindow(
                L"BUTTON",
                L"1",
                WS_VISIBLE | WS_CHILD,
                10,
                160,
                50,
                50,
                hWnd,
                (HMENU)BTN_1,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button2 = CreateWindow(
                L"BUTTON",
                L"2",
                WS_VISIBLE | WS_CHILD,
                65,
                160,
                50,
                50,
                hWnd,
                (HMENU)BTN_2,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button3 = CreateWindow(
                L"BUTTON",
                L"3",
                WS_VISIBLE | WS_CHILD,
                120,
                160,
                50,
                50,
                hWnd,
                (HMENU)BTN_3,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button4 = CreateWindow(
                L"BUTTON",
                L"4",
                WS_VISIBLE | WS_CHILD,
                10,
                210,
                50,
                50,
                hWnd,
                (HMENU)BTN_4,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button5 = CreateWindow(
                L"BUTTON",
                L"5",
                WS_VISIBLE | WS_CHILD,
                65,
                210,
                50,
                50,
                hWnd,
                (HMENU)BTN_5,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button6 = CreateWindow(
                L"BUTTON",
                L"6",
                WS_VISIBLE | WS_CHILD,
                120,
                210,
                50,
                50,
                hWnd,
                (HMENU)BTN_6,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button7 = CreateWindow(
                L"BUTTON",
                L"7",
                WS_VISIBLE | WS_CHILD,
                10,
                260,
                50,
                50,
                hWnd,
                (HMENU)BTN_7,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button8 = CreateWindow(
                L"BUTTON",
                L"8",
                WS_VISIBLE | WS_CHILD,
                65,
                260,
                50,
                50,
                hWnd,
                (HMENU)BTN_8,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND Button9 = CreateWindow(
                L"BUTTON",
                L"9",
                WS_VISIBLE | WS_CHILD,
                120,
                260,
                50,
                50,
                hWnd,
                (HMENU)BTN_9,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND ResetButton = CreateWindow(
                L"BUTTON",
                L"RESET",
                WS_VISIBLE | WS_CHILD,
                10,
                60,
                50,
                50,
                hWnd,
                (HMENU)BTN_RESET,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND EqualButton = CreateWindow(
                L"BUTTON",
                L"=",
                WS_VISIBLE | WS_CHILD,
                120,
                310,
                50,
                50,
                hWnd,
                (HMENU)BTN_EQUAL,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

            HWND BackButton = CreateWindow(
                L"BUTTON",
                L"BACK",
                WS_VISIBLE | WS_CHILD,
                120,
                60,
                50,
                50,
                hWnd,
                (HMENU)BTN_BACK,
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);

        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
            case BTN_ADD:
                sign = '+';
                break;
            case BTN_MINUS:
                sign = '-';
                break;
            case BTN_TIME :
                sign = '*';
                break;
            case BTN_DIVIDE:
                sign = '/';
                break;
            case BTN_0:
                Calcul(BTN_0);
                break;
            case BTN_1:
                Calcul(BTN_1);
                break;
            case BTN_2:
                Calcul(BTN_2);
                break;
            case BTN_3:
                Calcul(BTN_3);
                break;
            case BTN_4:
                Calcul(BTN_4);
                break;
            case BTN_5:
                Calcul(BTN_5);
                break;
            case BTN_6:
                Calcul(BTN_6);
                break;
            case BTN_7:
                Calcul(BTN_7);
                break;
            case BTN_8:
                Calcul(BTN_8);
                break;
            case BTN_9:
                Calcul(BTN_9);
                break;
            case BTN_RESET:
                UpdateNumber(0);
                valeurA = NULL;
                valeurB = NULL;
                sign = NULL;
                break;
            case BTN_DOT:
                // TO DO 
                break;
            case BTN_BACK:
                RemoveNumber();
                break;
            case BTN_EQUAL:
                Result();
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Ajoutez ici le code de dessin qui utilise hdc...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
