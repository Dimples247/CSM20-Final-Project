#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const int _length) {
	length = _length;
	links = new bool*[_length];
	for (int i = 0; i < _length; i++)
		links[i] = new bool[_length - i];
	for (int i = 0; i < _length; i++)
		for (int j = 0; j < _length; j++)
			links[i][j] = false;
}
void AdjacencyMatrix::ModifyLink(int _index1, int _index2, bool _value) {
	bool isOrdered = _index1 < _index2;
	links[(isOrdered ? _index1 : _index2)][(isOrdered ? _index2 : _index1)] = _value;
}
bool AdjacencyMatrix::IsLinked(int _index1, int _index2) {
	bool isOrdered = _index1 < _index2;
	return links[(isOrdered ? _index1 : _index2)][(isOrdered ? _index2 : _index1)];
}
int AdjacencyMatrix::Length() {
	return length;
}