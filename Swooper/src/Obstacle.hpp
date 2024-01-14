#ifndef Obstacle_HPP
#define Obstacle_HPP

#include "Entity.hpp"
#include "raylib.h"

//Fix Sprite Drawing
class Obstacle : public Entity {

public:
	Obstacle(const float XCord, const bool Flip);
	void DrawObj();
	void UpdatePos();
	void Resize(const float& InitWidth, const float& InitHeight);
	void UnloadSprite();
	bool ScoredPoint(Entity& Player);
	void Reset();

private:

	//Scale Ratios (For Drawing & Position)
	const float RelativeWidRatio = 64.0 / 500.0;
	const float RelativeHighRatio = 196.0 / 300.0;

	//Range Ratios (For Position)
	const float RelativeMaxX = 750.0 / 500;
	const float RelativeMinX = -64.0 / 500;

	const float RelativeMinYTop = -66.0 / 300.0;
	const float RelativeMaxYTop = 20.0 / 300.0;

	const float RelativeMinYBot = 108.0 / 300.0;
	const float RelativeMaxYBot = 154.0 / 300.0;

	//Movement Ratio
	const float MovementRatio = (-200.0 / 500.0);

	Texture2D Sprite;
	Rectangle Frame;
	Rectangle PosRec;
	int MvSpeed = -220;
	int FlipMod = 0;
	int InitFlipMod = 0; //This Is a Dumb Line & probably Doesnt need to be here, but I dont know why it's Broken
	float InitX;
	bool ShowCollis = false;
	bool PastPlayer = false;

	//Private Functions
	float RandY();
};

//Obstacle Constructor
Obstacle::Obstacle(const float XCord, const bool Flip) {

	if (Flip == true) {
		FlipMod = 1;
		InitFlipMod = 1;
	}

	//Position Setup
	Vector2 Pos;
	Pos.x = XCord;
	Pos.y = RandY();
	InitX = XCord;

	//FrameSetup
	Frame.x = 64 * FlipMod;
	Frame.y = 0;
	Frame.width = 64;
	Frame.height = 192;

	//PosRec Setup
	PosRec.x = Pos.x;
	PosRec.y = Pos.y;
	PosRec.width = 64;
	PosRec.height = 196;

	//MoveSpeed Setup
	//MvSpeed = GetScreenWidth() * MovementRatio;

	Sprite = LoadTexture("GameArt/Obstacle.png");

	EntitySetUp(Pos, PosRec.width, PosRec.height);

}

//Draws Obstacle
void Obstacle::DrawObj() {

	//DrawTextureRec(Sprite, Frame, GetPos(), WHITE);
	DrawTexturePro(Sprite, Frame, PosRec, Vector2{0,0}, 0, WHITE);

	if (ShowCollis == true) {
		DrawCollis();
	}

}

//Updates Obstacle Position
void Obstacle::UpdatePos() {

	float DeltaTime = GetFrameTime();
	int NewYPos;

	//Resets their X pos & Y Pos after leaving Screen
	if (GetPos().x <= GetScreenWidth()*RelativeMinX) {
		
		//Resets Past Player Bool
		PastPlayer = false;

		//Checks if the Obstacle is Upside Down or Rightside Up
		if (FlipMod == 1) {

			Frame.x = 64 * FlipMod;
			//NewYPos = GetRandomValue(GetScreenHeight()*RelativeMinYTop, GetScreenHeight() * RelativeMaxYTop);
			SetPos(GetScreenWidth() * RelativeMaxX, RandY());
			FlipMod = 0;
		}
		else {

			Frame.x = 64 * FlipMod;
			//NewYPos = GetRandomValue(GetScreenHeight() * RelativeMinYBot, GetScreenHeight() * RelativeMaxYBot);
			SetPos(GetScreenWidth() * RelativeMaxX, RandY());
			FlipMod = 1;
		}
	}

	UpdateX(DeltaTime * MvSpeed);
	PosRec.x = GetPos().x;
	PosRec.y = GetPos().y;
}

//Resizes The Obstacle
void Obstacle::Resize(const float& InitWidth, const float& InitHeight){


	//Position Setup
	Vector2 Pos;
	Pos.x = GetScreenWidth() * (GetPos().x / InitWidth);
	Pos.y = GetScreenHeight() * (GetPos().y / InitHeight);

	//PosRecResizing
	PosRec.x = GetScreenWidth() * (GetPos().x / InitWidth);
	PosRec.y = GetScreenHeight() * (GetPos().y / InitHeight);

	PosRec.width = GetScreenWidth() * (PosRec.width / InitWidth);
	PosRec.height = GetScreenHeight() * (PosRec.height / InitHeight);


	EntitySetUp(Pos, PosRec.width, PosRec.height);

	MvSpeed = GetScreenWidth() * (MvSpeed / InitWidth);

}

//Unloads Obstacle Sprite
void Obstacle::UnloadSprite() {
	UnloadTexture(Sprite);
}

bool Obstacle::ScoredPoint(Entity& Player) {
	

	if (PastPlayer == false) {

		if (GetPos().x <= Player.GetPos().x) {

			PastPlayer = true;
			return true;
		}

	}


	return false;
}

//Resets Obstacle
void Obstacle::Reset() {

	float XPos = (InitX / 500) * GetScreenWidth();

	FlipMod = InitFlipMod;
	Frame.x = 64 * FlipMod;

	SetPos(XPos, RandY());


}

//Private Function(s)

//Returns a RandomY Position for
float Obstacle::RandY() {

	float NewY;

	if (FlipMod == 1) {

		NewY = GetRandomValue(GetScreenHeight() * RelativeMinYTop, GetScreenHeight() * RelativeMaxYTop);

	}
	else {

		NewY = GetRandomValue(GetScreenHeight() * RelativeMinYBot, GetScreenHeight() * RelativeMaxYBot);

	}

	return NewY;

}

#endif // !Obstacle_HPP

