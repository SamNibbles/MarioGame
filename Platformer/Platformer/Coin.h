#pragma once
class CCoin
{
public:
	CCoin(SDL_Renderer* passedRenderer);
	~CCoin();

	void Draw();
	void Update();
	void Spawn(int xpos, int ypos);

	bool GetActive();
	void SetActive(bool newActive);

	SDL_Rect GetRect();
	void SetRect(SDL_Rect newRect);

private:
	SDL_Texture* Sprite[5];
	SDL_Rect Rect;
	SDL_Rect PrevRect;
	SDL_Rect PositionRect;

	SDL_Renderer* renderer;

	bool Active;

	int currentSprite;
	int StartingPos;

	int Counter;
	int Limit;
	int SpriteCount;
};

