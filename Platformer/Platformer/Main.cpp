#include "stdafx.h"
#include "Main.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>

CMain::CMain()
{
	csdl_setup = new CSDL_Setup(&quit);
	Keys = SDL_GetKeyboardState(NULL);
	quit = false;
	Direction = 0;
	GravityReset = false;
	JumpReset = false;
	SetJumping = false;
	timeCheck = SDL_GetTicks();
	KeyPressed = false;
	FallAmount = 0;
	OnMoveBlock = false;
	BlockSelected = 8;
	FPS = 75;

	for (int i = 0; i < 100; i++)
	{
		Coin[i] = new CCoin(csdl_setup->GetRenderer());
	}

	for (int i = 0; i < 50; i++)
	{
		Koopa[i] = new CEnemy(csdl_setup->GetRenderer());
		Goomba[i] = new CEnemy2(csdl_setup->GetRenderer());
	}

	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			mainGrid[i][j] = { i * 40, j * 40, 40, 40 };
			PrevMainGrid[i][j] = mainGrid[i][j];
			baseBlock[i][j] = new CBlock(csdl_setup->GetRenderer());
			baseBlock[i][j]->SetRect(mainGrid[i][j]);
		}
	}

	std::ifstream mapFile;
	mapFile.open("Graphics/Map.txt");

	int y = 0;
	std::string Line;

	while (std::getline(mapFile, Line))
	{
		for (int i = 0; i < Line.length(); i++)
			baseBlock[i][y]->SetType(Line[i]);

		y++;
	}
	mapFile.close();

	Man = new CSprite(csdl_setup->GetRenderer());
	Arrow = new CArrow(csdl_setup->GetRenderer());

	MapReset();
}

CMain::~CMain()
{

}

void CMain::MapReset()
{
	for (int k = 0; k < 50; k++)
	{
		Goomba[k]->SetActive(false);
		Koopa[k]->SetActive(false);
	}

	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			mainGrid[i][j] = { i * 40, j * 40, 40, 40 };
			baseBlock[i][j]->SetRect(mainGrid[i][j]);
			mainGrid[i][j].x -= 20;
			mainGrid[i][j].y -= 1300;
			baseBlock[i][j]->SetRect({ baseBlock[i][j]->GetRect().x - 20, baseBlock[i][j]->GetRect().y - 1300, baseBlock[i][j]->GetRect().w, baseBlock[i][j]->GetRect().h });
		}
	}

	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			if (baseBlock[i][j]->GetType() == 'C')
			{
				for (int k = 0; k < 50; k++)
				{
					if (!Goomba[k]->GetActive())
					{
						Goomba[k]->Spawn(baseBlock[i][j]->GetRect().x, baseBlock[i][j]->GetRect().y - 50);
						break;
					}
				}
			}
			if (baseBlock[i][j]->GetType() == 'D')
			{
				for (int k = 0; k < 50; k++)
				{
					if (!Koopa[k]->GetActive())
					{
						Koopa[k]->Spawn(baseBlock[i][j]->GetRect().x, baseBlock[i][j]->GetRect().y - 50);
						break;
					}
				}
			}
		}
	}
}

void CMain::Inputs()
{
	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{
		if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE)
			SDL_QUIT;

		if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SPACE && KeyPressed == false)
		{
			Man->Jump(-30);
			KeyPressed = true;
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
	{
		if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_SPACE)
			KeyPressed = false;
	}

	if (Keys[SDL_SCANCODE_1])
		BlockSelected = 1;
	if (Keys[SDL_SCANCODE_2])
		BlockSelected = 2;
	if (Keys[SDL_SCANCODE_3])
		BlockSelected = 3;
	if (Keys[SDL_SCANCODE_4])
		BlockSelected = 4;
	if (Keys[SDL_SCANCODE_5])
		BlockSelected = 5;
	if (Keys[SDL_SCANCODE_6])
		BlockSelected = 6;
	if (Keys[SDL_SCANCODE_7])
		BlockSelected = 7;
	if (Keys[SDL_SCANCODE_8])
		BlockSelected = 8;
	if (Keys[SDL_SCANCODE_9])
		BlockSelected = 9;

	// Handles movement keys
	if (Keys[SDL_SCANCODE_D])
	{
		Man->SetDirection(1);
	}
	if (Keys[SDL_SCANCODE_A])
	{
		Man->SetDirection(2);
	}

	// Handles ability keys
	int MouseX = (csdl_setup->GetMainEvent()->button.x - baseBlock[0][0]->GetRect().x) / 40;
	int MouseY = (csdl_setup->GetMainEvent()->button.y - baseBlock[0][0]->GetRect().y) / 40;
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
	{

	}

	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONUP)
	{

	}
}

