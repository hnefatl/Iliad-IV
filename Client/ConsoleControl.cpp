#include "ConsoleControl.h"

#include <Windows.h>

void SetColour(CONSOLECOLOUR foreground, CONSOLECOLOUR background) {

    int Color = foreground + (background * 16);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, Color);
}

void SetCursor(int x, int y) {
  HANDLE hStdout;
  CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
  hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
  csbiInfo.dwCursorPosition.X=x;
  csbiInfo.dwCursorPosition.Y=y;
  SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}

void Clear()
{
	system("cls");
}

void EnableCursor(bool Shown)
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible=Shown;
	Info.dwSize=1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}