# C 语言学习项目

基于 Kernighan & Ritchie《The C Programming Language》（K&R C）的练习项目。

## 项目结构

```
~/c-language/
├── Makefile                  # 全局构建配置（自动发现 .c 文件）
├── README.md
├── TIPS.md                   # C89 vs 现代 C 差异速查
├── reference-book.pdf        # K&R 教材
├── bin/                      # 编译产物（已 gitignore）
├── ch01-tutorial-introduction/
│   ├── hello.c
│   ├── examples/             # 书中示例代码
│   └── exercises/            # 课后练习
├── ch02-types-operators-expressions/
├── ch03-control-flow/
├── ch04-functions-program-structure/
├── ch05-pointers-and-arrays/
├── ch06-structures/
├── ch07-input-and-output/
└── ch08-unix-system-interface/
```

- 源码（`.c`）在各章节目录下
- 编译产物统一输出到 `bin/`，不进入版本控制

## 环境要求

| 工具 | 用途 |
|------|------|
| GCC 13.3.0 | 编译器 |
| Make 4.3 | 构建工具 |
| GDB 15.0 | 调试器 |

## 编译与运行

### 使用 Make（推荐）

Makefile 会自动发现所有 `.c` 文件，编译到 `bin/` 下保持目录结构：

```bash
# 编译所有程序
make all

# 清除所有编译产物
make clean
```

### 运行程序

```bash
# 编译后的程序在 bin/ 下
bin/ch01-tutorial-introduction/hello
bin/ch01-tutorial-introduction/examples/fahr_to_celsius
```

### 单文件手动编译

```bash
# 基本编译（输出默认 a.out）
gcc hello.c

# 指定输出到 bin/
gcc -std=c17 -Wall -Wextra -pedantic -g -o bin/hello hello.c

# 链接数学库（如使用 math.h）
gcc -std=c17 -Wall -Wextra -pedantic -g -o bin/test_math test_math.c -lm
```

## GCC 常用选项

### 标准与警告

| 选项 | 说明 |
|------|------|
| `-std=c17` | 使用 C17 标准 |
| `-std=c99` | 使用 C99 标准 |
| `-Wall` | 开启常见警告 |
| `-Wextra` | 开启额外警告 |
| `-pedantic` | 严格遵循标准，不允许扩展语法 |
| `-Werror` | 将警告视为错误 |

### 调试与优化

| 选项 | 说明 |
|------|------|
| `-g` | 生成调试信息（GDB 可用） |
| `-O0` | 不优化（调试时推荐） |
| `-O1` | 基本优化 |
| `-O2` | 标准优化（发布时推荐） |
| `-O3` | 激进优化 |

### 输出控制

| 选项 | 说明 |
|------|------|
| `-o <file>` | 指定输出文件名 |
| `-c` | 只编译不链接，生成 `.o` 目标文件 |
| `-E` | 只预处理，输出宏展开结果 |
| `-S` | 生成汇编代码 `.s` 文件 |

### 多文件编译

```bash
# 一起编译
gcc -o program main.c utils.c helpers.c

# 分步编译：先编译为目标文件，再链接
gcc -c main.c
gcc -c utils.c
gcc -o program main.o utils.o
```

### 链接外部库

```bash
# 链接数学库
gcc -o program main.c -lm

# 链接 pthread 线程库
gcc -o program main.c -lpthread
```

## GDB 调试

编译时必须加 `-g` 选项：

```bash
# 启动调试
gdb ./hello

# 常用命令
(gdb) break main        # 在 main 函数设置断点
(gdb) run               # 运行程序
(gdb) next              # 单步执行（不进入函数）
(gdb) step              # 单步执行（进入函数）
(gdb) print var         # 打印变量值
(gdb) continue          # 继续运行
(gdb) quit              # 退出
```

## 注意事项

本书基于 C89 标准，编译使用 C17 标准。详细差异见 [TIPS.md](TIPS.md)，主要差异：

| 特性 | 书中写法（C89） | 现代写法（C17） |
|------|----------------|----------------|
| main 函数 | `main()` | `int main(void)` |
| 变量声明 | 在块开头声明 | 随处声明 |
| 布尔类型 | 无 | `#include <stdbool.h>` |
| for 循环初始化 | `int i; for (i = 0; ...)` | `for (int i = 0; ...)` |
| 注释 | `/* ... */` | `// ...` 也可用 |
