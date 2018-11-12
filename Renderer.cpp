
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

unsigned int ColorAdd;
unsigned int ColorAdd2;
bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& InPt)
{
	PutPixel(InPt.X, InPt.Y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void UpdateFrame(void)
{
	// Buffer Clear

	SetColor(32, 128, 255);
	
	Clear();


	ColorAdd += 1;
	if (ColorAdd >= 255)
	{
		ColorAdd = 1;
	}
	// Draw
	SetColor(ColorAdd, ColorAdd, ColorAdd);

	// Draw a filled circle with radius 100
	Vector3 center(0.0f, 0.0f);
	float radius = 100.f;
	int nradius = (int)radius;

	static float degree = 0;
	degree += 2;
	degree = fmodf(degree, 360.0f); //2 / 360 = degree¿¡

	Matrix3 rotMat;
	rotMat.SetRotation(degree);
	rotMat.Transpose();

	float maxScale = 0.5;
	float scale = ((sinf(Deg2Rad(degree * 2)) + 1) * 0.5) * maxScale;
	if (scale < 0.1f) scale = 0.1f;

	Matrix3 scaleMat;
	scaleMat.SetScale(scale, scale, scale);

	float maxPos = 100;
	float pos = sinf(Deg2Rad(degree)) * maxPos;
	Matrix3 translationMat;
	translationMat.SetTranslation(pos, pos);

	Matrix3 SR = scaleMat * rotMat;
	Matrix3 TRS = translationMat * rotMat * scaleMat;
	

		for (int i = -nradius; i <= nradius; i++)
		{
			for (int j = -nradius; j <= nradius; j++)
			{
				PutPixel(Vector3((float)i, (float)j) * SR);
			}
		}
		

		float radius2 = 10.0f;
		int nradius2 = (int)radius;

		
		static float degree2 = 0;
		degree2 += 1;
		degree2 = fmodf(degree2, 360.0f);

		float maxPos2 = 500;
		float pos2 = sinf(Deg2Rad(degree2)) * maxPos2;

		Matrix3 translationMat2;
		translationMat2.SetTranslation(pos2, pos2);

		Matrix3 Matrix = translationMat2;

		ColorAdd2 += 5;
		if (ColorAdd2 >= 255)
		{
			ColorAdd2 = 1;
		}
		SetColor(ColorAdd2, ColorAdd2, 1);

		
		Vector3 center2(0.0f, 0.0f);

		for (int i = -nradius2; i <= nradius2; i++)
		{
			for (int j = -nradius2; j <= nradius2; j++)
			{
				Vector3 vertex(i, j);
				if (Vector3::Dist(center2, vertex) <= radius)
				{
					PutPixel(Vector3(i, j) * Matrix);
				}

			}
		}


	// Buffer Swap 
	BufferSwap();
}
