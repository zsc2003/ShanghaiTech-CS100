## 在游戏世界中创建对象

我们需要在 `GameWorld` 里开一个列表来存储游戏中的对象，这个列表显然应该是 `SomeContainer<SomePointerToGameObject>` ，其中 `SomeContainer` 可以是 `std::vector` 或 `std::list` ， `SomePointerToGameObject` 应该是指向 `GameObject` 的某种指针。

对于 `SomeContainer` ，出题人和绝大多数同学的选择是 `std::list` ，这是没有问题的。由于我们要在游戏过程中删除这个列表里的死亡的游戏对象，最好选择一个支持在任意位置快速删除元素的数据结构，那么链表显然是符合要求的。 `std::vector` 也没有太大问题——一共也没几个对象，并不需要太担心 `std::vector` 在中间删除元素带来的时间开销。但需要注意的是 `std::vector` 的插入/删除操作可能会导致迭代器、指针、引用失效，而 `std::list` 不会。

对于 `SomePointerToGameObject` ，出题人和绝大多数同学的选择是 `std::shared_ptr<GameObject>` ，这和我的选择是不同的。 `std::shared_ptr` 是一种较为保守的选择，但在这里是没有必要的，我的选择是 `std::unique_ptr` 。

我们首先要明白一点：所有指针都应该被替换为智能指针吗？

答案是否定的。指针的用途有很多，管理对象的内存只是它的诸多用途中的一个，这也是在 modern C++ 下应该由智能指针完成的那一个。指针的最基本的用途是**指向一个对象**，它可以让我们拿到那个对象，对那个对象做一些操作；它可以充当一种“迭代器”，让我们一个接一个地访问一列对象。在这些使用场景中，智能指针不仅无法发挥作用，反而是累赘。

