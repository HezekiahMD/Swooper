//A Game By Hezekiah McDonald
#include<iostream>
#include"sddl.h"
#include"Entity.hpp"
#include"Player.hpp"
#include"Obstacle.hpp"
#include"Box.hpp"
#include"TextDimen.hpp"
#include"ScoreS&L.h"
#include<string>


//Struct for the Score Window
struct ScWin{

	Box ScBox = Box(-5, -1, 120, 30);
	TextDimen ScDimen = TextDimen(0, 2, 22, 1);

};

//Struct for Continue Window
struct Cont{

	Box ContBox = Box(150, 50, 200, 200);
	TextDimen YScoreDimen = TextDimen(155, 90, 25, 1);
	TextDimen HScoreDimen = TextDimen(157, 110, 25, 1);
	TextDimen ToContDimen = TextDimen(157.25, 170, 15, 0.25);

};


//Struct for Title Screen
struct TitleStff{
	Box TitleBox = Box(35, 40, 200, 60);
	TextDimen Title = TextDimen(50, 45, 45, 1);

	Box ToPlayBox = Box(10, 100, 270, 25);
	TextDimen PlayTxt = TextDimen(20, 99, 21, 1);

};


int main() {

	//SetTraceLogLevel(TraceLogLevel::LOG_NONE);

	//Setting target FPS & Ability to Resize Window
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	//ScoreFile
	std::string ScoreFile = "ScoreHolder/Score.txt";

	//Score Variables
	int Score = 0;
	int HighScore = SL::LoadScore(ScoreFile);

	//The Default Width & Height of the Window
	int ExpectWidth = 500;
	int ExpectHight = 300;

	//The Starting Width & Hight of the window
	int StartWidth = 750;
	int StartHight = 450;

	//Window Stuff
	TitleStff TitleScreen;
	ScWin ScoreWindow;
	Cont ContWindow;

	//Text Stuff
	std::string Title = "Swo0per";
	std::string ToStart = "-Press Space to Start-";
	std::string ToCont = "-Press Space to Continue-";

//Booleans That Help the Game Run

	//Checks if App Was Just Opened
	bool JustOpened = true;

	//Used to Handle When to Play The Explosion Sound
	bool PlayCrash = true;

	//Used to Check if Hit Should Be played
	bool PlayHit = true;

	//Init's Window
	InitWindow(StartWidth, StartHight, "Swooper");

	//Init's Audio
	InitAudioDevice();

	Sound Hit = LoadSound("Font&Sounds/Hit_Hurt#1.wav");
	Sound GainPoint = LoadSound("Font&Sounds/PointGain#1.wav");
	Sound Crash = LoadSound("Font&Sounds/Crash#1.wav");

	//Init Game Font
	Font Font = LoadFontEx("Font&Sounds/Thirteen-Pixel-Fonts.ttf", 128, 0, 0);

	//Render Target
	RenderTexture2D Target = LoadRenderTexture(ExpectWidth, ExpectHight);
	SetTextureFilter(Target.texture, TEXTURE_FILTER_BILINEAR);

	//Games Objects
	Player Player(150, 150);
	Obstacle Obst[3] = { Obstacle(700,true), Obstacle(950,false), Obstacle(1200,true) };

	while (WindowShouldClose() == false) {

		//Checks if Screen Size Changed/if not default Size
		if (ExpectWidth != GetScreenWidth() || ExpectHight != GetScreenHeight()) {
			Player.Resize(ExpectWidth, ExpectHight);
			for (int i = 0; i < 3; i++) {
				Obst[i].Resize(ExpectWidth, ExpectHight);
			}

			//Resizes TitleScreen Stuff
			TitleScreen.Title.Resize(ExpectWidth,ExpectHight);
			TitleScreen.TitleBox.Resize(ExpectWidth,ExpectHight);

			TitleScreen.ToPlayBox.Resize(ExpectWidth, ExpectHight);
			TitleScreen.PlayTxt.Resize(ExpectWidth, ExpectHight);

			//Resizes the Continue & Score Windows
			ContWindow.ContBox.Resize(ExpectWidth, ExpectHight);
			ScoreWindow.ScBox.Resize(ExpectWidth, ExpectHight);

			//Resizing the ContinueWindow & ScoreWindow Text
			ContWindow.HScoreDimen.Resize(ExpectWidth, ExpectHight);
			ContWindow.YScoreDimen.Resize(ExpectWidth, ExpectHight);
			ContWindow.ToContDimen.Resize(ExpectWidth, ExpectHight);
			ScoreWindow.ScDimen.Resize(ExpectWidth, ExpectHight);

			//Updating Expected Window Dimensions
			ExpectWidth = GetScreenWidth();
			ExpectHight = GetScreenHeight();
		}
		
		BeginTextureMode(Target);
		ClearBackground(RAYWHITE);
		EndTextureMode();

		BeginDrawing();

	//Game Stuffs

		//Drawing Obstacles & other Things that Need to Loop
		for (int i = 0; i < 3; i++) {
			Obst[i].DrawObj();
			Obst[i].UpdatePos();

			//Player Collision Check
			if (Player.ObjCollisCheck(Obst[i]) == true && PlayHit == true) {
				PlaySound(Hit);
				PlayHit = false;
			}

			//Checks if Player is Out of Bounds
			if (Player.IsOutBounds() == true && PlayHit == true){
				PlaySound(Hit);
				PlayHit = false;
			}


			//Player.ObjCollisCheck(Obst[i]);

			//Point Score Check
			if (Player.GetIsDead() == false) {
				if (Obst[i].ScoredPoint(Player) == true) {
					Score += 10;
					PlaySound(GainPoint);
				}


			}
		}

		//Drawing Black Border
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() * (20.0 / 300.0), BLACK);
		DrawRectangle(0, GetScreenHeight() * (280.0 / 300.0), GetScreenWidth(), GetScreenHeight() * (30.0 / 300.0), BLACK);


		//Show Title Screen
		if (JustOpened == true) {

			TitleScreen.TitleBox.Draw();
			DrawTextEx(Font, Title.c_str(), TitleScreen.Title.GetPos(), TitleScreen.Title.GetTxtSize(), TitleScreen.Title.GetSpSize(), BLACK);
			
			TitleScreen.ToPlayBox.Draw();
			DrawTextEx(Font, ToStart.c_str(), TitleScreen.PlayTxt.GetPos(), TitleScreen.PlayTxt.GetTxtSize(), TitleScreen.PlayTxt.GetSpSize(), BLACK);

			//Bouncing Text & Boxes
			TitleScreen.PlayTxt.Bounce(300, 0.25, 2);
			TitleScreen.ToPlayBox.Bounce(300, 0.25, 2);

			TitleScreen.Title.Bounce(300, 0.25, 2);
			TitleScreen.TitleBox.Bounce(300, 0.25, 2);

			

			//Exits the Title Screen
			if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				JustOpened = false;

				for (int i = 0; i < 3; i++) {
					Obst[i].Reset();
					Player.Reset();
				}

			}

		}
		else { //Actual Game Beyond this point

			//Drawing Player
			Player.DrawPlayer();

			//Taking Player Input
			Player.TakeInput();


			//Score Rectangle
			ScoreWindow.ScBox.Draw();
			DrawTextEx(Font, TextFormat("Score:%04i", Score), ScoreWindow.ScDimen.GetPos(), ScoreWindow.ScDimen.GetTxtSize(), ScoreWindow.ScDimen.GetSpSize(), BLACK);

			//On EndGame
			if (Player.GetEndGame() == true) {

				if (PlayCrash == true) {
					PlaySound(Crash);
					PlayCrash = false;
				}


				//Update HighScore Check
				if (HighScore < Score) {
					HighScore = Score;
				}

				//Continue Window
				ContWindow.ContBox.Draw();
				DrawTextEx(Font, TextFormat("Your Score:%04i", Score, HighScore), ContWindow.YScoreDimen.GetPos(), ContWindow.YScoreDimen.GetTxtSize(), ContWindow.YScoreDimen.GetSpSize(), BLACK);
				DrawTextEx(Font, TextFormat("High Score:%04i", HighScore), ContWindow.HScoreDimen.GetPos(), ContWindow.HScoreDimen.GetTxtSize(), ContWindow.HScoreDimen.GetSpSize(), BLACK);
				DrawTextEx(Font, ToCont.c_str(), ContWindow.ToContDimen.GetPos(), ContWindow.ToContDimen.GetTxtSize(), ContWindow.ToContDimen.GetSpSize(), BLACK);

				//Text Bounce
				ContWindow.YScoreDimen.Bounce(300, 0.5, 2);
				ContWindow.HScoreDimen.Bounce(300, 0.5, 2);
				ContWindow.ToContDimen.Bounce(300, 0.5, 2);

				//Resetting Game on Input
				if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

					//Sets JustOpened to False
					JustOpened = false;

					//Sets Play Explosion Back to True
					PlayCrash = true;

					//Sets Play Hit Back to True
					PlayHit = true;

					//Resetting Continue Window Text
					ContWindow.YScoreDimen.ResetPos(500, 300);
					ContWindow.HScoreDimen.ResetPos(500, 300);
					ContWindow.ToContDimen.ResetPos(500, 300);

					//Resetting Game Obj Positions
					Player.Reset();

					for (int i = 0; i < 3; i++) {
						Obst[i].Reset();
					}

					//Resets Score
					Score = 0;
				}

			}
		}

		//Refreshing Screen
		ClearBackground(WHITE);
		EndDrawing();
	}


//Saving HighScore
	SL::SaveScore(HighScore, ScoreFile);

//Unloading Textures
	UnloadRenderTexture(Target);
	Player.UnloadSprite();
	UnloadFont(Font);
	for (int i = 0; i < 3; i++) {
		Obst[i].UnloadSprite();
	}

	CloseWindow();
}