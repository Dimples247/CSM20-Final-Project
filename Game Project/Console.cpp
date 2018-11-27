#include "Console.h"

#include <iostream>
#include <string>

const HANDLE Console::DefaultConsole = GetStdHandle(STD_OUTPUT_HANDLE);

Vector2i Console::GetConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return Vector2i(columns, rows);
}

void Console::ClearScreen(BackgroundColor _bCol) {
	Vector2i consoleSize = GetConsoleSize();
	int numChars = consoleSize.x * consoleSize.y;

	DWORD Written;
	FillConsoleOutputCharacter(DefaultConsole, ' ', numChars, { 0, 0 }, &Written);
	FillConsoleOutputAttribute(DefaultConsole, (int)_bCol, numChars, { 0, 0 }, &Written);
}
Vector2i Console::GetCursorPos() {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(DefaultConsole, &cbsi);
	return Vector2i(cbsi.dwCursorPosition.X, cbsi.dwCursorPosition.Y);
}
void Console::SetCursorPos(Vector2i _pos) {
	SetConsoleCursorPosition(DefaultConsole, _pos);
}
void Console::SetConsoleColor(BackgroundColor _bCol) {
	SetConsoleTextAttribute(DefaultConsole, (int)_bCol);
}
void Console::SetConsoleColor(TextColor _tCol) {
	SetConsoleTextAttribute(DefaultConsole, (int)_tCol);
}
void Console::SetConsoleColor(int _col) {
	SetConsoleTextAttribute(DefaultConsole, _col);
}