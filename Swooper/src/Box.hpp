#ifndef Box_HPP
#define Box_HPP

#include "raylib.h"

class Box {
public:
	Box(const float& XCord, const float& YCord, const float& Width, const float& Hight);
	void Draw();
	void Resize(const float& InitWidth, const float& InitHight);
	void Bounce(const float& InitHeight, const float& AmplTude, const float& AngFreq);

private:
	Rectangle WhiteBox;
	Rectangle BlackBox;
	float WBOffsetX = 0;
	float WBOffsetY = 0;
};

Box::Box(const float& XCord, const float& YCord, const float& Width, const float& Hight) {

//BlackBox Setting
	BlackBox.x = XCord;
	BlackBox.y = YCord;

	BlackBox.width = Width;
	BlackBox.height = Hight;

//WhiteBox Setting
	WhiteBox.x = XCord + Width * 0.025;
	WhiteBox.y = YCord + Hight * 0.025;

	WhiteBox.width = Width * 0.95;
	WhiteBox.height = Hight * 0.95;

}

void Box::Draw() {

	DrawRectangle(BlackBox.x, BlackBox.y, BlackBox.width, BlackBox.height, BLACK);
	DrawRectangle(WhiteBox.x, WhiteBox.y, WhiteBox.width, WhiteBox.height, WHITE);

}

void Box::Resize(const float& InitWidth, const float& InitHight) {

	//BlackBox
	BlackBox.x = (BlackBox.x / InitWidth) * GetScreenWidth();
	BlackBox.y = (BlackBox.y / InitHight) * GetScreenHeight();

	BlackBox.width = (BlackBox.width / InitWidth) * GetScreenWidth();
	BlackBox.height = (BlackBox.height / InitHight) * GetScreenHeight();

	//WhiteBox
	WhiteBox.x = (WhiteBox.x / InitWidth) * GetScreenWidth();
	WhiteBox.y = (WhiteBox.y / InitHight) * GetScreenHeight();

	WhiteBox.width = (WhiteBox.width / InitWidth) * GetScreenWidth();
	WhiteBox.height = (WhiteBox.height / InitHight) * GetScreenHeight();

}

void Box::Bounce(const float& InitHight, const float& AmplTude, const float& AngFreq) {

	WhiteBox.y += sin(GetTime() * AngFreq) * (AmplTude / InitHight) * GetScreenHeight();
	BlackBox.y += sin(GetTime() * AngFreq) * (AmplTude / InitHight) * GetScreenHeight();

}

#endif // !Box

