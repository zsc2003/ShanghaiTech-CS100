## 我实现的特殊功能

坚果墙有坚果修复术，在血量不足 1/3 时可以在原地种一个，会使血量恢复满血。

双发射手会以一定概率变身为红色并发射红色豌豆，红色豌豆可以追踪，并且有一定概率引发 3*3 爆炸。

## 植物和种子

每个植物都非常不同，但是不同植物的种子有什么不同呢？各个种子唯一的区别，只在于被点击了之后，会种下什么植物。所以很显然，种子就应该是个模板类 `Seed<PlantType>` ，其中 `PlantType` 是某种植物。

```cpp
template <typename PlantType> class Seed : public GameObject {
public:
  Seed(ImageID imageID, int index, GameWorld *world, int price, int cooldownTime)
      : GameObject{imageID,    130 + index * 60, WINDOW_HEIGHT - 44,   LayerID::UI,
                   SEED_WIDTH, SEED_HEIGHT,      AnimID::NO_ANIMATION, world},
        m_price{price}, m_cooldownTime{cooldownTime} {}

  void OnClick() override {
    if (GetWorld()->IsHoldingShovel() || GetWorld()->HasSpawn())
      return;
    if (GetWorld()->GetSunlight() >= m_price) {
      GetWorld()->IncreaseSunlight(-m_price);
      GetWorld()->AddObject<CooldownMask>(GetX(), GetY(), GetWorld(), m_cooldownTime);
      GetWorld()->SetSelectedSeed(this); // 见下文
    }
  }

  void Update() override {}

private:
  int m_price;
  int m_cooldownTime;
};
```

比如 `Seed<Sunflower>` 就是向日葵种子， `Seed<Peashooter>` 就是豌豆射手的种子。

不过在我的实现中，我还加了一个父类 `SeedBase` ，然后让 `Seed<PlantType>` 继承自 `SeedBase` ，将所有与模板参数 `PlantType` 无关的代码都放进了父类 `SeedBase` 里。这样做的好处，其一详见《Effective C++》条款 44 “将与参数无关的代码抽离 templates” ，其二见下文。

## 如何种下植物？

这是一个比较有意思的问题。大多数同学都没有避开类似于这样的一组判断：

```cpp
if (/* 被选中的种子是向日葵种子 */)
  AddObject<Sunflower>(/* ... */);
else if (/* 被选中的种子是豌豆射手种子 */)
  AddObject<Peashooter>(/* ... */);
else if (/* 被选中的种子是坚果墙种子 */)
  AddObject<Wallnut>(/* ... */);
else if (/* 被选中的种子是樱桃炸弹种子 */)
  AddObject<CherryBomb>(/* ... */);
// ...
// ...
```

假如有 100 种植物，这里就会出现 100 个 `else if` ，并且每增加一种植物，这部分代码都需要修改、重新编译。

### 方法一

一些同学几乎已经想到了这个做法。我们给种子类加一组虚函数 `PlantAt(x, y)` ：

```cpp
class SeedBase : public GameObject {
public:
  SeedBase(ImageID imageID, int index, GameWorld *world, int price, int cooldownTime)
      : GameObject{imageID,    130 + index * 60, WINDOW_HEIGHT - 44,   LayerID::UI,
                   SEED_WIDTH, SEED_HEIGHT,      AnimID::NO_ANIMATION, world},
        m_price{price}, m_cooldownTime{cooldownTime} {}

  void Update() override {}

  void OnClick() override {
    if (GetWorld()->IsHoldingShovel() || GetWorld()->HasSelectedSeed())
      return;
    if (GetWorld()->GetSunlight() >= m_price) {
      GetWorld()->IncreaseSunlight(-m_price);
      GetWorld()->AddObject<CooldownMask>(GetX(), GetY(), GetWorld(), m_cooldownTime);
      GetWorld()->SetSelectedSeed(this);
    }
  }

  virtual void PlantAt(int x, int y) const = 0;

private:
  int m_price;
  int m_cooldownTime;
};

template <typename PlantType> class Seed : public SeedBase {
public:
  using SeedBase::SeedBase;

  void PlantAt(int x, int y) const override {
    GetWorld()->AddObject<PlantType>(x, y, GetWorld());
  }
};
```

如果你不是用一个类模板，而是为每个植物都定义了一个种子类，本质上也是一样的，比如

```cpp
class SunflowerSeed : public SeedBase {
public:
  void PlantAt(int x, int y) const override {
    GetWorld()->AddObject<Sunflower>(x, y, GetWorld());
  }
  // ...
};
class PeashooterSeed : public SeedBase {
public:
  void PlantAt(int x, int y) const override {
    GetWorld()->AddObject<Peashooter>(x, y, GetWorld());
  }
  // ...
};
class WallnutSeed : public SeedBase {
public:
  void PlantAt(int x, int y) const override {
    GetWorld()->AddObject<Wallnut>(x, y, GetWorld());
  }
  // ...
};
```

在 `GameWorld` 里，我们用一个 `const SeedBase *` 表示**当前选中的种子**：