我们可以简单地把指针与它所指向的对象的关系分为两类：管理者、观察者。那些管理着它所指向的对象的内存的指针是管理者，不参与这种内存管理的是观察者。如果一个对象仅有一个管理者，这个管理者就应该是 `std::unique_ptr` ；如果有多个管理者，这些管理者就应该是 `std::shared_ptr` 。那观察者应该是什么呢？曾经有人提出了一个 [`std::observer_ptr`](https://en.cppreference.com/w/cpp/experimental/observer_ptr) ，但是[被 Bjarne Stroustrup 反驳了](https://open-std.org/JTC1/SC22/WG21/docs/papers/2019/p1408r0.pdf) ，老爷子在最后写了一句：

> If you need a pointer representing non-ownership, I suggest:
> 
> ```cpp
> template <typename T> using observer_ptr = T*;
> ```

也就是说，最适合“观察者”这一身份的，就是裸指针，当然，还可以是引用。不过这里我们完全忘记了 `std::weak_ptr` ，它在 CS100 的课件中也没有出现。如果你有兴趣，可以上网查查什么时候需要 `std::weak_ptr` ，反正在这个项目中我们是不需要的。

回到代码本身。我们在 `GameWorld` 中添加了一个成员 `std::list<std::unique_ptr<GameObject>> m_objects` ，我的观点是**所有游戏对象都应该由 `m_objects` 里的这些指针管理**，其它的指针都是观察者。例如，判断两个对象是否产生碰撞的函数应该具有下面的形式

```cpp
bool CollisionHappens(const GameObject &a, const GameObject &b); // 或者 const GameObject *
```

而不是

```cpp
bool CollisionHappens(std::shared_ptr<GameObject> a, std::shared_ptr<GameObject> b);
```

再比如，一些同学用一个指向种子基类的指针来表示“当前选中的种子”，这个指针当然就应该是裸指针。它只是用来告诉我们“谁被选中了”而已，凭什么参与种子的内存管理？

破除了对智能指针的错误认识之后，很多问题就不难理解了。比如，在很多游戏对象中我们都需要存储指向 `GameWorld` 的指针，这个指针应该是什么指针？当然是裸指针！游戏对象是游戏世界创建并管理着的，你却想让它反过来管理游戏世界，这不是倒反天罡了吗？

于是，整个项目中，除了 `Framework` 之外就没有 `shared_ptr` 的用武之地了， `enable_shared_from_this` 和 `shared_from_this()` 也完全不需要了。

为了让别人能够创建游戏对象并添加到 `m_objects` 中去，我提供了一组接口 `AddObject` ：

```cpp
class GameWorld : public WorldBase {
public:
  void AddObject(std::unique_ptr<GameObject> object) {
    m_objects.push_back(std::move(object));
  }

  template <typename T, typename... Args>
  void AddObject(Args &&...args) {
    AddObject(std::make_unique<T>(std::forward<Args>(args)...));
  }

private:
  std::list<std::unique_ptr<GameObject>> m_objects;
};
```

起初我只写了第一个 `AddObject` ，后来发现我频繁地需要 `AddObject(std::make_unique<...>(...))` ，于是我就又写了第二个 `AddObject` ，那么我就只要 `AddObject<...>(...)` 即可完成创建+添加两件事了。

## 让游戏对象访问游戏世界

许多游戏对象都需要访问游戏世界，因为它们想要消耗阳光、检查僵尸是否存在、生成子弹等等。

### 方法一

上文已经提到，一种简单的办法就是在 `GameObject` 里存一个 `GameWorld *` ：

```cpp
class GameObject : public ObjectBase {
public:
  GameObject(GameWorld *world, /* 一些别的参数 ... */)
      : ObjectBase{/* ... */}, m_world{world} {}

  auto GetWorld() const { return m_world; }

  // ...

private:
  GameWorld *m_world;
};
```

任何游戏对象的构造函数都需要带上 `GameWorld *` ，比如

```cpp
class SunflowerSeed : public GameObject {
public:
  SunflowerSeed(int x, int y, GameWorld *world)
      : GameObject{world, /* 其它参数 ... */}, /* 其它成员 ... */ {}
  // ...
};
```

注意，访问游戏世界的方式是 `GetWorld()` 而非 `m_world` ，因为 `m_world` 是 private 的。我仍然不建议将 `m_world` 或者任何数据成员设为 protected 。 protected 成员的封装性和 public 成员的封装性是一样弱的——任何人只要认我做爹，就能访问我的 protected 成员。

在创建游戏对象的时候，当然要传入游戏世界的指针，比如

```cpp
void GameWorld::Init() {
  // ...

  m_objects.push_back(std::make_unique<SunflowerSeed>(/* x, y, */ this));

  // ...
}
```

对于“在 `GameObject` 中存储 `GameWorld *` ”这件事，一些同学有异议，他们的理由是像 `Background` （背景图片）这样的对象是完全不需要访问游戏世界的。但是，像 `Background` 这样的不需要访问游戏世界的对象究竟还有多少个？显然， `Background` 这种 trivial 的对象完全是特例，它不值得我们为之改变整体的设计。出于类似的原因，我还在 `GameObject` 中用一个成员 `int m_hp` 表示血量，因为绝大多数游戏对象都有血量，或者至少有“生”和“死”两种状态之分。

### 方法二

我们发现，在任何时刻其实都只有一个游戏世界在运行，那干嘛还要到每个游戏对象里存一个 `GameWorld *` 呢？我们当然可以在全局存一个 `GameWorld *` ，假设命名为 `g_world` 。问题是，现在我们有很多个 `.cpp` 文件和很多个 `.hpp` 文件，应该把 `g_world` 定义在哪个文件里？

定义在 `.hpp` 里是绝对不行的，因为它会被多个 `.cpp` 所包含。这些 `.cpp` 文件分别被编译，得到多个目标文件，这每一个目标文件里就都有了一个 `g_world` ，当这些目标文件被链接在一起时就违反了 One Definition Rule ——一个变量或函数应有且仅有一个定义。

所以，它应该被定义在一个 `.cpp` 里，这里我建议选 `main.cpp` 或 `GameWorld.cpp` ，比如：

```cpp
// main.cpp:
#include <memory>

#include "pvz/Framework/GameManager.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

GameWorld *g_world;

int main(int argc, char **argv) {
  auto world = std::make_shared<GameWorld>();
  g_world = world.get();
  GameManager::Instance().Play(argc, argv, world);
}
```

但是这样的话，怎么让别的文件访问 `g_world` 呢？一种办法是使用 `extern` 关键字来声明一个变量。

```cpp
// Plants.cpp:
extern GameWorld *g_world;

void CherryBomb::Update() {
  if (--m_explodeTimer == 0) {
    g_world->AddObject<Explosion>(GetX(), GetY()); // 构造游戏对象时无需再传 GameWorld * 了。
    SetDead();
  }
}
```

`extern GameWorld *g_world;` 这句话意思是说：这个名为 `g_world` 的、类型为 `GameWorld *` 的变量是存在的，只是它的定义可能在别处。此前，我们从来没有谈过变量的声明和定义的区别，像 `int x;` 这样的语句既是对 `x` 的声明也是对 `x` 的定义。但在这里， `extern GameWorld *g_world;` 仅仅是对 `g_world` 的声明，它的定义在 `main.cpp` 里。

还有一种办法，是为 `g_world` 提供“getter”。我们可以在 `utils.hpp` 这样的几乎所有文件都会包含的头文件里声明一个函数：

```cpp
// utils.hpp

class GameWorld; // 需要对 GameWorld 进行声明，但是别乱 #include 。

GameWorld *GetGameWorld();
```

然后在 `main.cpp` 里定义它：

```cpp
// main.cpp:
#include <memory>

#include "pvz/Framework/GameManager.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

GameWorld *g_world;

GameWorld *GetGameWorld() {
  return g_world;
}

int main(int argc, char **argv) {
  auto world = std::make_shared<GameWorld>();
  g_world = world.get();
  GameManager::Instance().Play(argc, argv, world);
}
```

这样一来，所有文件都可以调用 `GetGameWorld()` 来访问 `g_world` 。

### 方法三

既然注意到了只存在一个 `GameWorld` 对象，是不是可以用单例模式呢？当然是可以的。如果你忘记了什么是单例模式，可以去复习一下课件，在讲到 `static` 成员的时候有讲；或者直接看 `GameManager` 这个现成的例子，它就是用单例模式的。

你可能会有疑问： `GameManager` 的 `Play` 接受的第三个参数是一个 `shared_ptr` ，这该怎么和单例模式配合起来呢？如果我们把单例模式实现成这样：

```cpp
class GameWorld : public WorldBase {
public:
  static GameWorld Instance() {
    static GameWorld world;
    return world;
  }
};
```

那这个 `world` 就不是由 `shared_ptr` 管理的，就不好传给 `GameManager::Play` 了。既然这样，我们当然可以：

```cpp
class GameWorld : public WorldBase {
public:
  static std::shared_ptr<GameWorld> Instance() {
    static std::shared_ptr<GameWorld> world = std::make_shared<GameWorld>();
    return world;
  }
};
```

直接让 `shared_ptr` 管理这个实例。

其实想到这儿，你肯定已经意识到一个问题：能不能不用 `shared_ptr` 管理这个 `GameWorld` ，甚至，能不能干脆不用动态内存？肯定是可以的，不过这就得改改 Framework 里的东西了。
