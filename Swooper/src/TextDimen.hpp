#ifndef TextDimen_HPP
#define TextDimen_HPP

#include "raylib.h"

class TextDimen {
	
public:

	//Constructor
	TextDimen(const float& XCord, const float& YCord, const float& TxtSize, const float& SpSize);

	//Getters
	Vector2 GetPos();
	float GetTxtSize();
	float GetSpSize();


	//Setters
	void SetXPos(const float& XCord);
	void SetYPos(const float& YCord);
	void SetTxtSize(const float& TxtSize);
	void SetSpSize(const float& SpSize);

	//Misc
	void Resize(const float& InitWidth, const float& InitHeight);
	void Bounce(const float& InitHight, const float& AmplTude, const float& AngFreq);
	void ResetPos(const float& InitWidth, const float& InitHeight);

private:
	
	Vector2 Position;
	Vector2 InitPos;
	float TextSize;
	float SpaceSize;

};


//Constructor
TextDimen::TextDimen(const float& XCord, const float& YCord, const float& TxtSize, const float& SpSize) {

	Position.x = XCord;
	Position.y = YCord;

	InitPos = Position;

	TextSize = TxtSize;
	SpaceSize = SpSize;

}

//Getters


Vector2 TextDimen::GetPos() {
	return Position;
}

float TextDimen::GetTxtSize() {
	return TextSize;
}

float TextDimen::GetSpSize() {
	return SpaceSize;
}


//Setters

void TextDimen::SetXPos(const float& XCord) {
	Position.x = XCord;
}

void TextDimen::SetYPos(const float& YCord) {
	Position.y = YCord;
}

void TextDimen::SetTxtSize(const float& TxtSize) {
	TextSize = TxtSize;
}

void TextDimen::SetSpSize(const float& SpSize) {
	SpaceSize = SpSize;
}

//Misc
void TextDimen::Resize(const float& InitWidth, const float& InitHeight) {

	Position.x = (Position.x / InitWidth) * GetScreenWidth();
	Position.y = (Position.y / InitHeight) * GetScreenHeight();
	TextSize = (TextSize / InitWidth) * GetScreenWidth();
	SpaceSize = (SpaceSize / InitWidth) * GetScreenWidth();

}

void TextDimen::Bounce(const float& InitHight, const float& AmplTude, const float& AngFreq) {

	Position.y += sin(GetTime() * AngFreq) * (AmplTude / InitHight) * GetScreenHeight();

}

void TextDimen::ResetPos(const float& InitWidth, const float& InitHeight) {

	Position.x = (InitPos.x / InitWidth) * GetScreenWidth();
	Position.y = (InitPos.y / InitHeight) * GetScreenHeight();
}

#endif // !TextDimen_HPP

