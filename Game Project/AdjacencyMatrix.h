#pragma once

// This adjacency matrix class represents an undirected graph
class AdjacencyMatrix {
protected:
	bool** links;
	int length;

public:
	AdjacencyMatrix(int _length);

	void ModifyLink(int _index1, int _index2, bool _value);
	bool IsLinked(int _index1, int _index2);
	int Length();
};
