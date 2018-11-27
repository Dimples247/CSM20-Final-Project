#ifndef VECTOR2I_INCLUDED
#define VECTOR2I_INCLUDED

#include <Windows.h>

// This class represents and (x, y) pair of integers
class Vector2i {
public:
	// Attributes
	int x, y;

	// Constructors
	Vector2i();
	Vector2i(int _x, int _y);

	// Addition and subtraction of vectors
	Vector2i operator+ (Vector2i _vec) const;
	Vector2i operator- (Vector2i _vec) const;

	// Cast operator allows Vector2i to be used in place of the less convenient COORD used by Windows.h for console functions
	operator COORD() const;
};

#endif