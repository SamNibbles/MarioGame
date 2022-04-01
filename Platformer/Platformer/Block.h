#pragma once
class CBlock
{
public:
	CBlock(SDL_Renderer* passedRenderer);
	~CBlock();

	void Draw();
	void Update();

	SDL_Rect GetRect();
	void SetRect(SDL_Rect newRect);

	SDL_Rect GetPrevRect();
	void SetPrevRect(SDL_Rect newPrevRect);

	char GetType();
	void SetType(char newType);

	int GetDirection();
	void SetDirection(int newDirection);

	bool GetChange();
	void SetChange(bool newChange);

	bool GetOnTop();
	void SetOnTop(bool newOnTop);

private:
	char Type;
	int currentSprite;

	SDL_Texture* Sprite[12];
	SDL_Rect Rect;
	SDL_Rect PrevRect;

	SDL_Renderer* renderer;

	int Count;
	int Limit;
	int Direction;
	int PrevDirection;
};

