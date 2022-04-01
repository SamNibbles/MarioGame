#include "stdafx.h"
#include "Coin.h"


CCoin::CCoin(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;

	Sprite[0] = IMG_LoadTexture(renderer, "Graphics/Coin0.png");
	Sprite[1] = IMG_LoadTexture(renderer, "Graphics/Coin1.png");
	Sprite[2] = IMG_LoadTexture(renderer, "Graphics/Coin2.png");
	Sprite[3] = IMG_LoadTexture(renderer, "Graphics/Coin3.png");

	Rect.w = 34;
	Rect.h = 34;

	Active = false;

	Counter = 0;
	SpriteCount = 0;
	Limit = 5;
}


CCoin::~CCoin()
{
}

void CCoin::Draw()
{
	if (Active)
	{
		SDL_RenderCopy(renderer, Sprite[currentSprite], NULL, &Rect);
	}
}

void CCoin::Update()
{
	if (Active)
	{
		if (StartingPos < 34)
		{
			Rect.y -= 2;
			StartingPos += 2;
		}
		if (StartingPos >= 34)
		{
			Counter++;
			if (Counter == Limit)
			{
				Counter = 0;
				SpriteCount++;
				if (SpriteCount == 1)
					currentSprite = 1;
				if (SpriteCount == 2)
					currentSprite = 2;
				if (SpriteCount == 3)
					currentSprite = 3;
				if (SpriteCount == 4)
				{
					currentSprite = 0;
					SpriteCount = 0;
				}
			}
		}
	}
}

void CCoin::Spawn(int XPos, int YPos)
{
	Active = true;
	Rect.x = XPos;
	Rect.y = YPos;
	StartingPos = 0;
	currentSprite = 0;
	Counter = 0;
	SpriteCount = 0;
}

bool CCoin::GetActive()
{
	return Active;
}

void CCoin::SetActive(bool newActive)
{
	Active = newActive;
}

SDL_Rect CCoin::GetRect()
{
	return Rect;
}

void CCoin::SetRect(SDL_Rect  newRect)
{
	Rect = newRect;
}
