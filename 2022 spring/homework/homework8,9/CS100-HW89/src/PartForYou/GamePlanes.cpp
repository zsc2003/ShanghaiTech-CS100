#include "GamePlanes.h"
#include "GameBullet.h"
#include "GameMaterial.h"

Planes::Planes(int id, int x, int y, GameWorld* world, int new_hp, int new_attack, int new_speed,int opt,int new_energy) :
	GameObject(id, x, y, 180, 0, 1.0, world,opt), hp(new_hp), attack(new_attack), speed(new_speed) ,
	policy(0), policy_time(0) ,energy(new_energy) {};
int Planes::NewX() { return 0; }
int Planes::NewY() { return 0; }
int Planes::Gethp() const { return hp; }
void Planes::Sethp(int new_hp) { hp=new_hp; }
int Planes::GetAttack() const { return attack; }
void Planes::SetAttack(int new_attack) { attack = new_attack; }
int Planes::GetSpeed() const { return speed; }
void Planes::SetSpeed(int new_speed) { speed = new_speed; }
int Planes::GetPolicy() const { return policy; }
void Planes::SetPolicy(int new_policy) { policy = new_policy; }
int Planes::GetPolicyTime() const { return policy_time; }
void Planes::SetPolicyTime(int new_policy_time) { policy_time = new_policy_time; }
int Planes::GetEnergy() const { return energy; }
void Planes::SetEnergy(int new_energy) { energy = new_energy; }
void Planes::step3()
{
	if (GetState() == false)
		return;
	Dawnbreaker* dawnbreaker = GetWorld()->Getdawnbreaker();
	if (dawnbreaker->GetState() == true && GetWorld()->crash(this, dawnbreaker) == true)
	{
	//	std::cout << dawnbreaker->Gethp() << '\n';
		dawnbreaker->Sethp(dawnbreaker->Gethp() - 20);
		if (GetWorld()->Getdawnbreaker()->Gethp() <= 0 && GetWorld()->Getdawnbreaker()->GetState() == true)
			GetWorld()->Getdawnbreaker()->SetState(false);
	//	std::cout << dawnbreaker->Gethp() << '\n';
		SetState(false);
		GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
		GameObject* explosion = new Explosion(GetX(), GetY(), GetWorld());
		GetWorld()->AddElement(explosion);
		GetWorld()->ModifyEnemy(true);
		Destory();
	}
	if (GetState() == false)
		return;
	for (auto it = GetWorld()->GetBegin();it != GetWorld()->GetEnd();it++)
	{
		if (GetWorld()->crash(this,  (*it)) == false)
			continue;
		if ((*it)->GetState() == false)
			return;
		int opt = (*it)->GetOpt();
		if (opt == 5)//meteor
		{
			SetState(false);
			Sethp(0);
		}
		if (opt == 3)//blue bullet
		{
			Blue_Bullet* bluebullet = (Blue_Bullet*)(*it);
			bluebullet->SetState(false);
			Sethp(Gethp() - bluebullet->GetPower());
		}
		if (Gethp() <= 0)
			SetState(false);
		if (GetState() == false)
		{
			GameObject* explosion = new Explosion(GetX(), GetY(), GetWorld());
			GetWorld()->AddElement(explosion);
			GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
			GetWorld()->ModifyEnemy(true);
			Destory();
			return;
		}
	}
}
void Planes::dosomething(int x, int y) {
	if (GetState() == false)
		return;
	if (y < 0)
	{
		SetState(false);
		GetWorld()->SetOnScreen(GetWorld()->GetOnScreen() - 1);
		return;
	}
	step3();
	if (GetState() == false)
		return;
	Attack();
	if (GetPolicyTime() == 0)
	{
		SetPolicy(randInt(1, 3));
		SetPolicyTime(randInt(10, 50));
	}
	if (GetX() < 0)
	{
		SetPolicy(3);
		SetPolicyTime(randInt(10, 50));
	}
	if (GetX() >= WINDOW_WIDTH)
	{
		SetPolicy(1);
		SetPolicyTime(randInt(10, 50));
	}
	SetPolicyTime(GetPolicyTime() - 1);
	int opt = GetPolicy();
	if (opt == 2)
		MoveTo(GetX(), GetY() - GetSpeed());
	if (opt == 1)
		MoveTo(GetX() - GetSpeed(), GetY() - GetSpeed());
	if (opt == 3)
		MoveTo(GetX() + GetSpeed(), GetY() - GetSpeed());
	step3();
}

Alphatron::Alphatron(int x, int y, GameWorld* world, int hp, int attack, int speed) : Planes(IMGID_ALPHATRON, x, y, world, hp, attack, speed, 9, 25) {};
void Alphatron::Attack()
{
	if (abs(GetX() - GetWorld()->Getdawnbreaker()->GetX()) <= 10)
	{
		if (GetEnergy() >= 25)
		{
			int possibility = randInt(1, 4);
			if (possibility == 3)// 1/4的概率
			{
				SetEnergy(GetEnergy() - 25);
				GameObject* redbullet = new Red_Bullet(GetX(), GetY() - 50, 180, GetAttack(), GetWorld());
				GetWorld()->AddElement(redbullet);
			}
		}
	}
	if (GetEnergy() < 25)
		SetEnergy(GetEnergy() + 1);
}
void Alphatron::Destory() { GetWorld()->IncreaseScore(50); }

Sigmatron::Sigmatron(int x, int y, GameWorld* world, int hp, int attack, int speed) : Planes(IMGID_SIGMATRON, x, y, world, hp, attack, speed, 10, 0) {};
void Sigmatron::Attack()
{
	if (abs(GetX() - GetWorld()->Getdawnbreaker()->GetX()) <= 10)
	{
		SetPolicy(2);
		SetPolicyTime(2147483647);
		SetSpeed(10);
	}
}
void Sigmatron::Destory()
{
	GetWorld()->IncreaseScore(100);
	int possibility = randInt(1, 5);
	if (possibility == 3)// 1/5的概率留下hp道具
	{
		GameObject* hpgoodie = new HPGoodie(GetX(), GetY(), GetWorld());
		GetWorld()->AddElement(hpgoodie);
	}
}

Omegatron::Omegatron(int x, int y, GameWorld* world, int hp, int attack, int speed) : Planes(IMGID_OMEGATRON, x, y, world, hp, attack, speed, 11, 50) {};
void Omegatron::Attack()
{
	if (GetEnergy() >= 50)
	{
		SetEnergy(GetEnergy() - 50);
		GameObject* redbullet1 = new Red_Bullet(GetX(), GetY() - 50, 162, GetAttack(), GetWorld());
		GameObject* redbullet2 = new Red_Bullet(GetX(), GetY() - 50, 198, GetAttack(), GetWorld());
		GetWorld()->AddElement(redbullet1);
		GetWorld()->AddElement(redbullet2);
	}
	if (GetEnergy() < 50)
		SetEnergy(GetEnergy() + 1);
	return;
}
void Omegatron::Destory()
{
	GetWorld()->IncreaseScore(200);
	int possibility = randInt(1, 5);
	if (possibility == 3 || possibility == 5)// 2/5的概率留下hp道具
	{
		possibility = randInt(1, 5);
		GameObject* goodie;
		if (possibility == 2)//20%陨石
			goodie = new MeteorGoodie(GetX(), GetY(), GetWorld());
		else
			goodie = new PowerUpGoodie(GetX(), GetY(), GetWorld());
		GetWorld()->AddElement(goodie);
	}
}