void CMain::Collision()
{
	GravityReset = false;
	JumpReset = false;

	//HANDLE COLLISION AND MOVEMENT
	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			if (baseBlock[i][j]->GetType() != '0' && baseBlock[i][j]->GetType() != 'C' && baseBlock[i][j]->GetType() != 'D')
			{
				ChangeAmount = { CharacterBlockCollision(baseBlock[i][j]->GetPrevRect(), baseBlock[i][j]->GetRect(), Man->GetRect(), Man->GetRect()) };

				if (ChangeAmount.x != 0 || ChangeAmount.y != 0)
				{
					if (baseBlock[i][j]->GetType() == 'A' || baseBlock[i][j]->GetType() == 'B')
						MapReset();

					for (int k = 0; k < GridX; k++)
					{
						for (int l = 0; l < GridY; l++)
						{
							mainGrid[k][l].x += ChangeAmount.x;
							mainGrid[k][l].y += ChangeAmount.y;
							baseBlock[k][l]->SetRect({ baseBlock[k][l]->GetRect().x + ChangeAmount.x, baseBlock[k][l]->GetRect().y + ChangeAmount.y, baseBlock[k][l]->GetRect().w, baseBlock[k][l]->GetRect().h });
						}
					}
					for (int i = 0; i < 50; i++)
					{
						if (Koopa[i]->GetActive())
							Koopa[i]->SetRect({ Koopa[i]->GetRect().x + ChangeAmount.x, Koopa[i]->GetRect().y + ChangeAmount.y, Koopa[i]->GetRect().w, Koopa[i]->GetRect().h });
						if (Goomba[i]->GetActive())
							Goomba[i]->SetRect({ Goomba[i]->GetRect().x + ChangeAmount.x, Goomba[i]->GetRect().y + ChangeAmount.y, Goomba[i]->GetRect().w, Goomba[i]->GetRect().h });
					}
					for (int i = 0; i < 100; i++)
					{
						if (Coin[i]->GetActive())
							Coin[i]->SetRect({ Coin[i]->GetRect().x + ChangeAmount.x, Coin[i]->GetRect().y + ChangeAmount.y, Coin[i]->GetRect().w, Coin[i]->GetRect().h });
					}
				}

				if (GravityReset)
					Man->SetGravityReset(GravityReset);
				if (JumpReset)
					Man->SetJumpReset(JumpReset);

				JumpReset = false;
				GravityReset = false;

				if (Man->GetRect().y == baseBlock[i][j]->GetRect().y + baseBlock[i][j]->GetRect().h)
				{
					if (Man->GetRect().x + Man->GetRect().w > baseBlock[i][j]->GetRect().x && Man->GetRect().x < baseBlock[i][j]->GetRect().x + baseBlock[i][j]->GetRect().w)
					{
						if (baseBlock[i][j]->GetType() == '8')
						{
							baseBlock[i][j]->SetType('9');
							for (int k = 0; k < 100; k++)
							{
								if (!Coin[k]->GetActive())
								{
									Coin[k]->Spawn(baseBlock[i][j]->GetRect().x + 3, baseBlock[i][j]->GetRect().y);
									break;
								}
							}
						}
					}
				}



				//COLLISION BETWEEN GRID AND Koopa
				for (int k = 0; k < 50; k++)
				{
					if (Koopa[k]->GetActive() && !Koopa[k]->GetKilled())
					{
						ChangeAmount = { CharacterBlockCollision(Koopa[k]->GetPrevRect(), Koopa[k]->GetRect(), baseBlock[i][j]->GetPrevRect(), baseBlock[i][j]->GetRect()) };

						if (ChangeAmount.x != 0 || ChangeAmount.y != 0)
							Koopa[k]->SetRect({ Koopa[k]->GetRect().x + ChangeAmount.x, Koopa[k]->GetRect().y + ChangeAmount.y, Koopa[k]->GetRect().w, Koopa[k]->GetRect().h });

						if (JumpReset)
							Koopa[k]->SetGravityReset(true);

						JumpReset = false;

						if (ChangeAmount.x > 2 || ChangeAmount.x < -2)
						{
							if (Koopa[k]->GetDirection() != 0)
							{
								if (Koopa[k]->GetPrevDirection() == 1)
									Koopa[k]->SetDirection(2);
								if (Koopa[k]->GetPrevDirection() == 2)
									Koopa[k]->SetDirection(1);
							}
						}

						if (ChangeAmount.y < 0 && !Koopa[k]->GetInShell())
						{
							if (Koopa[k]->GetDirection() == 1)
							{
								if (baseBlock[i + 1][j]->GetType() == '0' && baseBlock[i + 2][j]->GetType() == '0')
								{
									if (Koopa[k]->GetRect().x + Koopa[k]->GetRect().w > baseBlock[i + 1][j]->GetRect().x)
									{
										Koopa[k]->SetDirection(2);
										Koopa[k]->SetRect({ baseBlock[i + 1][j]->GetRect().x - Koopa[k]->GetRect().w, Koopa[k]->GetRect().y, Koopa[k]->GetRect().w, Koopa[k]->GetRect().h });
									}
								}
							}
							if (Koopa[k]->GetDirection() == 2)
							{
								if (baseBlock[i - 1][j]->GetType() == '0' && baseBlock[i - 2][j]->GetType() == '0')
								{
									if (Koopa[k]->GetRect().x < baseBlock[i - 1][j]->GetRect().x + baseBlock[i - 1][j]->GetRect().w)
									{
										Koopa[k]->SetDirection(1);
										Koopa[k]->SetRect({ baseBlock[i - 1][j]->GetRect().x + baseBlock[i - 1][j]->GetRect().w, Koopa[k]->GetRect().y, Koopa[k]->GetRect().w, Koopa[k]->GetRect().h });
									}
								}
							}
						}
					}

					if (Goomba[k]->GetActive() && !Goomba[k]->GetKilled())
					{
						ChangeAmount = { CharacterBlockCollision(Goomba[k]->GetPrevRect(), Goomba[k]->GetRect(), baseBlock[i][j]->GetPrevRect(), baseBlock[i][j]->GetRect()) };

						if (ChangeAmount.x != 0 || ChangeAmount.y != 0)
							Goomba[k]->SetRect({ Goomba[k]->GetRect().x + ChangeAmount.x, Goomba[k]->GetRect().y + ChangeAmount.y, Goomba[k]->GetRect().w, Goomba[k]->GetRect().h });

						if (ChangeAmount.x > 2 || ChangeAmount.x < -2)
						{
							if (Goomba[k]->GetDirection() != 0)
							{
								if (Goomba[k]->GetPrevDirection() == 1)
									Goomba[k]->SetDirection(2);
								if (Goomba[k]->GetPrevDirection() == 2)
									Goomba[k]->SetDirection(1);
							}
						}

						if (JumpReset)
							Goomba[k]->SetGravityReset(true);

						JumpReset = false;

						if (ChangeAmount.y < 0)
						{
							if (Goomba[k]->GetDirection() == 1)
							{
								if (baseBlock[i + 1][j]->GetType() == '0' && baseBlock[i + 2][j]->GetType() == '0')
								{
									if (Goomba[k]->GetRect().x + Goomba[k]->GetRect().w > baseBlock[i + 1][j]->GetRect().x)
									{
										Goomba[k]->SetDirection(2);
										Goomba[k]->SetRect({ baseBlock[i + 1][j]->GetRect().x - Goomba[k]->GetRect().w, Goomba[k]->GetRect().y, Goomba[k]->GetRect().w, Goomba[k]->GetRect().h });
									}
								}
							}
							if (Goomba[k]->GetDirection() == 2)
							{
								if (baseBlock[i - 1][j]->GetType() == '0' && baseBlock[i - 2][j]->GetType() == '0')
								{
									if (Goomba[k]->GetRect().x < baseBlock[i - 1][j]->GetRect().x + baseBlock[i - 1][j]->GetRect().w)
									{
										Goomba[k]->SetDirection(1);
										Goomba[k]->SetRect({ baseBlock[i - 1][j]->GetRect().x + baseBlock[i - 1][j]->GetRect().w, Goomba[k]->GetRect().y, Goomba[k]->GetRect().w, Goomba[k]->GetRect().h });
									}
								}
							}
						}
					}
				}


			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (Man->GetRect().x + Man->GetRect().w > Coin[i]->GetRect().x && Man->GetRect().x < Coin[i]->GetRect().x + Coin[i]->GetRect().w)
		{
			if (Man->GetRect().y + Man->GetRect().h > Coin[i]->GetRect().y && Man->GetRect().y < Coin[i]->GetRect().y + Coin[i]->GetRect().h)
				Coin[i]->SetActive(false);
		}
	}

	for (int i = 0; i < 50; i++)
	{
		if (Koopa[i]->GetActive())
		{
			ChangeAmount = { CharacterBlockCollision(Koopa[i]->GetPrevRect(), Koopa[i]->GetRect(), Man->GetRect(), Man->GetRect()) };

			if (ChangeAmount.y > 0)
			{
				if (!Koopa[i]->GetInShell() && Man->GetYVel() > 0)
				{
					Man->SetJumping(false);
					Man->Jump(-20);
					Koopa[i]->SetInShell(true);
					Koopa[i]->SetDirection(0);
					Koopa[i]->SetRect({ Koopa[i]->GetRect().x, Koopa[i]->GetRect().y + 30, Koopa[i]->GetRect().w, Koopa[i]->GetRect().h - 30 });
				}
				if (Koopa[i]->GetInShell() && Koopa[i]->GetDirection() == 0 && Man->GetYVel() > 0)
				{
					Man->SetJumping(false);
					Man->Jump(-15);
					Koopa[i]->SetDirection(Koopa[i]->GetPrevDirection());
				}
				if (Koopa[i]->GetInShell() && !Koopa[i]->GetDirection() == 0 && Man->GetYVel() > 0 && !Koopa[i]->GetKilled())
				{
					Man->SetJumping(false);
					Man->Jump(-10);
					Koopa[i]->SetKilled(true);
					Koopa[i]->SetYVel(-10);
				}
			}

			if (ChangeAmount.x != 0 || ChangeAmount.y < 0)
				Man->SetHit(true);
		}

		if (Goomba[i]->GetActive())
		{
			ChangeAmount = { CharacterBlockCollision(Goomba[i]->GetPrevRect(), Goomba[i]->GetRect(), Man->GetRect(), Man->GetRect()) };

			if (ChangeAmount.y > 0)
			{
				if (Man->GetYVel() > 0)
				{
					Man->SetJumping(false);
					Man->Jump(-10);
					Goomba[i]->SetKilled(true);
				}
			}

			if (ChangeAmount.x != 0 || ChangeAmount.y < 0)
				Man->SetHit(true);
		}
	}
}

