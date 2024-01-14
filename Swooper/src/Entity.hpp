#ifndef Entity_HPP
#define Entity_HPP

//#include <iostream>
#include "raylib.h"

class Entity {
public:

	//Constructor
	Entity();
	Entity(const Vector2& Pos, const float Width, const float Hight);

	//Setters
	void EntitySetUp(const Vector2& Pos, const float Width, const float Hight);
	void SetPos(const float& X, const float& Y);
	void SetCollisOffset(const float& OffX, const float& OffY);
	void SetPrevPos(const Vector2& Pos);
	void SetCollis(const float& Width, const float& Hight, const float& XOff, const float& YOff);
	void SetCanCollide(const bool& Input);

	//Getters
	Vector2 GetPos();
	Vector2 GetPrevPos();
	Rectangle GetCollis();
	float GetCollisOffX();
	float GetCollisOffY();

	//Misc
	void UpdateY(const float& Y);
	void UpdateX(const float& X);
	bool CollisCheck(const Entity& Obj);
	void SolidCollisCheck(const Entity& Obj);
	void DrawCollis();

private:
	Vector2 PrevPosition;
	Vector2 Position;
	Rectangle ColliShape;
	Color CollisColor = Color{ 0,0,255,128 };

	//Position Offset for CollisionShape
	float CollisXOff = 0;
	float CollisYOff = 0;
	bool CanCollide = true;

	//Functions
	void SolveCollis(const Entity& Obj);
};

//Default Constructor
Entity::Entity() {

}

//Constructor
Entity::Entity(const Vector2& Pos, const float Width, const float Hight) {
	EntitySetUp(Pos, Width, Hight);
}

//Entity Set Up
void Entity::EntitySetUp(const Vector2& Pos, const float Width, const float Hight) {
	SetPos(Pos.x, Pos.y);
	SetCollis(Width, Hight, CollisXOff, CollisYOff);
	PrevPosition = Position;
}

//Setters

//Sets the Entity Position
void Entity::SetPos(const float& X, const float& Y) {
	Position.x = X;
	Position.y = Y;
	ColliShape.x = X;
	ColliShape.y = Y;
}

//Sets Collision Offeset
void Entity::SetCollisOffset(const float& OffX, const float& OffY) {
	CollisXOff = OffX;
	CollisYOff = OffY;
}

//Sets PreviousPosition
void Entity::SetPrevPos(const Vector2& Pos) {
	PrevPosition = Pos;
}

//Sets Collision Variables
void Entity::SetCollis(const float& Width, const float& Hight, const float& XOff, const float& YOff) {

	ColliShape.width = Width;
	ColliShape.height = Hight;

	CollisXOff = XOff;
	CollisYOff = YOff;

	ColliShape.x = Position.x; //+CollisXOff;
	ColliShape.y = Position.y; //+CollisYOff;
}

//Makes ActiveCollision On or Off
void Entity::SetCanCollide(const bool& Input) {
	CanCollide = Input;
}

//Getters

//Returns the Position of Entity
Vector2 Entity::GetPos() {
	return Position;
}

//Returns the Previous Position of Entity
Vector2 Entity::GetPrevPos() {
	return PrevPosition;
}

//Returns the collision Shape of Entity
Rectangle Entity::GetCollis() {
	return ColliShape;
}

//Returns the collision OffsetX
float Entity::GetCollisOffX() {
	return CollisXOff;
}

//Returns the collision OffsetY
float Entity::GetCollisOffY() {
	return CollisYOff;
}

//Misc

//Transforms X Position of Entity
void Entity::UpdateX(const float& X) {
	Position.x += X;
	ColliShape.x += X;
}

//Transforms Y Position of Entity
void Entity::UpdateY(const float& Y) {
	Position.y += Y;
	ColliShape.y += Y;
}

//Checks if two Entities have Collided
bool Entity::CollisCheck(const Entity& Obj) {

	//Self Collision Dimensions
	float SelfYUp = ColliShape.y + CollisYOff;
	float SelfYDow = ColliShape.y + CollisYOff +ColliShape.height;
	float SelfXLef = ColliShape.x + CollisXOff;
	float SelfXRig = ColliShape.x + CollisXOff + ColliShape.width;

	//Obj Collision Dimensions
	float ObjYUp = Obj.ColliShape.y + Obj.CollisYOff;
	float ObjYDow = Obj.ColliShape.y + Obj.CollisYOff + Obj.ColliShape.height;
	float ObjXLef = Obj.ColliShape.x + Obj.CollisXOff;
	float ObjXRig = Obj.ColliShape.x + Obj.CollisXOff + Obj.ColliShape.width;

	//Collision Checking (If Objects Overlap, Undo Movement)
	if (CanCollide == true) {

		if (SelfYUp <= ObjYDow && SelfYDow >= ObjYUp) {

			if (SelfXLef <= ObjXRig && SelfXRig >= ObjXLef) {

				return true;

			}

		}
	}

	return false;
}

//Makes Entity Collide with other entities
void Entity::SolidCollisCheck(const Entity& Obj) {

	if (CollisCheck(Obj) == true) {
		SolveCollis(Obj);
	}

}

//Used to Draw Collision Shape Over Objects
void Entity::DrawCollis() {
	DrawRectangle(ColliShape.x + CollisXOff, ColliShape.y + CollisYOff, ColliShape.width, ColliShape.height, CollisColor);
}

//Solves Object Collisions (Currently Broken)
void Entity::SolveCollis(const Entity& Obj) {

	Vector2 PosHolder = Position;

	//X Check
	Position.x = PrevPosition.x;
	ColliShape.x = PrevPosition.x;

	//Checking if X Transform Worked
	if (CollisCheck(Obj) == false) {
		return;
	}
	else {
		Position.x = PosHolder.x;
		ColliShape.x = PosHolder.x;
	}

	//Y Check
	Position.y = PrevPosition.y;
	ColliShape.y = PrevPosition.y;

	//Checking if Y Transform Worked
	if (CollisCheck(Obj) == false) {
		return;
	}
	else {
		Position = PrevPosition;
		ColliShape.x = PrevPosition.x;
		ColliShape.y = PrevPosition.y;
		return;
	}

}

#endif