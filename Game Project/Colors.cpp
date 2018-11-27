#include "Colors.h"

// TextColor + BackgroundColor
int operator+ (TextColor _tCol, BackgroundColor _bCol) {
	return (int)_tCol + (int)_bCol;
}
// BackgroundColor + TextColor
int operator+ (BackgroundColor _bCol, TextColor _tCol) {
	return (int)_tCol + (int)_bCol;
}