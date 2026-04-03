#include <stdio.h>
#include <assert.h>
#include <math.h>

// 浮点版本的温度转换
float to_celsius_f(float fahr)
{
    return (fahr - 32.0f) * (5.0f / 9.0f);
}

// 整数版本的温度转换
int to_celsius_i(int fahr)
{
    return 5 * (fahr - 32) / 9;
}

// 浮点比较：允许 0.01 的误差
#define FLOAT_EQ(a, b) (fabsf((a) - (b)) < 0.01f)

int main(void)
{
    // === 浮点精度测试 ===

    // 1. 冰点：32°F = 0°C（精确）
    assert(FLOAT_EQ(to_celsius_f(32.0f), 0.0f));

    // 2. 沸点：212°F = 100°C（精确）
    assert(FLOAT_EQ(to_celsius_f(212.0f), 100.0f));

    // 3. 华氏=摄氏 交叉点：-40°F = -40°C（精确）
    assert(FLOAT_EQ(to_celsius_f(-40.0f), -40.0f));

    // 4. 100°F = 37.78°C（浮点保留了小数精度）
    assert(FLOAT_EQ(to_celsius_f(100.0f), 37.78f));

    // 5. 0°F = -17.78°C（对比整数版本截断为 -17）
    assert(FLOAT_EQ(to_celsius_f(0.0f), -17.78f));
    assert(to_celsius_i(0) == -17);

    // 6. 整数除法陷阱验证：5/9 == 0（整数），5.0f/9.0f ≈ 0.556（浮点）
    assert(5 / 9 == 0);
    assert(FLOAT_EQ(5.0f / 9.0f, 0.5556f));

    // 7. 浮点 vs 整数精度差异对比
    //    68°F：精确值 20.0°C
    assert(FLOAT_EQ(to_celsius_f(68.0f), 20.0f));
    assert(to_celsius_i(68) == 20);    // 整数版恰好也是 20

    //    100°F：精确值 37.78°C
    assert(FLOAT_EQ(to_celsius_f(100.0f), 37.78f));
    assert(to_celsius_i(100) == 37);   // 整数版丢失了 .78

    //    300°F：精确值 148.89°C
    assert(FLOAT_EQ(to_celsius_f(300.0f), 148.89f));
    assert(to_celsius_i(300) == 148);  // 整数版丢失了 .89

    // 8. 负温度：-40°F 两种版本结果一致
    assert(FLOAT_EQ(to_celsius_f(-40.0f), -40.0f));
    assert(to_celsius_i(-40) == -40);

    printf("All 8 tests passed!\n");
    return 0;
}
