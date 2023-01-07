#include"raylib.h"
#include<string>
using namespace std;

//Const Global Variables
//-----------------------------------------------
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;

const float GRAVITY = 1000;

const float collisionLost = 0.4;
//-----------------------------------------------

class Ball {
private:
	float posX;
	float posY;
	float velX;
	float velY;
	float accX;
	float accY;

	//Forces are in Newtons
	float horizontalForce;
	float verticalForce;

	float mass;
	Color color; 

public:
	Ball();

	float getPosX();
	float getPosY();
	float getVelX();
	float getVelY();
	float getAccX();
	float getAccY();
	float getHorizontalForce();
	float getVerticalForce();

	void setPosX(float posX);
	void setPosY(float posY);
	void setVelX(float velX);
	void setVelY(float velY);
	void setAccX(float accX);
	void setAccY(float accY);
	void setHorizontalForce(float horizontalForce);
	void setVerticalForce(float verticalForce);

	void Draw();
	void PrintStats();
	void CalculateHorizontalForce(float LeftBlowerForce, float RightBlowerForce);
	void CalculateVerticalForce(float TopBlowerForce, float BottomBlowerForce);
	void CalculateAcceleration();
	void CalculateVelocity();
	void CalculatePosition();
	void ReverseDirection();
	void BoundCheck();
};

Ball::Ball()
	: posX(GetScreenWidth() / 2), posY(GetScreenHeight() / 2), velX(0), velY(0), accX(0), accY(0), horizontalForce(0), verticalForce(0), mass(30), color(RED) {}

float Ball::getPosX() { return posX; }
float Ball::getPosY() { return posY; }
float Ball::getVelX() { return velX; }
float Ball::getVelY() { return velY; }
float Ball::getAccX() { return accX; }
float Ball::getAccY() { return accY; }
float Ball::getHorizontalForce() { return horizontalForce; }
float Ball::getVerticalForce() { return verticalForce; }

void Ball::setPosX(float posX) { this->posX = posX; }
void Ball::setPosY(float posY) { this->posY = posY; }
void Ball::setVelX(float velX) { this->velX = velX; }
void Ball::setVelY(float velY) { this->velY = velY; }
void Ball::setAccX(float accX) { this->accX = accX; }
void Ball::setAccY(float accY) { this->accY = accY; }
void Ball::setHorizontalForce(float horizontalForce) { this->horizontalForce = horizontalForce; }
void Ball::setVerticalForce(float verticalForce) { this->verticalForce = verticalForce; }

void Ball::Draw() { DrawCircle(posX, posY, mass, color); }
void Ball::PrintStats()
{
	char message[50];
	int fontSize = 30;
	int textPosX = GetScreenWidth() / 3 * 2;
	int textPosY = fontSize / 2;

	strcpy_s(message, "Position: (");
	strcat_s(message, to_string(static_cast<int>(posX)).c_str());
	strcat_s(message, ", ");
	strcat_s(message, to_string(static_cast<int>(GetScreenHeight() - posY)).c_str());
	strcat_s(message, ")");
	DrawText(message, textPosX, textPosY, fontSize, YELLOW);

	textPosY += fontSize + fontSize / 2;
	strcpy_s(message, "Velocity: (");
	strcat_s(message, to_string(static_cast<int>(velX)).c_str());
	strcat_s(message, ", ");
	strcat_s(message, to_string(static_cast<int>(velY)).c_str());
	strcat_s(message, ")");
	DrawText(message, textPosX, textPosY, fontSize, YELLOW);

	textPosY += fontSize + fontSize / 2;
	strcpy_s(message, "Acceleration: (");
	strcat_s(message, to_string(static_cast<int>(accX)).c_str());
	strcat_s(message, ", ");
	strcat_s(message, to_string(static_cast<int>(-1 * accY)).c_str());
	strcat_s(message, ")");
	DrawText(message, textPosX, textPosY, fontSize, YELLOW);

	textPosY += fontSize + fontSize / 2;
	strcpy_s(message, "Horizontal Force: ");
	strcat_s(message, to_string(static_cast<int>(horizontalForce)).c_str());
	strcat_s(message, " N");
	DrawText(message, textPosX, textPosY, fontSize, YELLOW);

	textPosY += fontSize + fontSize / 2;
	strcpy_s(message, "Vertical Force: ");
	strcat_s(message, to_string(static_cast<int>(verticalForce)).c_str());
	strcat_s(message, " N");
	DrawText(message, textPosX, textPosY, fontSize, YELLOW);
}
void Ball::CalculateHorizontalForce(float LeftBlowerForce, float RightBlowerForce)
{
	horizontalForce = LeftBlowerForce - RightBlowerForce;
}
void Ball::CalculateVerticalForce(float TopBlowerForce, float BottomBlowerForce)
{
	verticalForce = TopBlowerForce - BottomBlowerForce;
}
void Ball::CalculateAcceleration()
{
	accX = horizontalForce / mass;
	//accY = verticalForce / mass; //No Gravity
	accY = verticalForce / mass + GRAVITY; //Yes Gravity
}
void Ball::CalculateVelocity()
{
	velX += accX * GetFrameTime();
	velY += accY * GetFrameTime();
}
void Ball::CalculatePosition()
{
	posX += velX * GetFrameTime();
	posY += velY * GetFrameTime();
}
void Ball::ReverseDirection()
{
	velX *= -1;
	velY *= -1;
}

