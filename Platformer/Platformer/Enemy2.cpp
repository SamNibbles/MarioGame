#include "stdafx.h"
#include "Enemy2.h"


CEnemy2::CEnemy2(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;

	Sprite[0] = IMG_LoadTexture(renderer, "Graphics/Enemy1-0.png");
	Sprite[1] = IMG_LoadTexture(renderer, "Graphics/Enemy1-1.png");
	Sprite[2] = IMG_LoadTexture(renderer, "Graphics/Enemy1-2.png");

	Rect.w = 40;
	Rect.h = 40;

	PositionRect.x = Rect.x;
	PositionRect.y = Rect.y;

	VelocityCapX = 30;
	VelocityCapY = 50;

	GravityValue = 2;

	currentSprite = 0;
	Direction = 1;
	PrevDirection = 2;
	MoveSpeed = 3;

	MoveSpriteCount = 0;
	MoveLimit = 2;
	MoveCounter = MoveLimit;

	GravityReset = false;
}


CEnemy2::~CEnemy2()
{
}

void CEnemy2::Draw()
{
	if (Active)
	{
		SDL_QueryTexture(Sprite[currentSprite], NULL, NULL, &Width, &Height);

		PositionRect.w = Width;
		PositionRect.h = Height;

		PositionRect.y = Rect.y;

		if (Direction == 0)
		{
			if (PrevDirection == 1)
				PositionRect.x = Rect.x;
			if (PrevDirection == 2)
				PositionRect.x = Rect.x + Rect.w - PositionRect.w;
		}

		if (Direction == 1)
			PositionRect.x = Rect.x;
		if (Direction == 2)
			PositionRect.x = Rect.x + Rect.w - PositionRect.w;
	}
	SDL_RenderCopy(renderer, Sprite[currentSprite], NULL, &PositionRect);
}

void CEnemy2::Update()
{
	if (Active)
	{
		PrevRect = Rect;

		Gravity();

		if (Direction != 0)
			PrevDirection = Direction;

		if (Direction == 0)
		{
			currentSprite = 0;
			MoveSpriteCount = 0;
			VelocityX = 0;
		}

		if (Direction != 0)
		{
			if (!Falling)
			{
				if (MoveCounter == MoveLimit)
				{
					MoveCounter = 0;
					MoveSpriteCount++;
					if (MoveSpriteCount == 1)
						currentSprite = 1;
					if (MoveSpriteCount == 3)
						currentSprite = 2;
					if (MoveSpriteCount == 4)
						MoveSpriteCount = 0;
				}
				MoveCounter++;
			}
		}

		if (Direction == 1)
			VelocityX = MoveSpeed;
		if (Direction == 2)
			VelocityX = -MoveSpeed;

		//CAP VELOCITIES
		if (VelocityX > VelocityCapX)
			VelocityX = VelocityCapX;
		if (VelocityX < -VelocityCapX)
			VelocityX = -VelocityCapX;

		if (VelocityY > VelocityCapY)
			VelocityY = VelocityCapY;

		Rect.x += VelocityX;
		Rect.y += VelocityY;
	}
}

void CEnemy2::Gravity()
{
	if (GravityReset)
	{
		Falling = false;
		GravityReset = false;
		VelocityY = 0;
	}
	VelocityY += GravityValue;
}

void CEnemy2::Spawn(int XPos, int YPos)
{
	Active = true;
	Rect.x = XPos;
	Rect.y = YPos;
	Killed = false;
	VelocityY = 0;
}

bool CEnemy2::GetActive()
{
	return Active;
}

void CEnemy2::SetActive(bool newActive)
{
	Active = newActive;
}

bool CEnemy2::GetKilled()
{
	return Killed;
}

void CEnemy2::SetKilled(bool newKill)
{
	Killed = newKill;
}

SDL_Rect CEnemy2::GetRect()
{
	return Rect;
}

void CEnemy2::SetRect(SDL_Rect  newRect)
{
	Rect = newRect;
}

SDL_Rect CEnemy2::GetPrevRect()
{
	return PrevRect;
}

void CEnemy2::SetPrevRect(SDL_Rect  newRect)
{
	PrevRect = newRect;
}

SDL_Rect CEnemy2::GetPositionRect()
{
	return PositionRect;
}

void CEnemy2::SetPositionRect(SDL_Rect  newRect)
{
	PositionRect = newRect;
}

void CEnemy2::SetGravityReset(bool newReset)
{
	GravityReset = newReset;
}

int CEnemy2::GetDirection()
{
	return Direction;
}

void CEnemy2::SetDirection(int newDirection)
{
	Direction = newDirection;
}

int CEnemy2::GetPrevDirection()
{
	return PrevDirection;
}

void CEnemy2::SetPrevDirection(int newDirection)
{
	PrevDirection = newDirection;
}

int CEnemy2::GetXVel()
{
	return VelocityX;
}

void CEnemy2::SetXVel(int newX)
{
	VelocityX = newX;
}

int CEnemy2::GetYVel()
{
	return VelocityY;
}

void CEnemy2::SetYVel(int newY)
{
	VelocityY = newY;
}


