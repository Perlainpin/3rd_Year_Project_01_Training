// Semaine_Insertion_Show_Bitmap_With_Time.cpp : Définit le point d'entrée de l'application.
//

#include <Windows.h>
#include <WinUser.h>
#include <random>  
#include <chrono>  
#include <vector>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "framework.h"
#include "Semaine_Insertion_Show_Bitmap_With_Time.h"


#define MAX_LOADSTRING 100

#define DRAW_PIXEL 101

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

FILE* pfile;
BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

BYTE* buffer = nullptr;
BYTE* bgr = nullptr;
long lSize = 0;
int currentY = 0;
int currentX = 0;
int pixel;

std::vector<int> indexPixel;

HDC hdc;
HBITMAP Drawing;
HDC CompatibleDC;

//// Fonction pour lire une image BMP
void readBMP(const char* filePath, BITMAPFILEHEADER& fileHeader, BITMAPINFOHEADER& infoHeader, BYTE*& buffer, BYTE*& bgr, long& lSize) {



    fopen_s(&pfile, filePath, "rb"); // Ouvrir le fichier BMP en mode binaire
    if (pfile == NULL) {
        //std::cerr << "Erreur : impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    // Taille du fichier
    fseek(pfile, 0, SEEK_END);
    lSize = ftell(pfile);
    rewind(pfile);

    // Allocation de la mémoire pour lire le fichier
    buffer = new BYTE[lSize];
    if (buffer == NULL) {
        // std::cerr << "Erreur : problème d'allocation mémoire." << std::endl;
        fclose(pfile);
        return;
    }

    // Lire le fichier dans le buffer
    size_t result = fread(buffer, 1, lSize, pfile);
    if (result != lSize) {
        //std::cerr << "Erreur : la lecture du fichier BMP a échoué." << std::endl;
        fclose(pfile);
        delete[] buffer;
        return;
    }

    fclose(pfile);

    // Appliquer les infos du buffer dans les headers
    memcpy(&fileHeader, buffer, sizeof(BITMAPFILEHEADER));
    memcpy(&infoHeader, buffer + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

    // Récupérer les données des pixels (BGR)
    bgr = buffer + fileHeader.bfOffBits;
}


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
    LoadStringW(hInstance, IDC_SEMAINEINSERTIONSHOWBITMAPWITHTIME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Effectue l'initialisation de l'application :
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEMAINEINSERTIONSHOWBITMAPWITHTIME));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SEMAINEINSERTIONSHOWBITMAPWITHTIME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SEMAINEINSERTIONSHOWBITMAPWITHTIME);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
    case WM_CREATE : {

            SetTimer(hWnd, DRAW_PIXEL, 1, NULL);
            readBMP("BMP.bmp", fileHeader, infoHeader, buffer, bgr, lSize);

            for (int i = 0; i < infoHeader.biWidth * infoHeader.biHeight; i++) {
                indexPixel.push_back(i);
            }

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

            shuffle(indexPixel.begin(), indexPixel.end(), std::default_random_engine(seed));

            // allow to generate only a part of the image
            //indexPixel.erase(indexPixel.begin(), indexPixel.begin() + indexPixel.size()/8);

            break;
        }
    case WM_TIMER: {
        
            switch (wParam) {

                case DRAW_PIXEL:
                {
                    hdc = GetDC(hWnd);

                    // randomly generate
                    if (indexPixel.size() != 0) {

                        for (int i = 0; i < indexPixel.size(); i++) {
                            currentX = indexPixel[i] % infoHeader.biWidth;
                            currentY = indexPixel[i] / infoHeader.biWidth;

                            COLORREF color = GetPixel(CompatibleDC, currentX, currentY);
                            SetPixel(hdc, currentX, currentY, color);
                        }
                        KillTimer(hWnd, DRAW_PIXEL);
                    }
                    

                    // generate top to bottom
                    /*
                    if (indexPixel.size() != 0) {

                        for (int i = 0; i < indexPixel.size(); i++) {
                            currentX = indexPixel[i] / infoHeader.biHeight;
                            currentY = indexPixel[i] % infoHeader.biHeight;

                            COLORREF color = GetPixel(CompatibleDC, currentX, currentY);
                            SetPixel(hdc, currentX, currentY, color);
                        }
                        KillTimer(hWnd, DRAW_PIXEL);
                    }
                    */

                    //generate left to right 
                    /*
                    if (indexPixel.size() != 0) {

                        for (int i = 0; i < indexPixel.size(); i++) {
                            currentX = indexPixel[i] % infoHeader.biWidth;
                            currentY = indexPixel[i] / infoHeader.biWidth;

                            COLORREF color = GetPixel(CompatibleDC, currentX, currentY);
                            SetPixel(hdc, currentX, currentY, color);
                        }
                        KillTimer(hWnd, DRAW_PIXEL);
                    }
                    */

                    

                   
                    ReleaseDC(hWnd, hdc);
                }
                break;     
            }

        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analyse les sélections de menu :
            switch (wmId)
            {
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
            hdc = BeginPaint(hWnd, &ps);

            Drawing = CreateDIBitmap(hdc, &infoHeader, CBM_INIT, bgr, (BITMAPINFO*)&infoHeader, DIB_RGB_COLORS);
            CompatibleDC = CreateCompatibleDC(hdc);
            SelectObject(CompatibleDC, Drawing);

            //BitBlt(hdc, 0, 0, infoHeader.biWidth, infoHeader.biHeight, CompatibleDC, 0, 0,SRCCOPY);

            /*
            for (int x = 0; x < infoHeader.biWidth; x++) {
                for (int y = 0; y < infoHeader.biHeight; y++) {
                    BitBlt(hdc, x, y, infoHeader.biWidth, infoHeader.biHeight, CompatibleDC, x, y, SRCCOPY);
                }
            }
            */
            
            
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

