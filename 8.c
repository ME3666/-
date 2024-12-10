#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义棋盘大小
#define SIZE 3

// 定义目标状态
int target[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// 定义步数和开始时间
int steps = 0;
clock_t start_time;

// 清除屏幕（Windows系统使用 system("cls")）
void clear_screen() {
    system("cls"); // Windows系统
}

// 打印棋盘
void print_board(int board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf("   "); // 空白格子
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 检查棋盘是否达到目标状态
int is_solved(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != target[i][j]) {
                return 0; // 如果有一个数字不匹配，说明没有解决
            }
        }
    }
    return 1; // 如果所有数字都匹配，游戏结束
}

// 查找空白位置（0的位置）
void find_blank(int board[SIZE][SIZE], int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// 交换两个数字块
void swap(int board[SIZE][SIZE], int r1, int c1, int r2, int c2) {
    int temp = board[r1][c1];
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = temp;
}

// 移动空白块
int move_blank(int board[SIZE][SIZE], char move) {
    int row, col;
    find_blank(board, &row, &col);
    int valid_move = 0;

    switch (move) {
    case 'w': // 上
        if (row > 0) {
            swap(board, row, col, row - 1, col);
            valid_move = 1;
        }
        break;
    case 's': // 下
        if (row < SIZE - 1) {
            swap(board, row, col, row + 1, col);
            valid_move = 1;
        }
        break;
    case 'a': // 左
        if (col > 0) {
            swap(board, row, col, row, col - 1);
            valid_move = 1;
        }
        break;
    case 'd': // 右
        if (col < SIZE - 1) {
            swap(board, row, col, row, col + 1);
            valid_move = 1;
        }
        break;
    default:
        printf("无效的输入！\n");
        break;
    }

    return valid_move;
}

// 计算逆序数
int count_inversions(int board[SIZE][SIZE]) {
    int inversions = 0;
    int arr[SIZE * SIZE];

    // 把二维棋盘展平成一维数组
    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[idx++] = board[i][j];
        }
    }

    // 计算逆序数
    for (int i = 0; i < SIZE * SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE * SIZE; j++) {
            if (arr[i] != 0 && arr[j] != 0 && arr[i] > arr[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

// 检查棋盘是否可解
int is_solvable(int board[SIZE][SIZE]) {
    int inversions = count_inversions(board);
    return inversions % 2 == 0; // 可解的逆序数是偶数
}

// 生成一个随机打乱的初始棋盘
void shuffle_board(int board[SIZE][SIZE]) {
    int nums[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        nums[i] = i;
    }

    // 打乱数字顺序
    srand(time(NULL));
    do {
        for (int i = 0; i < SIZE * SIZE; i++) {
            int j = rand() % (SIZE * SIZE);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }

        // 填充棋盘
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = nums[i * SIZE + j];
            }
        }
    } while (!is_solvable(board)); // 重新打乱直到得到可解的棋盘
}

// 游戏主程序
int main() {
    int board[SIZE][SIZE];
    shuffle_board(board);

    printf("数字华容道游戏开始！\n");
    printf("目标状态：\n");
    print_board(target);

    // 记录游戏开始时间
    start_time = clock();

    while (1) {
        clear_screen(); // 每次输入后清除屏幕

        print_board(board);

        if (is_solved(board)) {
            // 游戏完成，打印步数和时间
            printf("恭喜你，成功完成华容道！\n");
            clock_t end_time = clock();
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("游戏完成！\n");
            printf("步数：%d\n", steps);
            printf("耗时：%.2f 秒\n", time_taken);
            break;
        }

        printf("请通过 'w' 上, 's' 下, 'a' 左, 'd' 右 来移动空白块: ");
        char move;
        move = getchar(); // 获取用户输入
        while (getchar() != '\n'); // 清除缓冲区中的多余字符

        if (move_blank(board, move)) {
            steps++; // 增加步数
        }
        else {
            printf("无效的移动，请重新输入！\n");
        }
    }

    return 0;
}
