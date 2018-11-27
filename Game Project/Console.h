#ifndef CONSOLE_INCLUDED
#define CONSOLE_INCLUDED

#include <Windows.h>
#include "Vector2i.h"
#include "Colors.h"

static class Console {
public:
	// Handle to default console and console size
	static const HANDLE DefaultConsole;


	static Vector2i GetConsoleSize();

	// Can optionally clear screen to a specific color
	static void ClearScreen(BackgroundColor _bCol = BackgroundColor::Black);

	static Vector2i GetCursorPos();
	static void SetCursorPos(Vector2i _pos);

	// Sets the text and background color of the console
	static void SetConsoleColor(BackgroundColor _bCol);
	static void SetConsoleColor(TextColor _tCol);
	static void SetConsoleColor(int _col);
};

#endif