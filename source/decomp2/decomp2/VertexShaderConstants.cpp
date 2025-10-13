#include "VertexShaderConstants.h"

void VertexShaderConstants::MatrixMul3x4(Vector4* matrix1, Matrix44& matrix2)
{
	int i = 4;
	Vector4* ptr = &c[0];

	do
	{
		ptr->x = matrix2[0][0] * matrix1->x + matrix2[1][0] * matrix1->y + matrix2[2][0] * matrix1->z;
		ptr->y = matrix2[0][1] * matrix1->x + matrix2[1][1] * matrix1->y + matrix2[2][1] * matrix1->z;
		ptr->z = matrix2[0][2] * matrix1->x + matrix2[1][2] * matrix1->y + matrix2[2][2] * matrix1->z;
		ptr->w = 0;

		matrix1 += 1;
		ptr += 1;
	} while (--i);

	ptr->x += matrix2[3][0];
	ptr->y += matrix2[3][1];
	ptr->z += matrix2[3][2];
	ptr->w = 1;
}

void VertexShaderConstants::ProjectionMul(Matrix44& matrix)
{
	int i = 4;
	Vector4* ptr = &c[0];

	do
	{
		ptr->x = matrix[0][0] * ptr->x + matrix[1][0] * ptr->y + matrix[2][0] * ptr->z + matrix[3][0] * ptr->w;
		ptr->y = matrix[0][1] * ptr->x + matrix[1][1] * ptr->y + matrix[2][1] * ptr->z + matrix[3][1] * ptr->w;
		ptr->z = matrix[0][2] * ptr->x + matrix[1][2] * ptr->y + matrix[2][2] * ptr->z + matrix[3][2] * ptr->w;
		ptr->w = matrix[0][3] * ptr->x + matrix[1][3] * ptr->y + matrix[2][3] * ptr->z + matrix[3][3] * ptr->w;

		ptr += 1;
	} while (--i);
}