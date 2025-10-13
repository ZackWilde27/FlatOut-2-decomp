#pragma once
#include "BasicTypes.h"

// A buffer for preparing to update the first 10 VertexShaderConstants
class VertexShaderConstants
{
	Vector4 c[10];

	// Multiplies 2 matrices together, overwriting the matrix in the viewProj slot.
	// It only does a 3x3, overwriting those vectors, and then adds the 4th row from matrix2 to what's already there
	// What's strange is that the matrices are given in different ways, the first is the pointer to the first Vector4 of a matrix, and the second is a pointer to the actual matrix
	// It might just be ghidra's mistake though
	void MatrixMul3x4(Vector4* matrix1, Matrix44& matrix2);

	// Multiplies the already existing projection matrix by another matrix
	void ProjectionMul(Matrix44& matrix);
};