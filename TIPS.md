# C89 vs 现代 C 差异速查

本文档记录 K&R 教材（基于 C89/C90）与现代 C 标准（C99/C17/C23）之间的关键差异。
学习过程中遇到新的差异会持续追加。

---

## 1. 函数声明与定义

### 1.1 空参数列表

```c
// C89: 参数未指定，编译器不检查传参
int main()

// 现代 C: 明确零参数，传参会报错（推荐）
int main(void)
```

### 1.2 函数声明风格

```c
// C89 旧式声明（K&R 风格）
int add(a, b)
int a;
int b;
{
    return a + b;
}

// 现代 C: 函数原型（推荐）
int add(int a, int b)
{
    return a + b;
}
```

> C23 起旧式声明已被彻底移除，必须使用函数原型。

### 1.3 隐式 int

```c
// C89: 缺少类型默认为 int
foo() { return 0; }

// C99 起: 不允许，必须显式写明类型
int foo(void) { return 0; }
```

---

## 2. 变量声明

### 2.1 声明位置

```c
// C89: 必须在块的开头声明所有变量
void func(void) {
    int i;    /* 必须在最前面 */
    int sum;
    sum = 0;
    for (i = 0; i < 10; i++) { ... }
}

// C99 起: 可以在任意位置声明
void func(void) {
    int sum = 0;
    for (int i = 0; i < 10; i++) { ... }  // for 内声明
}
```

---

## 3. 注释

```c
// C89: 只有块注释
/* this is a comment */

// C99 起: 增加行注释（推荐用于简短注释）
// this is a comment
```

---

## 4. 布尔类型

```c
// C89: 没有布尔类型，用 int 模拟
int flag = 1;  /* true */
if (flag) { ... }

// C99 起: 提供 _Bool 和 <stdbool.h>
#include <stdbool.h>
bool flag = true;
if (flag) { ... }
```

> `true` = 1, `false` = 0, `bool` 实际是 `_Bool` 的宏别名。

---

## 5. main 函数返回值

```c
// C89: 必须显式 return
int main(void) {
    printf("hello\n");
    return 0;
}

// C99 起: 到达末尾时隐式返回 0，可省略 return
int main(void) {
    printf("hello\n");
    // 隐式 return 0;
}
```

---

## 6. 格式化字符串

### 6.1 long long 类型

```c
// C89: 无 long long
// C99 起: 新增 long long (至少 64 位)
long long x = 9223372036854775807LL;
printf("%lld\n", x);
```

### 6.2 size_t 的打印

```c
// C89: 通常用 %lu 或 %d（不严谨）
printf("%lu\n", (unsigned long)sizeof(int));

// C99 起: 使用 %zu（推荐）
printf("%zu\n", sizeof(int));
```

---

## 7. 可变长数组 VLA

```c
// C89: 数组大小必须是编译期常量
int arr[100];

// C99: 允许运行时确定大小
int n = 10;
int arr[n];

// 注意: VLA 在 C11 变为可选特性，C23 重新强制支持
```

---

## 8. 结构体初始化

```c
// C89: 只能按顺序初始化
struct Point { int x; int y; };
struct Point p = { 1, 2 };

// C99 起: 支持指定成员初始化（推荐）
struct Point p = { .y = 2, .x = 1 };
```

---

## 9. 整数除法 vs 浮点除法

> 来源：ch01 §1.2 温度转换练习

```c
// 整数除法：两个操作数都是 int，结果截断为整数
int a = 5 / 9;       // a = 0
int b = 5 * (68-32) / 9;  // b = 20（先乘后除减少精度损失）

// 浮点除法：只要有一个操作数是浮点，整个运算就是浮点运算
float c = 5.0f / 9.0f;     // c = 0.555...
float d = 5.0f / 9;        // c = 0.555...（int 9 隐式转为 float）
float e = (float)5 / 9;    // e = 0.555...（显式转型也可以）
```

**关键规则：** 运算类型由操作数类型决定，与赋值目标类型无关。

```c
// 错误：右边是整数除法，5/9=0，再赋给 float 也是 0.0
float result = (fahr - 32) * (5 / 9);     // result = 0.0

// 正确：用浮点字面量
float result = (fahr - 32.0f) * (5.0f / 9.0f);
```

---

## 10. 其他重要新增特性（书中未涉及）

| 特性 | 标准 | 简述 |
|------|------|------|
| `<stdint.h>` | C99 | 固定宽度整数类型 `int32_t` 等 |
| `<inttypes.h>` | C99 | 固定宽度类型的 printf/scanf 格式 |
| 复合字面量 | C99 | `(struct Point){ .x = 1, .y = 2 }` |
| 变参宏 | C99 | `__VA_ARGS__` |
| `_Generic` | C11 | 泛型选择（类似函数重载） |
| `_Static_assert` | C11 | 编译期静态断言 |
| `<threads.h>` | C11 | 多线程支持 |
| `constexpr` | C23 | 编译期常量 |
| `nullptr` | C23 | 类型安全的空指针常量 |

---

## 变更日志

| 日期 | 新增条目 |
|------|---------|
| 2026-04-02 | 初始版本：函数声明、变量声明、注释、布尔类型、main 返回值、格式化字符串、VLA、结构体初始化、其他新增特性 |
| 2026-04-03 | §9 整数除法 vs 浮点除法（来源：ch01 §1.2 温度转换） |