void CMain::Update()
{
	if (Man->GetLives() < 0)
	{
		MapReset();
		Man->SetLives(3);
	}

	if (baseBlock[0][GridY - 1]->GetRect().y < 100)
		MapReset();

	Man->Update();

	for (int i = 0; i < 50; i++)
	{
		if (Koopa[i]->GetActive())
			Koopa[i]->Update();
		if (Goomba[i]->GetActive())
			Goomba[i]->Update();
	}

	for (int i = 0; i < 100; i++)
	{
		Coin[i]->Update();
	}

	//UPDATE MAP BASED ON PLAYERS VELOCITY	
	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			baseBlock[i][j]->Update();
			mainGrid[i][j].x -= Man->GetXVel();
			mainGrid[i][j].y -= Man->GetYVel();
			baseBlock[i][j]->SetRect({ baseBlock[i][j]->GetRect().x - Man->GetXVel(), baseBlock[i][j]->GetRect().y - Man->GetYVel(), baseBlock[i][j]->GetRect().w, baseBlock[i][j]->GetRect().h });
		}
	}

	for (int i = 0; i < 50; i++)
	{
		if (Koopa[i]->GetActive())
			Koopa[i]->SetRect({ Koopa[i]->GetRect().x - Man->GetXVel(), Koopa[i]->GetRect().y - Man->GetYVel(), Koopa[i]->GetRect().w, Koopa[i]->GetRect().h });
		if (Goomba[i]->GetActive())
			Goomba[i]->SetRect({ Goomba[i]->GetRect().x - Man->GetXVel(), Goomba[i]->GetRect().y - Man->GetYVel(), Goomba[i]->GetRect().w, Goomba[i]->GetRect().h });
	}
	for (int i = 0; i < 100; i++)
	{
		if (Coin[i]->GetActive())
			Coin[i]->SetRect({ Coin[i]->GetRect().x - Man->GetXVel(), Coin[i]->GetRect().y - Man->GetYVel(), Coin[i]->GetRect().w, Coin[i]->GetRect().h });
	}

	Collision();
}

