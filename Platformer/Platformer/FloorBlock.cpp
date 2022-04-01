#include "stdafx.h"
#include "FloorBlock.h"


CFloorBlock::CFloorBlock(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;
	Sprite = NULL;
	Sprite = IMG_LoadTexture(renderer, "Graphics/Floor.png");
	Active = false;

	Rect.x = 0;
	Rect.y = 0;
	Rect.w = 50;
	Rect.h = 50;
}

CFloorBlock::~CFloorBlock()
{

}

void CFloorBlock::Draw()
{
	if (Active)
		SDL_RenderCopy(renderer, Sprite, NULL, &Rect);
}

SDL_Rect CFloorBlock::GetRect()
{
	return Rect;
}

void CFloorBlock::SetRect(SDL_Rect newRect)
{
	Rect = newRect;
}

bool CFloorBlock::GetActive()
{
	return Active;
}

void CFloorBlock::SetActive(bool newAct)
{
	Active = newAct;
}
