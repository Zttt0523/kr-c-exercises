#include <stdio.h>
#include <assert.h>

// 公式：celsius = 5 * (fahr - 32) / 9（整数运算）
int to_celsius(int fahr)
{
    return 5 * (fahr - 32) / 9;
}

int main(void)
{
    // === 测试用例 ===

    // 1. 冰点：32°F = 0°C（精确值）
    assert(to_celsius(32) == 0);

    // 2. 沸点：212°F = 100°C（精确值）
    assert(to_celsius(212) == 100);

    // 3. 绝对零度：-459.67°F ≈ -273°C
    assert(to_celsius(-460) == -273);

    // 4. 0°F = -17°C（截断，实际 -17.78）
    assert(to_celsius(0) == -17);

    // 5. 100°F = 37°C（截断，实际 37.78）
    assert(to_celsius(100) == 37);

    // 6. 负温度：-40°F = -40°C（精确值，华氏=摄氏）
    assert(to_celsius(-40) == -40);

    // 7. 对称性验证：5 * (fahr-32) 和 (fahr-32) * 5 结果相同
    assert(5 * (68 - 32) / 9 == (68 - 32) * 5 / 9);

    // 8. 整数截断方向验证：100°F
    //   精确值 = 5 * 68 / 9 = 340 / 9 = 37.777...
    //   整数结果 = 37（向零截断）
    assert(to_celsius(100) == 37);

    printf("All 8 tests passed!\n");
    return 0;
}