void CMain::Draw()
{
	csdl_setup->Begin();

	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			if (baseBlock[i][j]->GetType() == '0')
				baseBlock[i][j]->Draw();
		}
	}

	for (int i = 0; i < 100; i++)
		Coin[i]->Draw();

	for (int i = 0; i < GridX; i++)
	{
		for (int j = 0; j < GridY; j++)
		{
			if (baseBlock[i][j]->GetType() != '0')
				baseBlock[i][j]->Draw();
		}
	}

	for (int i = 0; i < 50; i++)
	{
		Koopa[i]->Draw();
		Goomba[i]->Draw();
	}


	Man->Draw();

	csdl_setup->End();
}

void CMain::GameLoop(void)
{
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		timeCheck = SDL_GetTicks();

		//INPUTS
		Inputs();

		//UPDATE
		Update();

		//DRAW
		Draw();

		if (((1000 / FPS) > SDL_GetTicks() - timeCheck))
		{
			int delay = (1000 / FPS) - (SDL_GetTicks() - timeCheck);
			SDL_Delay(delay);
		}
	}
}

SDL_Rect CMain::CharacterBlockCollision(SDL_Rect PrevBlockRect, SDL_Rect BlockRect, SDL_Rect PrevCharRect, SDL_Rect CharRect)
{
	int ChangeX = 0;
	int ChangeY = 0;
	// Check to see if the Player has collided with a block
	if (BlockRect.x + BlockRect.w >= CharRect.x && BlockRect.x <= CharRect.x + CharRect.w)
	{
		if (BlockRect.y + BlockRect.h >= CharRect.y && BlockRect.y <= CharRect.y + CharRect.h)
		{
			if (PrevBlockRect.x >= PrevCharRect.x + PrevCharRect.w)
			{ // Player colliding with a block to the left of them
				if (PrevBlockRect.y >= PrevCharRect.y + PrevCharRect.h)
				{ // The block was above the player before collision
					if (CharRect.x + CharRect.w - BlockRect.x < CharRect.y + CharRect.h - BlockRect.y)
					{ // Push the player out to the right
						ChangeX = (CharRect.x + CharRect.w) - BlockRect.x;
					}
					if (CharRect.x + CharRect.w - BlockRect.x > CharRect.y + CharRect.h - BlockRect.y)
					{ // Push the player out upwards
						ChangeY = CharRect.y + CharRect.h - BlockRect.y;
					}
				}
				if (PrevBlockRect.y + PrevBlockRect.h > PrevCharRect.y && PrevBlockRect.y < PrevCharRect.y + PrevCharRect.h)
				{ // The block was within the same y boundaries as the player
					//Push the player out to the right
					ChangeX = (CharRect.x + CharRect.w) - BlockRect.x;
				}
				if (PrevBlockRect.y + PrevBlockRect.h <= PrevCharRect.y)
				{ // The block was below the player before collision
					if (CharRect.x + CharRect.w - BlockRect.x < BlockRect.y + BlockRect.h - CharRect.y)
					{ // Push the player out to the right
						ChangeX = (CharRect.x + CharRect.w) - BlockRect.x;
					}
					if (CharRect.x + CharRect.w - BlockRect.x > BlockRect.y + BlockRect.h - CharRect.y)
					{ // Push the player out upwards
						ChangeY = CharRect.y - (BlockRect.y + BlockRect.h);
					}
				}
			}
			////--------------------------------------------------------------------------------------------
			if (PrevBlockRect.x + PrevBlockRect.w <= PrevCharRect.x)
			{ // Player colliding with a block to the right of them
				if (PrevBlockRect.y >= PrevCharRect.y + PrevCharRect.h)
				{ // The block was above the player before collision
					if (BlockRect.x + BlockRect.w - CharRect.x < CharRect.y + CharRect.h - BlockRect.y)
					{ // Push the player out to the left
						ChangeX = CharRect.x - (BlockRect.x + BlockRect.w);
					}
					if (BlockRect.x + BlockRect.w - CharRect.x > CharRect.y + CharRect.h - BlockRect.y)
					{ // Push the player out upwards
						ChangeY = CharRect.y + CharRect.h - BlockRect.y;
					}
				}
				if (PrevBlockRect.y + PrevBlockRect.h > PrevCharRect.y && PrevBlockRect.y < PrevCharRect.y + PrevCharRect.h)
				{ // The block was within the same y boundaries as the player
					// Push the player out to the left
					ChangeX = CharRect.x - (BlockRect.x + BlockRect.w);
				}
				if (PrevBlockRect.y + PrevBlockRect.h <= PrevCharRect.y)
				{ // The block was below the player before collision
					if (BlockRect.x + BlockRect.w - CharRect.x < BlockRect.y + BlockRect.h - CharRect.y)
					{ // Push the player out to the left
						ChangeX = CharRect.x - (BlockRect.x + BlockRect.w);
					}
					if (BlockRect.x + BlockRect.w - CharRect.x > BlockRect.y + BlockRect.h - CharRect.y)
					{ // Push the player out upwards
						ChangeY = CharRect.y - (BlockRect.y + BlockRect.h);
					}
				}
			}
			//--------------------------------------------------------------------------------------------
			if (PrevBlockRect.x + PrevBlockRect.w > PrevCharRect.x && PrevBlockRect.x < PrevCharRect.x + PrevCharRect.w)
			{ // Player colliding with a block with the same x boundaries as the player
				if (PrevBlockRect.y >= PrevCharRect.y + PrevCharRect.h)
				{ // The block was above the player before collision
					// Push the player out downwards
					ChangeY = (CharRect.y + CharRect.h) - BlockRect.y;
					GravityReset = true;
					SetJumping = true;
				}
				if (PrevBlockRect.y + PrevBlockRect.h <= PrevCharRect.y)
				{ // The block was below the player before collision
					// Push the player out upwards
					ChangeY = CharRect.y - (BlockRect.y + BlockRect.h);
					JumpReset = true;
				}
			}
		}
	}
	return{ ChangeX, ChangeY, 0, 0 };
}