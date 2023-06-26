#include "GameBullet.h"
#include "GamePlanes.h"
#include "GameMaterial.h"

Bullet::Bullet(int imageID, int x, int y, int direction, int layer, double size, int set_power, GameWorld* world, int opt) :
	GameObject(imageID, x, y, direction, layer, size, world, opt), power(set_power) {};
int Bullet::GetPower() const { return power; }

Blue_Bullet::Blue_Bullet(int x, int y, double size, int set_power, GameWorld* world) :
	Bullet(IMGID_BLUE_BULLET, x, y, 0, 1, size, set_power, world, 3) {};
int Blue_Bullet::NewX() { return GetX(); }
int Blue_Bullet::NewY() { return GetY() + 6; }
void Blue_Bullet::step3()
{
	if (GetState() == false)
		return;
	for (auto it = GetWorld()->GetBegin();it != GetWorld()->GetEnd();it++)
	{
		if ((*it)->GetState() == false)
			continue;
		if (GetWorld()->crash(this, (*it)) == false)
			continue;
		int opt = (*it)->GetOpt();
		if (opt == 9 || opt == 10 || opt == 11)
		{
			Planes* plane = (Planes*)(*it);
			plane->Sethp(plane->Gethp() - GetPower());
			if (plane->Gethp() <= 0)
			{
				plane->SetState(false);
				GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
				GameObject* explosion = new Explosion(plane->GetX(), plane->GetY(), GetWorld());
				GetWorld()->AddElement(explosion);
				GetWorld()->ModifyEnemy(true);
				plane->Destory();
			}
			SetState(false);
			return;
		}
	}
}
void Blue_Bullet::dosomething(int x,int y)
{
	if (GetY() >= WINDOW_HEIGHT)
	{
		SetState(false);
		return;
	}
	step3();
	MoveTo(NewX(), NewY());
	step3();
}


Red_Bullet::Red_Bullet(int x, int y, int direction, int set_power, GameWorld* world) :
	Bullet(IMGID_RED_BULLET, x, y, direction, 1, 0.5, set_power, world, 4) {};
int Red_Bullet::NewX() {
	int x = GetX(), direction = GetDirection();
	if (direction == 180)//正下
		x = x;
	if (direction == 162)//右下
		x += 2;
	if (direction == 198)//左下
		x -= 2;
	return x;
}
int Red_Bullet::NewY() { return GetY() - 6; }
void Red_Bullet::dosomething(int x, int y)
{
	if (GetY() < 0)
	{
		SetState(false);
		return;
	}
	step3();
	MoveTo(NewX(), NewY());
	step3();
}
void Red_Bullet::step3()
{
	if (GetState() == false)
		return;
	Dawnbreaker* dawnbreaker = GetWorld()->Getdawnbreaker();
	
	if (dawnbreaker->GetState() == false)
		return;
	if (GetWorld()->crash(this, dawnbreaker) == false)
		return;
	dawnbreaker->Sethp(dawnbreaker->Gethp() - GetPower());
	if (dawnbreaker->Gethp() <= 0 && dawnbreaker->GetState() == true)
		dawnbreaker->SetState(false);
	SetState(false);
}

Meteor::Meteor(int x, int y, GameWorld* world) : Bullet(IMGID_METEOR, x, y, 0, 1, 2.0, 0, world, 5) {};
int Meteor::NewX() { return GetX(); }
int Meteor::NewY() { return GetY() + 2; }
void Meteor::step3()
{
	if (GetState() == false)
		return;
	for (auto it = GetWorld()->GetBegin();it != GetWorld()->GetEnd();it++)
	{
		if ((*it)->GetState() == false)
			continue;
		if (GetWorld()->crash(this, (*it)) == false)
			continue;
		int opt = (*it)->GetOpt();
		if (opt == 9 || opt == 10 || opt == 11)
		{
			Planes* plane = (Planes*)(*it);
			plane->Sethp(0);
			plane->SetState(false);
			GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
			GameObject* explosion = new Explosion(plane->GetX(), plane->GetY(), GetWorld());
			GetWorld()->AddElement(explosion);
			GetWorld()->ModifyEnemy(true);
			plane->Destory();
			return;
		}
	}
}
void Meteor::dosomething(int x, int y)
{
	if (GetY() >= WINDOW_HEIGHT)
	{
		SetState(false);
		return;
	}
	step3();
	MoveTo(NewX(), NewY());
	SetDirection(GetDirection() + 5);
	step3();
}