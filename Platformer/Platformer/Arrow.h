#pragma once
class CArrow
{
public:
	CArrow(SDL_Renderer* passedRenderer);
	~CArrow();

	void Draw();
	void Update();

	int GetX();
	void SetX(int newX);

	int GetY();
	void SetY(int newY);

	bool GetFire();
	void SetFire(bool newFire);

	void SetVectorX(float newVector);
	void SetVectorY(float newVector);

private:
	SDL_Texture* Sprite;
	SDL_Rect Rect;

	SDL_Renderer* renderer;

	float VelocityX;
	float VelocityY;
	bool Fire;
	int Angle;
	float MouseVectorX;
	float MouseVectorY;
	int GravityValue;
};

