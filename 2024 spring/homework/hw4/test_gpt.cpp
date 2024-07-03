#include <stdio.h>
#include <unistd.h> // 用于 usleep 函数

// ANSI 转义码
#define ANSI_MOVE_CURSOR "\033[%d;%dH"

// 游戏界面大小
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20

// Pacman 当前位置
int pacmanX = 10;
int pacmanY = 5;

// 移动光标到指定位置并输出字符
void moveCursorAndPrint(int x, int y, char character) {
    printf(ANSI_MOVE_CURSOR, y + 1, x + 1); // ANSI 转义码中的坐标从1开始
    putchar(character);
    fflush(stdout); // 立即刷新输出缓冲区
}

int main() {
    // 输出初始地图
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            putchar('.');
        }
        putchar('\n');
    }

    // 主循环
    while (1) {
        // 清除 Pacman 之前的位置
        moveCursorAndPrint(pacmanX, pacmanY, ' ');

        // 移动 Pacman 示例
        pacmanX = (pacmanX + 1) % SCREEN_WIDTH;

        // 输出 Pacman 新的位置
        moveCursorAndPrint(pacmanX, pacmanY, 'P');

        // 模拟游戏速度，这里休眠一段时间
        usleep(500000); // 500毫秒
    }

    return 0;
}
