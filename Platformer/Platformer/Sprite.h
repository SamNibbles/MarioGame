#pragma once
class CSprite
{
public:
	CSprite(SDL_Renderer* passedRenderer);
	~CSprite();

	void Draw();
	void Gravity();
	void Jump(int newJumpValue);
	void Update();

	bool GetJumping();
	void SetJumping(bool newJumping);

	int GetX();
	void SetX(int newX);

	int GetY();
	void SetY(int newY);

	SDL_Rect GetRect();
	void SetRect(SDL_Rect newRect);

	int GetDirection();
	void SetDirection(int newDirection);

	void SetPrevDirection(int newPrevDirection);
	int GetPrevDirection();

	int GetXVel();
	void SetXVel(int newX);

	int GetYVel();
	void SetYVel(int newY);

	int GetScore();
	void SetScore(int newScore);

	bool GetAbility(int AbilityNo);
	void SetAbility(int AbilityNo, bool newAbility);

	bool GetHit();
	void SetHit(bool newHit);

	int GetLives();
	void SetLives(bool newLives);

	bool GetImmune();
	void SetImmune(bool newImmune);

	void SetGravityReset(bool newReset);
	void SetJumpReset(bool newReset);

	bool GetTeleport();
	int GetTeleportValue();
	void SetTeleport(bool newTeleport);

private:
	SDL_Texture* Sprite[80];
	SDL_Rect Rect;
	SDL_Rect PositionRect;

	SDL_Renderer* renderer;

	int GravityValue;

	bool Jumping;
	bool Falling;
	int JumpValue;
	bool GravityReset;
	bool JumpReset;
	int MoveSpeed;
	int Score;

	int currentSprite;
	int Direction;
	int PrevDirection;

	int MoveCounter;
	int MoveLimit;
	int MoveSpriteCount;

	int JumpCounter;
	int JumpLimit;
	int JumpSpriteCount;

	float VelocityX;
	float VelocityY;

	int VelocityCapX;
	int VelocityCapY;

	int Width;
	int Height;

	int Lives;
	bool Hit;
	bool Dead;
	bool Immune;
	int ImmuneCount;
	int ImmuneLimit;
	int ImmuneAlphaCount;
	int AlphaValue;
};

