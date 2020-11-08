#include <iostream>
#include "windows.h"

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)
std::wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int main() {
    auto *screen = new wchar_t[80 * 30];
    for (int i=0;i<80*30;i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer
            (GENERIC_READ | GENERIC_WRITE, 0,
             nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

    pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer

    for (int x = 0; x < nFieldWidth; x++) // Board Boundary
        for (int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

    for (int x = 0; x < nFieldWidth; x++)
        for (int y = 0; y < nFieldHeight; y++)
         screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];

    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dbyteswritten;
    while(1)
    WriteConsoleOutputCharacter(hConsole, reinterpret_cast<LPCSTR>(screen), 80 * 30, {0, 0}, &dbyteswritten);
    return 0;
}
