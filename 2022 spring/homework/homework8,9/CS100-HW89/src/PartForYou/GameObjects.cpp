#include "GameObjects.h"
#include "GameBullet.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world,int new_opt)
	: ObjectBase(imageID, x, y, direction, layer, size), state(true), my_world(world),opt(new_opt) {};


bool GameObject::GetState() const{
	return state;
}
void GameObject::SetState(bool flag) {
	state = flag;
}
GameWorld* GameObject::GetWorld() const {
	return my_world;
}
int GameObject::GetOpt() const {
	return opt;
}

void GameObject::Update() {
	if (state == false)
		return;
	int x = GetX(), y = GetY();
	dosomething(x,y);
	if (GetWorld()->Getdawnbreaker()->Gethp() <= 0 && GetWorld()->Getdawnbreaker()->GetState() == true)
		GetWorld()->Getdawnbreaker()->SetState(false);
	return;
}

Star::Star(int x, int y, double size, GameWorld* world) : GameObject(IMGID_STAR, x, y, 0, 4, size, world, 2) {};
int Star::NewX() { return GetX(); }
int Star::NewY() { return GetY() - 1; }
void Star::dosomething(int x,int y) {
	if (y < 0)
	{
		SetState(false);
		return;
	}
	MoveTo(x, y - 1);
	return;
}

Dawnbreaker::Dawnbreaker(GameWorld* world) :GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0, world, 1)
, hp(100), energy(10), level_up(0) {};

int Dawnbreaker::Gethp() const {
	return hp;
}
void Dawnbreaker::Sethp(int new_hp) {
	hp = new_hp;
}
int Dawnbreaker::Getenergy() const {
	return energy;
}
void Dawnbreaker::Setenergy(int new_energy) {
	energy = new_energy;
}
int Dawnbreaker::NewX()
{
	int x = GetX();
	if (GetWorld()->GetKey(KeyCode::LEFT) == true)
		x -= 4;
	if (GetWorld()->GetKey(KeyCode::RIGHT) == true)
		x += 4;
	return x;
}
int Dawnbreaker::NewY()
{
	int y = GetY();
	if (GetWorld()->GetKey(KeyCode::DOWN) == true)
		y -= 4;
	if (GetWorld()->GetKey(KeyCode::UP) == true)
		y += 4;
	return y;
}
int Dawnbreaker::Getlevel_up() const { return level_up; }
void Dawnbreaker::Setlevel_up(int new_level_up) { level_up = new_level_up; }
void Dawnbreaker::dosomething(int x,int y) {
	if (Gethp() <= 0 && GetState() == true)
	{
		SetState(false);
		return;
	}
	int posx = x, posy = y;
	int newx = NewX(), newy = NewY();
	if (0 <= newx && newx <= WINDOW_WIDTH - 1)
		posx = newx;
	if (50 <= newy && newy <= WINDOW_HEIGHT - 1)
		posy = newy;
	MoveTo(posx, posy);
	if (GetWorld()->GetKey(KeyCode::FIRE1) == true)
	{
		if (Getenergy() >= 10)
		{
			Setenergy(Getenergy() - 10);
			int power = 5 + 3 * (Getlevel_up());
			double size = 0.5 + 0.1 * (double)(Getlevel_up());
			GameObject* blue_bullet = new Blue_Bullet(GetX(), GetY() + 50, size, power, GetWorld());
			GetWorld()->AddElement(blue_bullet);
		}
	}
	if (GetWorld()->GetKeyDown(KeyCode::FIRE2) == true)
	{
		if (GetWorld()->Getmeteor() >= 1)
		{
			GameObject* meteor = new Meteor(GetX(), GetY() + 100, GetWorld());
			GetWorld()->AddElement(meteor);
			GetWorld()->Setmeteor(GetWorld()->Getmeteor() - 1);
		}
	}
	if (Getenergy() < 10)
		Setenergy(Getenergy() + 1);
}
