#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Block.h"
#include "Coin.h"
#include "Arrow.h"

class CMain
{
public:
	CMain();
	~CMain();

	void GameLoop();
	void Update();
	void Collision();
	void Inputs();
	void Draw();
	void MapReset();

private:
	const Uint8 *Keys;
	int GridX = 200;
	int GridY = 50;
	SDL_Rect PrevMainGrid[200][50];
	SDL_Rect mainGrid[200][50];
	int valueGrid[200][50];
	bool quit;
	int Direction;
	int timeCheck;
	bool GravityReset;
	bool JumpReset;
	bool SetJumping;
	int FallAmount;
	int VectorX;
	int VectorY;
	int BlockSelected;
	bool KeyPressed;
	bool MousePressed;
	bool PlayerColliding;
	bool OnMoveBlock;
	int MoveDirection;
	int FPS;

	SDL_Rect ChangeAmount;

	CSprite* Man;
	CEnemy* Koopa[50];
	CEnemy2* Goomba[50];
	CBlock* baseBlock[200][50];
	CCoin* Coin[100];
	CArrow* Arrow;

	CSDL_Setup* csdl_setup;

	SDL_Rect CharacterBlockCollision(SDL_Rect PrevCharRect, SDL_Rect CharRect, SDL_Rect PrevBlockRect, SDL_Rect BlockRect);
};
	

