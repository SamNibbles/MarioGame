#pragma once
class CFloorBlock
{
public:
	CFloorBlock(SDL_Renderer* passedRenderer);
	~CFloorBlock();

	void Draw();

	SDL_Rect GetRect();
	void SetRect(SDL_Rect newRect);

	bool GetActive();
	void SetActive(bool newAct);

private:
	bool Active;

	SDL_Texture* Sprite;
	SDL_Rect Rect;

	SDL_Renderer* renderer;
};

