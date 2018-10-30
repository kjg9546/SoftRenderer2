
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector2.h"
#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint& InPt)
{
	PutPixel(InPt.x, InPt.y);
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

	// Draw
	SetColor(255, 0, 0);
	PutPixel(0, 0);


	/*Matrix2 scaleMat;
	scaleMat.SetScale(2.f, 0.5f);

	Matrix2 RotMat;
	RotMat.SetRotation(30.f);

	Matrix2 SRMat = scaleMat * RotMat;
	Matrix2 RSMat = RotMat * scaleMat;*/

	// Draw a circle with radius 100
	Vector2 center(0.f, 0.f);
	float radius = 100.f;
	int nradius = (int)radius;

	static float degree = 0;
	degree += 1.f;
	degree = fmodf(degree, 360.f);

	Matrix2 rotmat;
	rotmat.SetRotation(degree);

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = -nradius; j <= nradius; j++)
		{
			PutPixel(Vector2(i, j) * rotmat);
		}
	}

	//Vector2 startVec(radius, 0.f);

	//for (int i = 0; i < 360; i++)
	//{
	//	Matrix2 rotMat;
	//	rotMat.SetRotation((float)i);
	//	PutPixel(startVec * rotMat);

	//}

	for (int i = -nradius; i <= nradius; i++)
	{
		for (int j = 0/*-nradius*/; j <= nradius; j++)
		{
			IntPoint pt(i, j);
			Vector2 ptVec = pt.ToVector2();
			if(Vector2::DistSquared(center, pt.ToVector2()) <= radius * radius)
				{
				//IntPoint scaledPt(ptVec * scaleMat);
				//IntPoint rotatedPt(ptVec * RotMat);
				//IntPoint SRpt(ptVec * SRMat);
				//IntPoint RSpt(ptVec * RSMat);
				//PutPixel(RSpt);
				}
		}
	}
	

	// Buffer Swap 
	BufferSwap();
}