#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MS_SIZE 8 //ゲームボードのサイズ

int main(void)
{
    while (1)
    {
        int mode;                         //モードを保持
        int number_of_mines;              //地雷数のデフォルト値は10
        int mine_map[MS_SIZE][MS_SIZE];   //地雷セルと数字セルを記録
        int game_board[MS_SIZE][MS_SIZE]; //ゲームの進行を記録するためのゲームボード
        int i, j;                         //iがy座標、jがx座標
        int mine = 0;

        srand((unsigned)time(NULL)); //time関数で現在時刻を取得し、乱数を初期化する。

        /*オプション1*/
        printf("地雷の数を1~63個で入力してください。\n");

        do
        {
            scanf("%d", &number_of_mines);
            if ((number_of_mines < 1) || (number_of_mines > 63))
            {
                printf("1~63で入力してください。\n");
            }
        } while ((number_of_mines < 1) || (number_of_mines > 63));

        /* 課題1 地雷をランダムにセット */

        for (i = 0; i < MS_SIZE; i++)
        {
            for (j = 0; j < MS_SIZE; j++)
            {
                mine_map[i][j] = 0;
                game_board[i][j] = 0;
            }
        }
        while (mine != number_of_mines)
        {
            int i = rand() % MS_SIZE;
            int j = rand() % MS_SIZE;
            if (mine_map[i][j] != -1)
            {
                mine_map[i][j] = -1;
                mine++;
            }
        }

        /*　課題2 各セルの8近傍の地雷をカウント */
        for (i = 0; i < MS_SIZE; i++)
        {
            for (j = 0; j < MS_SIZE; j++)
            {
                if (mine_map[i][j] == -1)
                {
                    continue;
                }
                int target_i = -1;
                int target_j = -1;
                int count = 0;
                for (target_i = -1; target_i <= 1; target_i++)
                {
                    if ((i + target_i) < 0 || (i + target_i) >= MS_SIZE)
                        continue;
                    for (target_j = -1; target_j <= 1; target_j++)
                    {
                        if (target_i == 0 && target_j == 0)
                            continue;
                        if ((j + target_j) < 0 || (j + target_j) >= MS_SIZE)
                            continue;
                        if (mine_map[i + target_i][j + target_j] == -1)
                            count += 1;
                    }
                }
                mine_map[i][j] = count;
            }
        }

        /* printf("[y]\n\n");
        for (i = 0; i < MS_SIZE; i++)
        {
            printf("%d|", i);
            for (j = 0; j < MS_SIZE; j++)
            {
                printf("%2d", mine_map[i][j]);
            }
            printf("\n");
        }
        printf("  ");
        for (i = 0; i < MS_SIZE; i++)
        {
            printf("--");
        }
        printf("\n");
        printf("  ");
        for (j = 0; j < MS_SIZE; j++)
        {
            printf("%2d", j);
        }
        printf("   [x]\n");

        printf("[y]\n\n");
        for (i = 0; i < MS_SIZE; i++)
        {
            printf("%d|", i);
            for (j = 0; j < MS_SIZE; j++)
            {
                printf(" ");
                if (game_board[i][j] == 0)
                {
                    printf("x");
                }
                else if (game_board[i][j] == 1)
                {
                    printf(" ");
                }
                else if (game_board[i][j] == 2)
                {
                    printf("F");
                }
                else
                {
                    printf("%2d", mine_map[i][j]);
                }
            }
            printf("\n");
        }
        printf("  ");
        for (i = 0; i < MS_SIZE; i++)
        {
            printf("--");
        }
        printf("\n");
        printf("  ");
        for (j = 0; j < MS_SIZE; j++)
        {
            printf("%2d", j);
        }
        printf("   [x]\n"); */

        while (1)
        {
            printf("モードを選択してください: セルを開く (1), フラグを設置/除去する (2): ");
            scanf("%d", &mode);
            while (mode != 1 && mode != 2)
            {
                printf("1か2を入力してください。: ");
                scanf("%d", &mode);
            }

            printf("セルを選択してください。\n");
            printf("x:");
            scanf("%d", &j);
            printf("y:");
            scanf("%d", &i);

            if (mode == 1)
            {
                /* 課題3 */
                int l, m;
                if (mine_map[i][j] == -1)
                {
                    printf("ゲームオーバー\n");
                    break;
                }

                for (l = i - 1; l <= i + 1; l++)
                {
                    if (l < 0 || l >= MS_SIZE)
                        continue;
                    for (m = j - 1; m <= j + 1; m++)
                    {
                        if (m == i && l == j)
                        {
                            game_board[i][j] = 1;
                        }
                        if (m < 0 || m >= MS_SIZE)
                            continue;
                        if (game_board[l][m] == 2)
                        {
                            game_board[l][m] = 2;
                        }
                        else if (mine_map[l][m] != -1)
                        {
                            game_board[l][m] = 1;
                        }
                        else
                        {
                            game_board[l][m] = 0;
                        }
                    }
                }
            }
            else
            {
                if (game_board[i][j] != 2)
                {
                    game_board[i][j] = 2;
                }
                else
                {
                    game_board[i][j] = 0;
                }
            }
            printf("[y]\n\n");
            for (i = 0; i < MS_SIZE; i++)
            {
                printf("%d|", i);
                for (j = 0; j < MS_SIZE; j++)
                {
                    printf(" ");
                    if (game_board[i][j] == 0)
                    {
                        printf("x");
                    }
                    else if (game_board[i][j] == 2)
                    {
                        printf("F");
                    }
                    else if (mine_map[i][j] != 0)
                    {
                        printf("%d", mine_map[i][j]);
                    }
                    else
                    {
                        printf(" ");
                    }
                }
                printf("\n");
            }
            printf("  ");
            for (i = 0; i < MS_SIZE; i++)
            {
                printf("--");
            }
            printf("\n");
            printf("  ");
            for (j = 0; j < MS_SIZE; j++)
            {
                printf("%2d", j);
            }
            printf("   [x]\n");

            int clear = 0;
            for (i = 0; i < MS_SIZE; i++)
            {
                for (j = 0; j < MS_SIZE; j++)
                {
                    if (game_board[i][j] != 0)
                    {
                        clear++;
                    }
                }
            }
            if (clear == MS_SIZE * MS_SIZE - number_of_mines)
            {
                printf("Congratulation!\n");
                break;
            }
        }

        int YN;
        printf("もう一度遊びますか？\n");
        printf("Yes:1,No:0で入力してください。\n");
        while (1)
        {
            scanf("%d", &YN);
            if ((YN != 1) && (YN != 0))
            {
                printf("1か0を入力してください。\n");
            }
            else
            {
                break;
            }
        }
        if (YN == 0)
        {
            break;
        }
    }
    return 0;
}
