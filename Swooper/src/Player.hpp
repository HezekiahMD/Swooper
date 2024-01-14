#ifndef Player_HPP
#define Player_HPP


#include "Entity.hpp"
#include "raylib.h"
#include "Obstacle.hpp"
//#include <iostream>

class Player : public Entity {
public:
	Player(const float& XCord, const float& YCord);
	void TakeInput();
	void DrawPlayer();
	bool ObjCollisCheck(const Obstacle& Obj);
	bool GetIsDead();
	bool GetEndGame();
	void SetEndState(const bool& GS);
	void SetIsDead(const bool& State);
	void Resize(const float& InitWidth, const float& InitHeight);
	void Reset();
	void UnloadSprite();
	bool IsOutBounds();

private:

	//Player DeathVars
	bool IsDead = true;
	bool EndGame = true;
	const float EndGamePosRatio = (360.0 / 300.0);
	float EndGamePos = 360;

	//Scale Ratios (For Drawing & Position)
	const float RelativeWidRatio = 32.0 / 500.0;
	const float RelativeHighRatio = 32.0 / 300.0;

	//Acceleration Ratios
	const float RelativeYAccel = (8.0 / 300.0);
	const float RelativeDeathRotAccel = (384.0 / 300.0);

	//Max & Min Y Pos Ratios
	const float MinYPosRatio = (28.0 / 300.0);
	const float MaxYPosRatio = (272.0 / 300.0);

	//Max & Min Y Pos;
	float MinYPos = 28;
	float MaxYPos = 272;

	//Rendering Vas
	bool ShowCollis = false;
	Texture2D Sprite;
	Rectangle Frame;
	Rectangle PosRec;

	//Y Motion Vars
	float YAccel = 8;
	float YVelocity = 0;

	//rotation Vars
	Vector2 RotPoint = { 16,16 };
	float Rotation = 0;
	float RotAcell = 30;
	float DeatRotAcell = 384;
	const float MaxRot = 30;

	//RotationPoint Ratios
	const float RotPointXRatio = (16.0 / 500.0);
	const float RotPointYRatio = (16.0 / 300.0);

	//StartingPos
	Vector2 InitPos;

	//functions
	void DeathAnim(); //Makes the Player Death animation happen
};

//Constructor
Player::Player(const float& XCord, const float& YCord) {

//Setting up Frame
	Frame.x = 0;
	Frame.y = 0;
	Frame.width = 32;
	Frame.height = 32;

//Setting Up PositionRect
	PosRec.x = XCord;
	PosRec.y = YCord;
	PosRec.width = 32;
	PosRec.height = 32;

//Setting Up Position
	InitPos.x = XCord;
	InitPos.y = YCord;

//Setting up EntityStuffs
	EntitySetUp(InitPos, 32, 16);
	SetCollisOffset(-16.0, -8.0);

//Loading Sprite
	Sprite = LoadTexture("GameArt/SwooperPH.png");
}

//Misc

//Takes Player Input
void Player::TakeInput() {

	if (IsDead == true) {
		DeathAnim();
		return;
	}


	float DeltaTime = GetFrameTime();

//Input Handling
	if (IsKeyDown(KEY_SPACE)|| IsMouseButtonDown(MOUSE_BUTTON_LEFT)){

		YVelocity += YAccel;
		Rotation += RotAcell * DeltaTime;
		UpdateY(YVelocity * DeltaTime);
	}
	else {

		YVelocity -= YAccel;
		Rotation -= RotAcell * DeltaTime;
		UpdateY(YVelocity * DeltaTime);
	}

//Rotation Max;
	if (Rotation > MaxRot) {
		Rotation = MaxRot;
	}
	else if (Rotation < -1*MaxRot) {
		Rotation = -1 * MaxRot;
	}

	PosRec.y = GetPos().y;

}

//Draws the Player
void Player::DrawPlayer() {

	DrawTexturePro(Sprite, Frame, PosRec, RotPoint, Rotation, WHITE);

	if (ShowCollis == true) {
		DrawCollis();
	}

}

//Checks if Player Collided with an Obstacle
bool Player::ObjCollisCheck(const Obstacle& Obj) {

	if (CollisCheck(Obj) == true && IsDead == false) {
		IsDead = true;
		return true;
	}

	return false;
}

//Resets Player Position
void Player::Reset() {

	float XPos = (InitPos.x / 500.0) * GetScreenWidth();
	float YPos = (InitPos.y / 300.0) * GetScreenHeight();
	SetPos(XPos, YPos);
	EndGame = false;
	IsDead = false;
	Rotation = 0;
	YVelocity = 0;

}


//Unloads Player Sprite
void Player::UnloadSprite() {
	UnloadTexture(Sprite);
}

//Getters

//Returns True if Game is Over
bool Player::GetEndGame() {
	return EndGame;
}

//Returns True if Player is Dead
bool Player::GetIsDead() {
	return IsDead;
}

//Setters

//Used to set EndGame to True or False
void Player::SetEndState(const bool& GS) {
	EndGame = GS;
}

//Used to Set "IsDead" boolean
void Player::SetIsDead(const bool& State) {
	IsDead = State;
}

//Resizes the Player to match the size of the screen
void Player::Resize(const float& InitWidth, const float& InitHeight) {

	//Setting up Position Rect (Also Effects Image Scale)
	PosRec.x = GetScreenWidth() * (PosRec.x / InitWidth);
	PosRec.y = GetScreenHeight() * (PosRec.y / InitHeight);
	PosRec.width = GetScreenWidth() * RelativeWidRatio;
	PosRec.height = GetScreenHeight() * RelativeHighRatio;


	//Setting up Rotation point
	RotPoint.x = GetScreenWidth() * RotPointXRatio;
	RotPoint.y = GetScreenHeight() * RotPointYRatio;

	//Setting Up "Entity" for Collisions
	Vector2 Pos;
	Pos.x = GetScreenWidth() * (GetPos().x / InitWidth);
	Pos.y = GetScreenHeight() * (GetPos().y / InitHeight);

	//I dont know why Multiplying ScreenHeight by the Width Ratio works but it does
	EntitySetUp(Pos, GetScreenWidth() * RelativeWidRatio, GetScreenHeight() * RelativeWidRatio);

	//Something is broken here, FIX IT NOW
	SetCollisOffset(GetScreenWidth() * (GetCollisOffX() / InitWidth), GetScreenHeight() * (GetCollisOffY() / InitHeight));

	//Setting up MinY & MaxY Pos
	MaxYPos = GetScreenHeight() * MaxYPosRatio;
	MinYPos = GetScreenHeight() * MinYPosRatio;

	//Setting Up Acceleration Stuff
	YAccel = GetScreenHeight() * RelativeYAccel;

	//Setting up EndGamePos (Y)
	EndGamePos = GetScreenHeight() * EndGamePosRatio;
}


//Returns True if the player is out of bounds (also Kills Player if Out of Bounds)
bool Player::IsOutBounds() {
	
	//Checks if Out of Bounds
	if (GetPos().y < MinYPos || GetPos().y > MaxYPos) {
		IsDead = true;
		return true;
	}

	return false;
}

//Private Function(s)

//Animates the Player Death
void Player::DeathAnim() {

	float DeltaTime = GetFrameTime();

	YVelocity += YAccel;
	Rotation += DeatRotAcell * DeltaTime;
	UpdateY(YVelocity * DeltaTime);

	if (GetPos().y > EndGamePos) {
		EndGame = true;
		SetPos(GetPos().x, EndGamePos);
		YVelocity = 0;
		Rotation = 0;
	}

	PosRec.y = GetPos().y;

}

#endif