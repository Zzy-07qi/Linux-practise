#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#define WIDTH 40
#define HEIGHT 20

// 坐标点结构体，用于表示游戏中的位置
typedef struct {
    int x;  // x坐标
    int y;  // y坐标
} Point;

// 蛇结构体，包含蛇的身体、长度和移动方向
typedef struct {
    Point body[100];  // 蛇的身体数组，最多100节
    int length;       // 蛇的当前长度
    int dir_x;        // x方向移动增量（-1左，1右，0不动）
    int dir_y;        // y方向移动增量（-1上，1下，0不动）
} Snake;

Point food;     // 食物的位置
Snake snake;    // 蛇的实例
int score;      // 当前得分
int game_over;  // 游戏结束标志（1表示结束，0表示继续）

// 初始化游戏：设置蛇的初始位置、方向、食物位置、得分和游戏状态
void init_game() {
    snake.length = 3;  // 蛇初始长度为3
    // 蛇头位于屏幕中央，身体向左延伸
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    snake.body[1].x = WIDTH / 2 - 1;
    snake.body[1].y = HEIGHT / 2;
    snake.body[2].x = WIDTH / 2 - 2;
    snake.body[2].y = HEIGHT / 2;
    snake.dir_x = 1;  // 初始方向向右
    snake.dir_y = 0;
    
    srand(time(NULL));  // 初始化随机种子
    // 随机生成食物位置（避开边界）
    food.x = rand() % (WIDTH - 2) + 1;
    food.y = rand() % (HEIGHT - 2) + 1;
    
    score = 0;      // 初始得分0
    game_over = 0;  // 游戏未结束
}

// 绘制游戏边界：在屏幕四周绘制 '#' 字符
void draw_border() {
    // 绘制上下边界
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");           // 上边界
        mvprintw(HEIGHT - 1, i, "#");  // 下边界
    }
    // 绘制左右边界
    for (int i = 0; i < HEIGHT; i++) {
        mvprintw(i, 0, "#");           // 左边界
        mvprintw(i, WIDTH - 1, "#");   // 右边界
    }
}

// 绘制蛇：蛇头用 'O'，身体用 'o'
void draw_snake() {
    for (int i = 0; i < snake.length; i++) {
        if (i == 0) {
            mvprintw(snake.body[i].y, snake.body[i].x, "O");  // 蛇头
        } else {
            mvprintw(snake.body[i].y, snake.body[i].x, "o");  // 蛇身
        }
    }
}

// 绘制食物：用 '*' 表示
void draw_food() {
    mvprintw(food.y, food.x, "*");
}

// 绘制得分：在屏幕底部显示当前得分
void draw_score() {
    char score_str[20];
    sprintf(score_str, "Score: %d", score);  // 格式化得分字符串
    mvprintw(HEIGHT, 0, score_str);          // 显示在边界下方
}

// 移动蛇：处理蛇的移动、碰撞检测和食物吃取
void move_snake() {
    // 从蛇尾到蛇头，依次将每个身体段移动到前一段的位置
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    
    // 移动蛇头（根据当前方向）
    snake.body[0].x += snake.dir_x;
    snake.body[0].y += snake.dir_y;
    
    // 检测是否撞到边界
    if (snake.body[0].x <= 0 || snake.body[0].x >= WIDTH - 1 ||
        snake.body[0].y <= 0 || snake.body[0].y >= HEIGHT - 1) {
        game_over = 1;
        return;
    }
    
    // 检测是否撞到自己的身体
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            game_over = 1;
            return;
        }
    }
    
    // 检测是否吃到食物
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        snake.length++;  // 蛇长度增加
        score += 10;     // 得分增加10
        
        // 生成新食物（确保不在蛇身上）
        int valid = 0;
        while (!valid) {
            food.x = rand() % (WIDTH - 2) + 1;
            food.y = rand() % (HEIGHT - 2) + 1;
            valid = 1;
            // 检查食物是否与蛇身重叠
            for (int i = 0; i < snake.length; i++) {
                if (food.x == snake.body[i].x && food.y == snake.body[i].y) {
                    valid = 0;
                    break;
                }
            }
        }
    }
}

// 处理用户输入：方向键改变蛇的移动方向，Q键退出游戏
void handle_input() {
    int ch = getch();  // 获取键盘输入
    switch (ch) {
        case KEY_UP:    // 上方向键
            // 防止反向移动（当前向下时不能立即向上）
            if (snake.dir_y != 1) {
                snake.dir_x = 0;
                snake.dir_y = -1;
            }
            break;
        case KEY_DOWN:  // 下方向键
            if (snake.dir_y != -1) {
                snake.dir_x = 0;
                snake.dir_y = 1;
            }
            break;
        case KEY_LEFT:  // 左方向键
            if (snake.dir_x != 1) {
                snake.dir_x = -1;
                snake.dir_y = 0;
            }
            break;
        case KEY_RIGHT: // 右方向键
            if (snake.dir_x != -1) {
                snake.dir_x = 1;
                snake.dir_y = 0;
            }
            break;
        case 'q':       // Q键退出
        case 'Q':
            game_over = 1;
            break;
    }
}

// 主函数：游戏主循环
int main() {
    // 初始化 ncurses 库
    initscr();       // 初始化屏幕
    cbreak();        // 禁用行缓冲，立即处理输入
    noecho();        // 不回显输入字符
    keypad(stdscr, TRUE);  // 启用功能键
    curs_set(0);     // 隐藏光标
    timeout(100);    // 设置输入超时时间（毫秒）
    
    init_game();     // 初始化游戏状态
    
    // 游戏主循环
    while (!game_over) {
        clear();         // 清除屏幕
        draw_border();   // 绘制边界
        draw_snake();    // 绘制蛇
        draw_food();     // 绘制食物
        draw_score();    // 绘制得分
        refresh();       // 刷新屏幕显示
        
        handle_input();  // 处理用户输入
        move_snake();    // 移动蛇
    }
    
    // 游戏结束界面
    clear();
    mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Game Over!");  // 显示游戏结束
    char score_str[20];
    sprintf(score_str, "Score: %d", score);
    mvprintw(HEIGHT / 2 + 1, WIDTH / 2 - strlen(score_str) / 2, score_str);  // 显示最终得分
    mvprintw(HEIGHT / 2 + 2, WIDTH / 2 - 8, "Press Q to exit");  // 提示退出
    refresh();
    
    while (getch() != 'q');  // 等待用户按Q退出
    
    endwin();  // 关闭 ncurses
    return 0;
}