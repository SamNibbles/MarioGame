#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;

	Sprite[0] = IMG_LoadTexture(renderer, "Graphics/Enemy0-0.png");
	Sprite[1] = IMG_LoadTexture(renderer, "Graphics/Enemy0-1.png");
	Sprite[2] = IMG_LoadTexture(renderer, "Graphics/Enemy0-2.png");
	Sprite[3] = IMG_LoadTexture(renderer, "Graphics/Enemy0-3.png");
	Sprite[4] = IMG_LoadTexture(renderer, "Graphics/Enemy0-4.png");
	Sprite[5] = IMG_LoadTexture(renderer, "Graphics/Enemy0-5.png");
	Sprite[6] = IMG_LoadTexture(renderer, "Graphics/Enemy0-6.png");
	Sprite[7] = IMG_LoadTexture(renderer, "Graphics/Enemy0-7.png");
	Sprite[8] = IMG_LoadTexture(renderer, "Graphics/Enemy0-8.png");
	Sprite[9] = IMG_LoadTexture(renderer, "Graphics/Enemy0-9.png");
	Sprite[10] = IMG_LoadTexture(renderer, "Graphics/Enemy0-10.png");
	Sprite[11] = IMG_LoadTexture(renderer, "Graphics/Enemy0-11.png");
	Sprite[12] = IMG_LoadTexture(renderer, "Graphics/Enemy0-12.png");
	Sprite[13] = IMG_LoadTexture(renderer, "Graphics/Enemy0-13.png");
	Sprite[14] = IMG_LoadTexture(renderer, "Graphics/Enemy0-14.png");
	Sprite[15] = IMG_LoadTexture(renderer, "Graphics/Enemy0-15.png");
	Sprite[16] = IMG_LoadTexture(renderer, "Graphics/Enemy0-16.png");
	Sprite[17] = IMG_LoadTexture(renderer, "Graphics/Enemy0-17.png");
	Sprite[18] = IMG_LoadTexture(renderer, "Graphics/Enemy0-18.png");
	Sprite[19] = IMG_LoadTexture(renderer, "Graphics/Enemy0-19.png");

	Rect.w = 40;
	Rect.h = 60;

	PositionRect.x = Rect.x;
	PositionRect.y = Rect.y;

	VelocityCapX = 30;
	VelocityCapY = 50;

	GravityValue = 2;

	currentSprite = 0;
	Direction = 1;
	PrevDirection = 2;
	MoveSpeed = 4;

	MoveSpriteCount = 0;
	MoveLimit = 4;
	MoveCounter = MoveLimit;

	GravityReset = false;
	InShell = false;
}

CEnemy::~CEnemy()
{

}

void CEnemy::Draw()
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