```cpp
class GameWorld : public WorldBase {
public:
  void SetSelectedSeed(const SeedBase *seed) {
    m_selectedSeed = seed;
  }

  bool HasSelectedSeed() const {
    return m_selectedSeed != nullptr;
  }

  void ReleaseSelectedSeedAt(int x, int y) {
    m_selectedSeed->PlantAt(x, y);
    m_selectedSeed = nullptr;
  }

private:
  const SeedBase *m_selectedSeed;
};
```

于是，当种植位被点击时，我们就可以调用这个 `ReleaseSelectedSeedAt` ：

```cpp
class PlantingSpot : public GameObject {
public:
  void OnClick() override {
    if (GetWorld()->HasSelectedSeed())
      GetWorld()->ReleaseSelectedSeedAt(GetX(), GetY());
  }
};
```

有没有体会到其中的玄机？

1. 我们将“要种的植物的类型”这一信息隐藏在了一组函数 `PlantAt` 里。
2. 我们借助虚函数的动态绑定机制来选择究竟调用哪一个 `PlantAt` ，也就是选择种下哪一个植物。

这实际上就是一种设计模式，叫做**策略模式** (Strategy Pattern) 。还记得吗，之前我们已经见过**访问者模式** (Visitor Pattern) ，那也是一种设计模式。

这里的 `PlantAt` 就是“策略”，即“如何种下植物”。每一种植物（或者说种子）都有与之对应的“种植策略”，我们想要在运行时选择这些种植策略中的一个。借助虚函数动态绑定机制，是实现策略模式的一种方法，也是比较传统的一种方法。

## 方法二

如果你仔细看看方法一的 `PlantAt` 函数，你会发现它有点儿怪：它和这个种子本身的成员实际上并无关系！

仔细想想：我们将不同的策略实现为不同的 `PlantAt` 函数，然后借助虚函数动态绑定的机制完成了策略选择。但是，要完成策略选择，一定要借助虚函数吗？

```cpp
class GameWorld : public WorldBase {
public:
  void SetPlantStrategy(std::function<void(int, int)> strategy) {
    m_plantStrategy = strategy;
  }

  bool HasPlantStrategy() const {
    return static_cast<bool>(m_plantStrategy);
  }

  void ReleaseSelectedSeedAt(int x, int y) {
    m_plantStrategy(x, y);
    m_plantStrategy = {};
  }

private:
  std::function<void(int, int)> m_plantStrategy;
};
```

我们完全可以自己存储“函数”。可以用函数指针，也可以用 modern C++ 的 `std::function` ，后者用起来更方便一些，而且可以接受 lambda 等其它可调用对象。然后在 `Seed<PlantType>` 的 `OnClick` 里，我们向 `GameWorld::SetPlantStrategy` 传一个 lambda ：

```cpp
// 为了方便，这里我把 SeedBase 去掉了，直接让 Seed<PlantType> 继承自 GameObject 。
template <typename PlantType>
class Seed : public GameObject {
public:
  Seed(ImageID imageID, int index, GameWorld *world, int price, int cooldownTime)
      : GameObject{imageID,    130 + index * 60, WINDOW_HEIGHT - 44,   LayerID::UI,
                   SEED_WIDTH, SEED_HEIGHT,      AnimID::NO_ANIMATION, world},
        m_price{price}, m_cooldownTime{cooldownTime} {}

  void Update() override {}

  void OnClick() override {
    auto world = GetWorld();
    if (world->IsHoldingShovel() || world->HasSelectedSeed())
      return;
    if (world->GetSunlight() >= m_price) {
      world->IncreaseSunlight(-m_price);
      world->AddObject<CooldownMask>(GetX(), GetY(), world, m_cooldownTime);
      // 注意看这里！
      world->SetPlantStrategy([world](int x, int y) {
        world->AddObject<PlantType>(x, y);
      });
    }
  }

private:
  int m_price;
  int m_cooldownTime;
};
```

是不是很有趣？

实际上如果你认真读了 Homework 4 (Pacman) 的 solution ，那里其实就有一个类似的做法：

```c
void moveOneGhostNormal(Game *pGame, Ghost *pGhost) {
  // 按设定方向移动单个鬼
}

void moveOneGhostSmart(Game *pGame, Ghost *pGhost) {
  // 按最短距离移动单个鬼
}

// 移动策略，是一个函数指针
void (*moveOneGhost)(Game *, Ghost *) = &moveOneGhostNormal;

void moveGhosts(Game *pGame) {
  for (int i = pGame->ghostCnt - 1; i >= 0; --i)
    updateGrid(pGame, pGame->ghosts[i].pos, pGame->ghosts[i].itemBelow);
  for (int i = 0; i != pGame->ghostCnt; ++i) {
    moveOneGhost(pGame, pGame->ghosts + i);
    updateGrid(pGame, pGame->ghosts[i].pos, '@');
  }
}
```

我的实现采用的是方法一，因为我想要实现坚果修复术，方法一更方便。
