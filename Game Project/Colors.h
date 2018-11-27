#ifndef COLOR_INCLUDED
#define COLOR_INCLUDED

// This file contains enums for the 16 colors used by Windows.h for changing the foreground and background colors of the console

enum class TextColor {
	Black = 0x0,
	DarkBlue = 0x1,
	DarkGreen = 0x2,
	DarkCyan = 0x3,
	DarkRed = 0x4,
	Purple = 0x5,
	Gold = 0x6,
	LightGray = 0x7,
	Gray = 0x8,
	Blue = 0x9,
	Green = 0xA,
	Cyan = 0xB,
	Red = 0xC,
	Magenta = 0xD,
	Yellow = 0xE,
	White = 0xF
};

enum class BackgroundColor {
	Black = 0x00,
	DarkBlue = 0x10,
	DarkGreen = 0x20,
	DarkCyan = 0x30,
	DarkRed = 0x40,
	Purple = 0x50,
	Gold = 0x60,
	LightGray = 0x70,
	Gray = 0x80,
	Blue = 0x90,
	Green = 0xA0,
	Cyan = 0xB0,
	Red = 0xC0,
	Magenta = 0xD0,
	Yellow = 0xE0,
	White = 0xF0
};

// These operators allow you to add a background and foreground into one integer since that is how they are treated by Windows.h
int operator+ (TextColor _tCol, BackgroundColor _bCol);
int operator+ (BackgroundColor _bCol, TextColor _tCol);

#endif