void CEnemy::Update()
{
	if (Active)
	{
		PrevRect = Rect;

		Gravity();

		if (Direction != 0)
			PrevDirection = Direction;

 		if (Direction == 0)
		{
			MoveSpriteCount = 0;
			VelocityX = 0;
			if (InShell)
			{
				Rect.h = 30;

				MoveSpeed = 8;
				if (PrevDirection == 1)
					currentSprite = 8;
				if (PrevDirection == 2)
					currentSprite = 11;
			}
		}

		if (Direction == 1)
		{
			VelocityX = MoveSpeed;
			if (!Falling)
			{
				if (MoveCounter == MoveLimit)
				{
					if (!InShell)
					{
						MoveCounter = 0;
						MoveSpriteCount++;
						if (MoveSpriteCount == 1)
							currentSprite = 0;
						if (MoveSpriteCount == 2)
							currentSprite = 1;
						if (MoveSpriteCount == 3)
							currentSprite = 2;
						if (MoveSpriteCount == 4)
							currentSprite = 3;
						if (MoveSpriteCount == 5)
							currentSprite = 4;
						if (MoveSpriteCount == 6)
							currentSprite = 5;
						if (MoveSpriteCount == 7)
							currentSprite = 6;
						if (MoveSpriteCount == 8)
						{
							currentSprite = 7;
							MoveSpriteCount = 0;
						}
					}
					if (InShell)
					{
						MoveCounter = 0;
						MoveSpriteCount++;
						if (MoveSpriteCount == 1)
							currentSprite = 8;
						if (MoveSpriteCount == 2)
							currentSprite = 9;
						if (MoveSpriteCount == 3)
							currentSprite = 10;
						if (MoveSpriteCount == 4)
						{
							currentSprite = 11;
							MoveSpriteCount = 0;
						}

					}
				}
				MoveCounter++;
			}
		}
		if (Direction == 2)
		{
			VelocityX = -MoveSpeed;
			if (!Falling)
			{
				if (MoveCounter == MoveLimit)
				{
					if (!InShell)
					{
						MoveCounter = 0;
						MoveSpriteCount++;
						if (MoveSpriteCount == 1)
							currentSprite = 12;
						if (MoveSpriteCount == 2)
							currentSprite = 13;
						if (MoveSpriteCount == 3)
							currentSprite = 14;
						if (MoveSpriteCount == 4)
							currentSprite = 15;
						if (MoveSpriteCount == 5)
							currentSprite = 16;
						if (MoveSpriteCount == 6)
							currentSprite = 17;
						if (MoveSpriteCount == 7)
							currentSprite = 18;
						if (MoveSpriteCount == 8)
						{
							currentSprite = 19;
							MoveSpriteCount = 0;
						}
					}
					if (InShell)
					{
						MoveCounter = 0;
						MoveSpriteCount++;
						if (MoveSpriteCount == 1)
							currentSprite = 11;
						if (MoveSpriteCount == 2)
							currentSprite = 10;
						if (MoveSpriteCount == 3)
							currentSprite = 9;
						if (MoveSpriteCount == 4)
						{
							currentSprite = 8;
							MoveSpriteCount = 0;
						}
					}
				}
				MoveCounter++;
			}
		}

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

void CEnemy::Gravity()
{
	if (GravityReset)
	{
		Falling = false;
		GravityReset = false;
		VelocityY = 0;
	}
	VelocityY += GravityValue;
}

void CEnemy::Spawn(int XPos, int YPos)
{
	Active = true;
	Rect.x = XPos;
	Rect.y = YPos;
	Killed = false;
	VelocityY = 0;
}

bool CEnemy::GetActive()
{
	return Active;
}

void CEnemy::SetActive(bool newActive)
{
	Active = newActive;
}

bool CEnemy::GetInShell()
{
	return InShell;
}

void CEnemy::SetInShell(bool newInShell)
{
	InShell = newInShell;
}

bool CEnemy::GetKilled()
{
	return Killed;
}

void CEnemy::SetKilled(bool newKill)
{
	Killed = newKill;
}

SDL_Rect CEnemy::GetRect()
{
	return Rect;
}

void CEnemy::SetRect(SDL_Rect  newRect)
{
	Rect = newRect;
}

SDL_Rect CEnemy::GetPrevRect()
{
	return PrevRect;
}

void CEnemy::SetPrevRect(SDL_Rect  newRect)
{
	PrevRect = newRect;
}

SDL_Rect CEnemy::GetPositionRect()
{
	return PositionRect;
}

void CEnemy::SetPositionRect(SDL_Rect  newRect)
{
	PositionRect = newRect;
}

void CEnemy::SetGravityReset(bool newReset)
{
	GravityReset = newReset;
}

int CEnemy::GetDirection()
{
	return Direction;
}

void CEnemy::SetDirection(int newDirection)
{
	Direction = newDirection;
}

int CEnemy::GetPrevDirection()
{
	return PrevDirection;
}

void CEnemy::SetPrevDirection(int newDirection)
{
	PrevDirection = newDirection;
}

int CEnemy::GetXVel()
{
	return VelocityX;
}

void CEnemy::SetXVel(int newX)
{
	VelocityX = newX;
}

int CEnemy::GetYVel()
{
	return VelocityY;
}

void CEnemy::SetYVel(int newY)
{
	VelocityY = newY;
}
