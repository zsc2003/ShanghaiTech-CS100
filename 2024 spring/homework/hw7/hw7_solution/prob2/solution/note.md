此题没有设编译时检查，主要有以下几方面的考虑：

1. 出题时的思考、设计、实现花了很多时间，当时已经晚于第一题发布近一周，时间比较紧张。
2. 此题的代码不复杂，在实现方式上应该不会出现什么牛鬼蛇神。
3. 就代码和习惯而言，我们认为在之前的题目的基础上，一些明显的（并且也是容易检查的）不好的习惯应该已经被排除。

但事实上，此题至少有两处值得注意的点，而在大家提交的代码中我们几乎没有看到做得好的。

1. `visit(Variable &)`, `visit(IntegerConstant &)`, `visit(FloatConstant &)` 和 `visit(BooleanConstant &)` 到底应该怎么实现？既然 variables 和 constants 的类型都是在构造时就设定好的，那么这四个函数应该什么都不做。一些人写的 `a.setType(a.getType())` **完全是画蛇添足**。
   
   但是，真的什么都不用做吗？之所以可以什么都不做，是因为我们有一个**假定：这几个结点的类型在此时应该已经计算好了，而且 `Constant<T, ET>` 的类型正是 `ET`** 。任何时候，当你的代码因为某些假定而看起来非同寻常的时候，**你就应该 `assert` 这个假定**，除非它复杂到难以写出来。

   所以，这几个函数可以写成这样：
   
   ```cpp
   void visit([[maybe_unused]] Variable &v) override {
     // The type of Variable should be set during initialization.
     assert(v.getType() == ET::Integer ||
            v.getType() == ET::Boolean ||
            v.getType() == ET::Float);
   }
   void visit([[maybe_unused]] IntegerConstant &c) override {
     // The type of IntegerConstant should be set during initialization.
     assert(c.getType() == ET::Integer);
   }
   void visit([[maybe_unused]] FloatConstant &c) override {
     // The type of FloatConstant should be set during initialization.
     assert(c.getType() == ET::Float);
   }
   void visit([[maybe_unused]] BooleanConstant &c) override {
     // The type of BooleanConstant should be set during initialization.
     assert(c.getType() == ET::Boolean);
   }
   ```

   这里为什么要用 `[[maybe_unused]]` ？因为如果这个程序被编译时定义了 `NDEBUG` 宏（比如在 GCC 下带有 `-DNDEBUG` 参数）（典型情况就是 CMake 的 Release 模式），那么所有 `assert` 都会被预处理器删掉，这时这里的参数 `v` 和 `c` 就都是 unused parameter 了。这个例子跟第一题文档末尾的例子有异曲同工之妙。这也告诉我们：你大可以在 `assert` 里做很复杂的事情，完全不必担心效率问题，因为你可以“一键”把所有 `assert` 去掉。

2. 我们在题目里说，这些类型检查规则暗含了类型之间的一些关系。一个显然的关系就是 **`Integer` 可以被视为能隐式转换为 `Float`** ，但事实上还可以再上一层，我们可以定义所谓的 **common type** ：比如 `Integer` 和 `Float` 的 common type 是 `Float` ， 两个相同的类型的 common type 仍然是这个类型等等。扩展一下，在常见的更庞大的类型系统中，我们可以用这种方式给类型定义一个**序关系**，比如 $T\leqslant U$ 当且仅当 $T$ 可以隐式转换为 $U$ 。那么所谓的 common type 其实就是两个类型的 **least upper bound** ：
   
   $$
   C=A\sqcup B\iff (A\leqslant C)\land(B\leqslant C)\land(\forall D(((A\leqslant D)\land(B\leqslant D))\implies (C\leqslant D)))
   $$

   比如，本题的 `EqualityOp` 的类型是 `Boolean` 的充要条件，就是两个运算对象的类型的 common type 存在； `ConditionalOp` 的类型，其实就是 true 部分和 false 部分两个子表达式的类型的 common type 。当然，本题的 common type 计算十分简单。

   此外， $\{\mathtt{Integer},\mathtt{Float}\}$ 这个集合被反复地提及，显然它就是“算术类型”的意思。

   如果将这些东西都考虑清楚了，不仅思路会非常清晰，代码也简洁而不易出错，每个函数就 5 行左右，不存在大量的复制粘贴和各种“特殊判断”。

   具体的实现请看代码。
