#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passedRenderer)
{
	renderer = passedRenderer;

	Sprite[0] = IMG_LoadTexture(renderer, "Graphics/Player0.png");
	Sprite[1] = IMG_LoadTexture(renderer, "Graphics/Player1.png");
	Sprite[2] = IMG_LoadTexture(renderer, "Graphics/Player2.png");
	Sprite[3] = IMG_LoadTexture(renderer, "Graphics/Player3.png");
	Sprite[4] = IMG_LoadTexture(renderer, "Graphics/Player4.png");
	Sprite[5] = IMG_LoadTexture(renderer, "Graphics/Player5.png");
	Sprite[6] = IMG_LoadTexture(renderer, "Graphics/Player6.png");
	Sprite[7] = IMG_LoadTexture(renderer, "Graphics/Player7.png");
	Sprite[8] = IMG_LoadTexture(renderer, "Graphics/Player8.png");
	Sprite[9] = IMG_LoadTexture(renderer, "Graphics/Player9.png");
	Sprite[10] = IMG_LoadTexture(renderer, "Graphics/Player10.png");
	Sprite[11] = IMG_LoadTexture(renderer, "Graphics/Player11.png");
	Sprite[12] = IMG_LoadTexture(renderer, "Graphics/Player12.png");
	Sprite[13] = IMG_LoadTexture(renderer, "Graphics/Player13.png");
	Sprite[14] = IMG_LoadTexture(renderer, "Graphics/Player14.png");
	Sprite[15] = IMG_LoadTexture(renderer, "Graphics/Player15.png");
	Sprite[16] = IMG_LoadTexture(renderer, "Graphics/Player16.png");
	Sprite[17] = IMG_LoadTexture(renderer, "Graphics/Player17.png");
	Sprite[18] = IMG_LoadTexture(renderer, "Graphics/Player18.png");
	Sprite[19] = IMG_LoadTexture(renderer, "Graphics/Player19.png");
	Sprite[20] = IMG_LoadTexture(renderer, "Graphics/Player20.png");
	Sprite[21] = IMG_LoadTexture(renderer, "Graphics/Player21.png");
	Sprite[22] = IMG_LoadTexture(renderer, "Graphics/Player22.png");
	Sprite[23] = IMG_LoadTexture(renderer, "Graphics/Player23.png");
	Sprite[24] = IMG_LoadTexture(renderer, "Graphics/Player24.png");
	Sprite[25] = IMG_LoadTexture(renderer, "Graphics/Player25.png");
	Sprite[26] = IMG_LoadTexture(renderer, "Graphics/Player26.png");
	Sprite[27] = IMG_LoadTexture(renderer, "Graphics/Player27.png");
	Sprite[28] = IMG_LoadTexture(renderer, "Graphics/Player28.png");
	Sprite[29] = IMG_LoadTexture(renderer, "Graphics/Player29.png");
	Sprite[30] = IMG_LoadTexture(renderer, "Graphics/Player30.png");
	Sprite[31] = IMG_LoadTexture(renderer, "Graphics/Player31.png");
	Sprite[32] = IMG_LoadTexture(renderer, "Graphics/Player32.png");
	Sprite[33] = IMG_LoadTexture(renderer, "Graphics/Player33.png");
	Sprite[34] = IMG_LoadTexture(renderer, "Graphics/Player34.png");
	Sprite[35] = IMG_LoadTexture(renderer, "Graphics/Player35.png");
	Sprite[36] = IMG_LoadTexture(renderer, "Graphics/Player36.png");
	Sprite[37] = IMG_LoadTexture(renderer, "Graphics/Player37.png");
	Sprite[38] = IMG_LoadTexture(renderer, "Graphics/Player38.png");
	Sprite[39] = IMG_LoadTexture(renderer, "Graphics/Player39.png");
	Sprite[40] = IMG_LoadTexture(renderer, "Graphics/Player40.png");
	Sprite[41] = IMG_LoadTexture(renderer, "Graphics/Player41.png");
	Sprite[42] = IMG_LoadTexture(renderer, "Graphics/Player42.png");
	Sprite[43] = IMG_LoadTexture(renderer, "Graphics/Player43.png");
	Sprite[44] = IMG_LoadTexture(renderer, "Graphics/Player44.png");
	Sprite[45] = IMG_LoadTexture(renderer, "Graphics/Player45.png");
	Sprite[46] = IMG_LoadTexture(renderer, "Graphics/Player46.png");
	Sprite[47] = IMG_LoadTexture(renderer, "Graphics/Player47.png");
	Sprite[48] = IMG_LoadTexture(renderer, "Graphics/Player48.png");
	Sprite[49] = IMG_LoadTexture(renderer, "Graphics/Player49.png");
	Sprite[50] = IMG_LoadTexture(renderer, "Graphics/Player50.png");
	Sprite[51] = IMG_LoadTexture(renderer, "Graphics/Player51.png");
	Sprite[52] = IMG_LoadTexture(renderer, "Graphics/Player52.png");
	Sprite[53] = IMG_LoadTexture(renderer, "Graphics/Player53.png");
	Sprite[54] = IMG_LoadTexture(renderer, "Graphics/Player54.png");
	Sprite[55] = IMG_LoadTexture(renderer, "Graphics/Player55.png");
	Sprite[56] = IMG_LoadTexture(renderer, "Graphics/Player56.png");
	Sprite[57] = IMG_LoadTexture(renderer, "Graphics/Player57.png");
	Sprite[58] = IMG_LoadTexture(renderer, "Graphics/Player58.png");
	Sprite[59] = IMG_LoadTexture(renderer, "Graphics/Player59.png");
	Sprite[60] = IMG_LoadTexture(renderer, "Graphics/Player60.png");
	Sprite[61] = IMG_LoadTexture(renderer, "Graphics/Player61.png");

	Rect.x = 475;
	Rect.y = 195; 
	Rect.w = 45;
	Rect.h = 65;

	PositionRect.x = Rect.x;
	PositionRect.y = Rect.y;

	VelocityCapX = 30; 
	VelocityCapY = 50;

	GravityValue = 2;

	Jumping = false;
	JumpValue = -30;

	currentSprite = 0;
	Direction = 0;
	PrevDirection = 1;
	MoveSpeed = 8;

	MoveSpriteCount = 0;
	MoveLimit = 4;
	MoveCounter = MoveLimit;

	GravityReset = false;
	JumpReset = false;

	Lives = 3;
	Hit = false;
	Dead = false;
	Immune = false;
	ImmuneCount = 0;
	ImmuneLimit = 8;
	ImmuneAlphaCount = 0;
	AlphaValue = 255;
}


