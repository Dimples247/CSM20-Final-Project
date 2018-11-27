#include "Vector2i.h"

// Constructors
Vector2i::Vector2i() {
	x = 0;
	y = 0;
}
Vector2i::Vector2i(int _x, int _y) {
	x = _x;
	y = _y;
}

// Operator overloads
Vector2i Vector2i::operator+ (Vector2i _vec) const {
	return Vector2i(x + _vec.x, y + _vec.y);
}
Vector2i Vector2i::operator- (Vector2i _vec) const {
	return Vector2i(x - _vec.x, y - _vec.y);
}
Vector2i::operator COORD() const {
	COORD c;
	c.X = x;
	c.Y = y;
	return c;
}