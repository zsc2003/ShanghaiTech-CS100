## 对 `utils.hpp` 的魔改

这个想法来自于一位同学代码中的 bug ：

```cpp
GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : ObjectBase(x, y, width, height, imageID, layer, animID)
```

`GameObject` 和 `ObjectBase` 等类的构造函数都有一长串的参数，稍有不慎就会传错，比如这里就错了！如果你去翻一下 `ObjectBase` 的构造函数，你会发现它的参数列表是

```cpp
ObjectBase::ObjectBase(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
```

有没有办法让编译器帮我们发现这样的错误？我们需要求助于类型系统。在 `utils.hpp` 中，我们发现 `ImageID`, `LayerID` 和 `AnimID` 实际上都是 `int` 的别名，但它们其实比普通的 `int` 具有更多的含义，不应让它们随意与 `int` 互通。

这时候， `enum` 就大显神威了。将 `utils.hpp` 中的一串常量改为 scoped enum （即 `enum class`），不仅让命名更美观，还能让上面的错误代码无法通过编译，因为 scoped enum 是不能与其底层整数类型隐式转换的。

```cpp
enum class ImageID {
  NONE = 0,
  BACKGROUND,
  SUN,
  SHOVEL,
  COOLDOWN_MASK,
  SUNFLOWER = 10,
  PEASHOOTER,
  WALLNUT,
  CHERRY_BOMB,
  REPEATER,
  WALLNUT_CRACKED,
  RED_REPEATER,
  SEED_SUNFLOWER = 20,
  SEED_PEASHOOTER,
  SEED_WALLNUT,
  SEED_CHERRY_BOMB,
  SEED_REPEATER,
  SEED_RED_REPEATER,
  REGULAR_ZOMBIE = 30,
  BUCKET_HEAD_ZOMBIE,
  POLE_VAULTING_ZOMBIE,
  PEA = 40,
  EXPLOSION,
  RED_PEA,
  ZOMBIES_WON = 100
};

enum class AnimID { NO_ANIMATION = 0, IDLE, WALK, EAT, RUN, JUMP };

const int MAX_LAYERS = 7;

enum class LayerID {
  SUN = 0,
  ZOMBIES,
  PROJECTILES,
  PLANTS,
  COOLDOWN_MASK,
  UI,
  BACKGROUND,
};

const int MS_PER_FRAME = 33;
```

注意这里的技巧，比方说 `SUNFLOWER = 10, PEASHOOTER, WALLNUT` 就意味着 `PEASHOOTER` 对应 `11` ， `WALLNUT` 对应 `12` 。
