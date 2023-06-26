#include "GameMaterial.h"

Explosion::Explosion(int x, int y, GameWorld* world) : GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5, world,12)
								,update_times(0) {};
int Explosion::GetTimes() const {
	return update_times;
}
void Explosion::SetTimes(int new_time) {
	update_times = new_time;
}
int Explosion::NewX() { return 0; }
int Explosion::NewY() { return 0; }
void Explosion::dosomething(int x, int y)
{
	SetSize(GetSize() - 0.2);
	SetTimes(GetTimes() + 1);
	if (GetTimes() >= 20)
		SetState(false);
}

Goodie::Goodie(int id, int x, int y, GameWorld* world,int opt) : GameObject(id, x, y, 0, 2, 0.5, world,opt) {};
int Goodie::NewX() { return GetX(); }
int Goodie::NewY() { return GetY() - 2; }

void Goodie::dosomething(int x, int y)
{
	if (y < 0)
	{
		SetState(false);
		return;
	}
	if (GetWorld()->Getdawnbreaker()->GetState() == false)
		return;
	if (GetWorld()->crash(this, GetWorld()->Getdawnbreaker()))
		step3();
	if (GetState() == false)
		return;
	MoveTo(x, y - 2);
	if(GetWorld()->crash(this,GetWorld()->Getdawnbreaker()))
		step3();
}

HPGoodie::HPGoodie(int x, int y, GameWorld* world) : Goodie(IMGID_HP_RESTORE_GOODIE, x, y, world, 6) {};
void HPGoodie::step3()
{
	GetWorld()->Getdawnbreaker()->Sethp(std::min(GetWorld()->Getdawnbreaker()->Gethp() + 50, 100));
	GetWorld()->IncreaseScore(20);
	SetState(false);
	return;
}

PowerUpGoodie::PowerUpGoodie(int x, int y, GameWorld* world) : Goodie(IMGID_POWERUP_GOODIE, x, y, world, 7) {};
void PowerUpGoodie::step3()
{
	GetWorld()->Getdawnbreaker()->Setlevel_up(GetWorld()->Getdawnbreaker()->Getlevel_up() + 1);
	GetWorld()->IncreaseScore(20);
	SetState(false);
	return;
}


MeteorGoodie::MeteorGoodie(int x, int y, GameWorld* world) : Goodie(IMGID_METEOR_GOODIE, x, y, world, 8) {};
void MeteorGoodie::step3()
{
	GetWorld()->Setmeteor(GetWorld()->Getmeteor() + 1);
	GetWorld()->IncreaseScore(20);
	SetState(false);
}