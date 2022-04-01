#pragma once
class CEnemy
{
public:
	CEnemy(SDL_Renderer* passedRenderer);
	~CEnemy();

	void Draw();
	void Gravity();
	void Update();
	void Spawn(int xpos, int ypos);

	void SetGravityReset(bool newReset);

	int GetXVel();
	void SetXVel(int newX);

	int GetYVel();
	void SetYVel(int newY);

	bool GetActive();
	void SetActive(bool newActive);

	bool GetInShell();
	void SetInShell(bool newInShell);

	bool GetKilled();
	void SetKilled(bool newKilled);

	int GetDirection();
	void SetDirection(int newDirection);

	int GetPrevDirection();
	void SetPrevDirection(int newDirection);

	SDL_Rect GetRect();
	void SetRect(SDL_Rect newRect);

	SDL_Rect GetPositionRect();
	void SetPositionRect(SDL_Rect newRect);

	SDL_Rect GetPrevRect();
	void SetPrevRect(SDL_Rect newRect);

private:
	SDL_Texture* Sprite[20];
	SDL_Rect Rect;
	SDL_Rect PrevRect;
	SDL_Rect PositionRect;

	SDL_Renderer* renderer;

	bool Active;

	int currentSprite;
	int Direction;
	int PrevDirection;
	int Width;
	int Height;

	int MoveCounter;
	int MoveLimit;
	int MoveSpriteCount;

	int MoveSpeed;
	int VelocityX;
	int VelocityY;

	int VelocityCapX;
	int VelocityCapY;

	int GravityValue;
	bool GravityReset;
	bool Falling;

	bool Killed;
	bool InShell;
};

