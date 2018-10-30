#include "stdafx.h"
#include "Vector2.h"

float Vector2::Dist(const Vector2 & v1, const Vector2 & v2)
{

	return sqrtf(Vector2::DistSquared(v1, v2));
}

float Vector2::DistSquared(const Vector2 & v1, const Vector2 & v2)
{
	float xLength = v2.x - v1.x;
	float yLength = v2.y - v1.y;

	return xLength * xLength + yLength * yLength;
}

Vector2 Vector2::operator*(const Matrix2 & Mat) const
{
	Vector2 result;
	result.x = x * Mat._11 + y * Mat._12;
	result.y = x * Mat._21 + y * Mat._22;

	return result;
}

bool Vector2::Equals(const Vector2 & V, float tolerance) const
{
	return (fabs(x - V.x) <= tolerance) && (fabs(x - V.y) <= tolerance);
}
