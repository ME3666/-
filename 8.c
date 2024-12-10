#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �������̴�С
#define SIZE 3

// ����Ŀ��״̬
int target[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// ���岽���Ϳ�ʼʱ��
int steps = 0;
clock_t start_time;

// �����Ļ��Windowsϵͳʹ�� system("cls")��
void clear_screen() {
    system("cls"); // Windowsϵͳ
}

// ��ӡ����
void print_board(int board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf("   "); // �հ׸���
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ��������Ƿ�ﵽĿ��״̬
int is_solved(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != target[i][j]) {
                return 0; // �����һ�����ֲ�ƥ�䣬˵��û�н��
            }
        }
    }
    return 1; // ����������ֶ�ƥ�䣬��Ϸ����
}

// ���ҿհ�λ�ã�0��λ�ã�
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

// �����������ֿ�
void swap(int board[SIZE][SIZE], int r1, int c1, int r2, int c2) {
    int temp = board[r1][c1];
    board[r1][c1] = board[r2][c2];
    board[r2][c2] = temp;
}

// �ƶ��հ׿�
int move_blank(int board[SIZE][SIZE], char move) {
    int row, col;
    find_blank(board, &row, &col);
    int valid_move = 0;

    switch (move) {
    case 'w': // ��
        if (row > 0) {
            swap(board, row, col, row - 1, col);
            valid_move = 1;
        }
        break;
    case 's': // ��
        if (row < SIZE - 1) {
            swap(board, row, col, row + 1, col);
            valid_move = 1;
        }
        break;
    case 'a': // ��
        if (col > 0) {
            swap(board, row, col, row, col - 1);
            valid_move = 1;
        }
        break;
    case 'd': // ��
        if (col < SIZE - 1) {
            swap(board, row, col, row, col + 1);
            valid_move = 1;
        }
        break;
    default:
        printf("��Ч�����룡\n");
        break;
    }

    return valid_move;
}

// ����������
int count_inversions(int board[SIZE][SIZE]) {
    int inversions = 0;
    int arr[SIZE * SIZE];

    // �Ѷ�ά����չƽ��һά����
    int idx = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[idx++] = board[i][j];
        }
    }

    // ����������
    for (int i = 0; i < SIZE * SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE * SIZE; j++) {
            if (arr[i] != 0 && arr[j] != 0 && arr[i] > arr[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

// ��������Ƿ�ɽ�
int is_solvable(int board[SIZE][SIZE]) {
    int inversions = count_inversions(board);
    return inversions % 2 == 0; // �ɽ����������ż��
}

// ����һ��������ҵĳ�ʼ����
void shuffle_board(int board[SIZE][SIZE]) {
    int nums[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; i++) {
        nums[i] = i;
    }

    // ��������˳��
    srand(time(NULL));
    do {
        for (int i = 0; i < SIZE * SIZE; i++) {
            int j = rand() % (SIZE * SIZE);
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }

        // �������
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = nums[i * SIZE + j];
            }
        }
    } while (!is_solvable(board)); // ���´���ֱ���õ��ɽ������
}

// ��Ϸ������
int main() {
    int board[SIZE][SIZE];
    shuffle_board(board);

    printf("���ֻ��ݵ���Ϸ��ʼ��\n");
    printf("Ŀ��״̬��\n");
    print_board(target);

    // ��¼��Ϸ��ʼʱ��
    start_time = clock();

    while (1) {
        clear_screen(); // ÿ������������Ļ

        print_board(board);

        if (is_solved(board)) {
            // ��Ϸ��ɣ���ӡ������ʱ��
            printf("��ϲ�㣬�ɹ���ɻ��ݵ���\n");
            clock_t end_time = clock();
            double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("��Ϸ��ɣ�\n");
            printf("������%d\n", steps);
            printf("��ʱ��%.2f ��\n", time_taken);
            break;
        }

        printf("��ͨ�� 'w' ��, 's' ��, 'a' ��, 'd' �� ���ƶ��հ׿�: ");
        char move;
        move = getchar(); // ��ȡ�û�����
        while (getchar() != '\n'); // ����������еĶ����ַ�

        if (move_blank(board, move)) {
            steps++; // ���Ӳ���
        }
        else {
            printf("��Ч���ƶ������������룡\n");
        }
    }

    return 0;
}