CSprite::~CSprite()
{

}

void CSprite::Draw()
{
	SDL_QueryTexture(Sprite[currentSprite], NULL, NULL, &Width, &Height);
	PositionRect.w = Width;
	PositionRect.h = Height;
	
	if (PrevDirection == 1)
	{
		PositionRect.x = Rect.x;
		if (currentSprite == 48)
			PositionRect.x = Rect.x - 35;
		if (currentSprite == 49)
			PositionRect.x = Rect.x - 40;
		if (currentSprite == 51)
			PositionRect.x = Rect.x - 10;
		if (currentSprite == 52)
			PositionRect.x = Rect.x - 10;
		if (currentSprite == 53)
			PositionRect.x = Rect.x - 10;
	}
	if (PrevDirection == 2)
	{
		PositionRect.x = Rect.x + Rect.w - Width;
		if (currentSprite == 54)
			PositionRect.x = Rect.x + Rect.w - Width + 35;
		if (currentSprite == 55)
			PositionRect.x = Rect.x + Rect.w - Width + 40;
		if (currentSprite == 57)
			PositionRect.x = Rect.x + Rect.w - Width + 10;
		if (currentSprite == 58)
			PositionRect.x = Rect.x + Rect.w - Width + 10;
		if (currentSprite == 59)
			PositionRect.x = Rect.x + Rect.w - Width + 10;
	}

	if (currentSprite == 50 || currentSprite == 56)
		PositionRect.y = Rect.y - 20;
	else
		PositionRect.y = Rect.y;

	SDL_SetTextureBlendMode(Sprite[currentSprite], SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(Sprite[currentSprite], AlphaValue);

	SDL_RenderCopy(renderer, Sprite[currentSprite], NULL, &PositionRect);
}

void CSprite::Update()
{
	//HANDLE MOVEMENT
	if (!Jumping)
		Falling = true;

	Gravity();

	if (Hit)
	{
		Hit = false;
		if (!Immune)
		{
			Immune = true;
			Lives--;
		}
	}

	if (Immune)
	{
		if (ImmuneAlphaCount >= 1 && ImmuneAlphaCount < 5)
			AlphaValue -= 5;
		if (ImmuneAlphaCount >= 5 && ImmuneAlphaCount < 9)
			AlphaValue += 5;
		if (ImmuneAlphaCount >= 9 && ImmuneAlphaCount < 13)
			AlphaValue -= 5;
		if (ImmuneAlphaCount >= 13 && ImmuneAlphaCount < 17)
			AlphaValue += 5;
		if (ImmuneAlphaCount >= 17 && ImmuneAlphaCount < 21)
			AlphaValue -= 5;
		if (ImmuneAlphaCount >= 21 && ImmuneAlphaCount < 25)
			AlphaValue += 5;
		if (ImmuneAlphaCount == 25)
		{
			ImmuneAlphaCount = 0;
			Immune = false;
		}

		ImmuneCount++;
		if (ImmuneCount == ImmuneLimit)
		{
			ImmuneCount = 0;			
			ImmuneAlphaCount++;
		}
	}

	if (Lives < 0)
		Dead = true;
	else
		Dead = false;

	if (Direction != 0)
		PrevDirection = Direction;

	if (Direction == 0)
	{
		VelocityX = 0;
		MoveCounter = MoveLimit;
		MoveSpriteCount = 0;
		if (!Jumping)
		{
			if (PrevDirection == 1)
				currentSprite = 0;
			if (PrevDirection == 2)
				currentSprite = 9;
		}
	}

	if (Jumping)
	{
		JumpLimit = 3;
		JumpCounter++;
		if (JumpCounter == JumpLimit && JumpSpriteCount != -1)
		{
			JumpCounter = 0;
			JumpSpriteCount++;
			if (JumpSpriteCount == 1)
			{
				if (PrevDirection == 1)
					currentSprite = 18;
				if (PrevDirection == 2)
					currentSprite = 25;
			}
			if (JumpSpriteCount == 2)
			{
				if (PrevDirection == 1)
					currentSprite = 19;
				if (PrevDirection == 2)
					currentSprite = 26;
			}
			if (JumpSpriteCount == 3)
			{
				if (PrevDirection == 1)
					currentSprite = 20;
				if (PrevDirection == 2)
					currentSprite = 27;
			}
			if (JumpSpriteCount == 4)
			{
				if (PrevDirection == 1)
					currentSprite = 21;
				if (PrevDirection == 2)
					currentSprite = 28;
			}
			if (JumpSpriteCount == 5)
			{
				if (PrevDirection == 1)
					currentSprite = 22;
				if (PrevDirection == 2)
					currentSprite = 29;
			}
			if (JumpSpriteCount == 6)
			{
				if (PrevDirection == 1)
					currentSprite = 23;
				if (PrevDirection == 2)
					currentSprite = 30;
			}
			if (JumpSpriteCount == 7)
			{
				if (PrevDirection == 1)
					currentSprite = 24;
				if (PrevDirection == 2)
					currentSprite = 31;
			}
			if (JumpSpriteCount == 8)
			{
				if (PrevDirection == 1)
					currentSprite = 60;
				if (PrevDirection == 2)
					currentSprite = 61;
				JumpSpriteCount = -1;
			}
		}
	}
	else
	{
		JumpCounter = 0;
		JumpSpriteCount = 0;
	}

	if (Direction == 1)
	{
		VelocityX = MoveSpeed;
		if (!Jumping && !Falling)
		{
			if (MoveCounter == MoveLimit)
			{
				MoveCounter = 0;
				MoveSpriteCount++;
				if (MoveSpriteCount == 1)
					currentSprite = 1;
				if (MoveSpriteCount == 2)
					currentSprite = 2;
				if (MoveSpriteCount == 3)
					currentSprite = 3;
				if (MoveSpriteCount == 4)
					currentSprite = 4;
				if (MoveSpriteCount == 5)
					currentSprite = 5;
				if (MoveSpriteCount == 6)
					currentSprite = 6;
				if (MoveSpriteCount == 7)
					currentSprite = 7;
				if (MoveSpriteCount == 8)
				{
					currentSprite = 8;
					MoveSpriteCount = 0;
				}
			}
			MoveCounter++;
		}
	}
	if (Direction == 2)
	{
		VelocityX = -MoveSpeed;
		if (!Jumping && !Falling)
		{
			if (MoveCounter == MoveLimit)
			{
				MoveCounter = 0;
				MoveSpriteCount++;
				if (MoveSpriteCount == 1)
					currentSprite = 10;
				if (MoveSpriteCount == 2)
					currentSprite = 11;
				if (MoveSpriteCount == 3)
					currentSprite = 12;
				if (MoveSpriteCount == 4)
					currentSprite = 13;
				if (MoveSpriteCount == 5)
					currentSprite = 14;
				if (MoveSpriteCount == 6)
					currentSprite = 15;
				if (MoveSpriteCount == 7)
					currentSprite = 16;
				if (MoveSpriteCount == 8)
				{
					currentSprite = 17;
					MoveSpriteCount = 0;
				}
			}
			MoveCounter++;
		}
	}

	if (Falling)
	{
		if (PrevDirection == 1)
			currentSprite = 60;
		if (PrevDirection == 2)
			currentSprite = 61;
	}
	Direction = 0;

	//CAP VELOCITIES
	if (VelocityX > VelocityCapX)
		VelocityX = VelocityCapX;
	if (VelocityX < -VelocityCapX)
		VelocityX = -VelocityCapX;

	if (VelocityY > VelocityCapY)
		VelocityY = VelocityCapY;

}

void CSprite::Gravity()
{
	if (GravityReset)
	{ //When the player lands on top of a block
		Falling = false;
		GravityReset = false;
		Jumping = false;
		VelocityY = 0;
	}
	if (JumpReset)
	{ //When the player hits the bottom of a block
		JumpReset = false;
		VelocityY = 0;
	}
	VelocityY += GravityValue;
}

void CSprite::Jump(int newJumpValue)
{	
	if (!Jumping && !Falling)
	{
 		Jumping = true;
		GravityReset = false;
		VelocityY = newJumpValue;
	}
}

bool CSprite::GetImmune()
{
	return Immune;
}

void CSprite::SetImmune(bool newImmune)
{
	Immune = newImmune;
}

bool CSprite::GetJumping()
{
	return Jumping;
}

void CSprite::SetJumping(bool newJumping)
{
	Jumping = newJumping;
}

bool CSprite::GetHit()
{
	return Hit;
}

void CSprite::SetHit(bool newHit)
{
	Hit = newHit;
}

int CSprite::GetLives()
{
	return Lives;
}

void CSprite::SetLives(bool newLives)
{
	Lives = newLives;
}

int CSprite::GetX()
{
	return Rect.x;
}

void CSprite::SetX(int newX)
{
	Rect.x = newX;
}

int CSprite::GetY()
{
	return Rect.y;
}

void CSprite::SetY(int newY)
{
	Rect.y = newY;
}

int CSprite::GetXVel()
{
	return VelocityX;
}

void CSprite::SetXVel(int newX)
{
	VelocityX = newX;
}

int CSprite::GetYVel()
{
	return VelocityY;
}

void CSprite::SetYVel(int newY)
{
	VelocityY = newY;
}

SDL_Rect CSprite::GetRect()
{
	return Rect;
}

void CSprite::SetRect(SDL_Rect  newRect)
{
	Rect = newRect;
}

int CSprite::GetDirection()
{
	return Direction;
}

void CSprite::SetDirection(int newDirection)
{
	Direction = newDirection;
}

void CSprite::SetPrevDirection(int newPrevDirection)
{
	PrevDirection = newPrevDirection;
}

int CSprite::GetPrevDirection()
{
	return PrevDirection;
}


void CSprite::SetGravityReset(bool newReset)
{
	GravityReset = newReset;
}

void CSprite::SetJumpReset(bool newReset)
{
	JumpReset = newReset;
}