//mass is used as radius
void Ball::BoundCheck()
{
	if (posX <= mass)
	{
		posX = mass;
		velX *= -1 * collisionLost; 
	}
	else if (posX >= GetScreenWidth() - mass)
	{
		posX = GetScreenWidth() - mass;
		velX *= -1 * collisionLost;
	}

	if (posY <= mass)
	{
		posY = mass;
		velY *= -1 * collisionLost;
	}
	else if (posY >= GetScreenHeight() - mass)
	{
		posY = GetScreenHeight() - mass;
		velY *= -1 * collisionLost;
	}
}

//Global Variables
//-----------------------------------------------
Ball ball;
bool Stopped;

float TopBlowerForce;
float BottomBlowerForce;
float LeftBlowerForce;
float RightBlowerForce;

float BlowerGain;
float BlowerLoss;

float BlowerCap;

int BlowerForceIncrementSpeed;
int BlowerForceIncrementSpeedCounter;
//-----------------------------------------------

void PrintBlowerStats()
{
	char message[50];
	int textWidth;
	int fontSize = 30;
	int border = 30;

	strcpy_s(message, "");
	strcat_s(message, to_string(static_cast<int>(TopBlowerForce)).c_str());
	strcat_s(message, " N");
	DrawText(message, GetScreenWidth() / 2, border, fontSize, YELLOW);

	strcpy_s(message, "");
	strcat_s(message, to_string(static_cast<int>(LeftBlowerForce)).c_str());
	strcat_s(message, " N");
	DrawText(message, border, GetScreenHeight() / 2, fontSize, YELLOW);

	strcpy_s(message, "");
	strcat_s(message, to_string(static_cast<int>(RightBlowerForce)).c_str());
	strcat_s(message, " N");
	textWidth = MeasureText(message, fontSize);
	DrawText(message, GetScreenWidth() - textWidth - border, GetScreenHeight() / 2, fontSize, YELLOW);

	strcpy_s(message, "");
	strcat_s(message, to_string(static_cast<int>(BottomBlowerForce)).c_str());
	strcat_s(message, " N");
	DrawText(message, GetScreenWidth() / 2, GetScreenHeight() - border - fontSize, fontSize, YELLOW);
}

void SetUp()
{
	ball = Ball();
	Stopped = true;

	TopBlowerForce = 0;
	BottomBlowerForce = 0;
	LeftBlowerForce = 0;
	RightBlowerForce = 0;

	BlowerGain = 10000;
	BlowerLoss = 500;

	BlowerCap = 100000;

	BlowerForceIncrementSpeed = 10;
	BlowerForceIncrementSpeedCounter = 0;
}
void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	ball.Draw();
	ball.PrintStats();
	PrintBlowerStats();
	EndDrawing();
}

void Input()
{
	if (IsKeyPressed(KEY_S) || IsKeyDown(KEY_S))
	{
		TopBlowerForce += BlowerGain;
		if (TopBlowerForce > BlowerCap)
			TopBlowerForce = BlowerCap;
	}
	if (IsKeyPressed(KEY_W) || IsKeyDown(KEY_W))
	{
		BottomBlowerForce += BlowerGain;
		if (BottomBlowerForce > BlowerCap)
			BottomBlowerForce = BlowerCap;
	}
	if (IsKeyPressed(KEY_A) || IsKeyDown(KEY_A))
	{
		RightBlowerForce += BlowerGain;
		if (RightBlowerForce > BlowerCap)
			RightBlowerForce = BlowerCap;
	}
	if (IsKeyPressed(KEY_D) || IsKeyDown(KEY_D))
	{
		LeftBlowerForce += BlowerGain;
		if (LeftBlowerForce > BlowerCap)
			LeftBlowerForce = BlowerCap;
	}
}

void Logic()
{
	ball.CalculateHorizontalForce(LeftBlowerForce, RightBlowerForce);
	ball.CalculateVerticalForce(TopBlowerForce, BottomBlowerForce);
	ball.CalculateAcceleration();
	ball.CalculateVelocity();
	ball.CalculatePosition();
	ball.BoundCheck();

	TopBlowerForce -= BlowerLoss;
	if (TopBlowerForce < 0)
		TopBlowerForce = 0;
	BottomBlowerForce -= BlowerLoss;
	if (BottomBlowerForce < 0)
		BottomBlowerForce = 0;
	LeftBlowerForce -= BlowerLoss;
	if (LeftBlowerForce < 0)
		LeftBlowerForce = 0;
	RightBlowerForce -= BlowerLoss;
	if (RightBlowerForce < 0)
		RightBlowerForce = 0;
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Two Dimensional Motion");
	SetWindowState(FLAG_VSYNC_HINT);

	SetUp();
	while (!WindowShouldClose())
	{
		Draw();
		if (BlowerForceIncrementSpeedCounter == BlowerForceIncrementSpeed)
		{
			Input();
			BlowerForceIncrementSpeedCounter = 0;
		}
		Logic();
		BlowerForceIncrementSpeedCounter++;
	}
	CloseWindow();
}