#include "stdafx.h"
#include "Block.h"

CBlock::CBlock(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;
	Sprite[0] = IMG_LoadTexture(renderer, "Graphics/Block0.png");
	Sprite[1] = IMG_LoadTexture(renderer, "Graphics/Block1.png");
	Sprite[2] = IMG_LoadTexture(renderer, "Graphics/Block2.png");
	Sprite[3] = IMG_LoadTexture(renderer, "Graphics/Block3.png");
	Sprite[4] = IMG_LoadTexture(renderer, "Graphics/Block4.png");
	Sprite[5] = IMG_LoadTexture(renderer, "Graphics/Block5.png");
	Sprite[6] = IMG_LoadTexture(renderer, "Graphics/Block6.png");
	Sprite[7] = IMG_LoadTexture(renderer, "Graphics/Block7.png");
	Sprite[8] = IMG_LoadTexture(renderer, "Graphics/Block8.png");
	Sprite[9] = IMG_LoadTexture(renderer, "Graphics/Block9.png");
	Sprite[10] = IMG_LoadTexture(renderer, "Graphics/BlockA.png");
	Sprite[11] = IMG_LoadTexture(renderer, "Graphics/BlockB.png");

	currentSprite = 0;

	Count = 0;
	Limit = 50;

	Direction = 0;
}


CBlock::~CBlock()
{

}

void CBlock::Update()
{
	PrevRect = Rect;

	if (Type == '0')
		currentSprite = 0;
	if (Type == '1')
		currentSprite = 1;
	if (Type == '2')
		currentSprite = 2;
	if (Type == '3')
		currentSprite = 3;
	if (Type == '4')
		currentSprite = 4;
	if (Type == '5')
		currentSprite = 5;
	if (Type == '6')
		currentSprite = 6;
	if (Type == '7')
		currentSprite = 7;
	if (Type == '8')
		currentSprite = 8;
	if (Type == '9')
		currentSprite = 9;
	if (Type == 'A')
		currentSprite = 10;
	if (Type == 'B')
		currentSprite = 11;
}

void CBlock::Draw()
{
	if (Rect.x + Rect.w > 0 && Rect.x < 1000)
	{
		if (Rect.y + Rect.h > 0 && Rect.y < 550)
		{			
			SDL_RenderCopy(renderer, Sprite[currentSprite], NULL, &Rect);
		}
	}
}

SDL_Rect CBlock::GetRect()
{
	return Rect;
}

void CBlock::SetRect(SDL_Rect newRect)
{
	Rect = newRect;
}

SDL_Rect CBlock::GetPrevRect()
{
	return PrevRect;
}

void CBlock::SetPrevRect(SDL_Rect newPrevRect)
{
	PrevRect = newPrevRect;
}

char CBlock::GetType()
{
	return Type;
}

void CBlock::SetDirection(int newDirection)
{
	Direction = newDirection;
}

int CBlock::GetDirection()
{
	return Direction;
}

void CBlock::SetType(char newType)
{
	Type = newType;
}