#include "stdafx.h"
#include "Arrow.h"


CArrow::CArrow(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;
	Sprite = IMG_LoadTexture(renderer, "Graphics/Arrow.png");

	Rect.x = 0;
	Rect.y = 0;
	Rect.w = 41;
	Rect.h = 13;

	VelocityX = 30;
	VelocityY = 0;

	GravityValue = 1;

	Fire = false;
}

CArrow::~CArrow()
{
}

void CArrow::Update()
{
	if (!Fire)
	{
		if (MouseVectorX == 0 && MouseVectorY == 0)
			Angle = 0;
		if (MouseVectorX == 0 && MouseVectorY > 0)
			Angle = 0;
		if (MouseVectorX > 0 && MouseVectorY == 0)
			Angle = 90;
		if (MouseVectorX == 0 && MouseVectorY < 0)
			Angle = 180;
		if (MouseVectorX < 0 && MouseVectorY == 0)
			Angle = 270;

		if (MouseVectorX > 0 && MouseVectorY > 0)
			Angle = atan((float)MouseVectorX / (float)MouseVectorY) * (180 / M_PI);
		if (MouseVectorX > 0 && MouseVectorY < 0)
			Angle = (-atan((float)MouseVectorY / (float)MouseVectorX) * (180 / M_PI)) + 90;
		if (MouseVectorX < 0 && MouseVectorY < 0)
			Angle = (atan((float)MouseVectorX / (float)MouseVectorY) * (180 / M_PI)) + 180;
		if (MouseVectorX < 0 && MouseVectorY > 0)
			Angle = (-atan((float)MouseVectorY / (float)MouseVectorX) * (180 / M_PI)) + 270;

		VelocityX = (float)MouseVectorX / 10;

		if (VelocityX > 30)
			VelocityX = 30;

		VelocityY = -(VelocityX / tan(Angle * (M_PI / 180)));
		VelocityY -= (((float)MouseVectorX / (float)VelocityX) / 2);
	}
	if (Fire)
	{
		VelocityY += GravityValue;

		Angle = atan((float)VelocityY / (float)VelocityX) * (180 / M_PI);
		
		Rect.x += VelocityX;
		Rect.y += VelocityY;

		if (Rect.x > 1000 || Rect.x < 0 || Rect.y > 550)
			Fire = false;
	}
}

void CArrow::Draw()
{
	SDL_RenderCopy(renderer, Sprite, NULL, &Rect);
}

int CArrow::GetX()
{
	return Rect.x;
}

void CArrow::SetX(int newX)
{
	Rect.x = newX;
}

int CArrow::GetY()
{
	return Rect.y;
}

void CArrow::SetY(int newY)
{
	Rect.y = newY;
}

bool CArrow::GetFire()
{
	return Fire;
}

void CArrow::SetFire(bool newFire)
{
	Fire = newFire;
}

void CArrow::SetVectorX(float newVector)
{
	MouseVectorX = newVector;
}

void CArrow::SetVectorY(float newVector)
{
	MouseVectorY = newVector;
}


