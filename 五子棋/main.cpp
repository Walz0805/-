#include<stdio.h>
#include<easyx.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include <algorithm>
#include <vector>

#define ROWS 15
#define COLS 15
#define GRID_SIZE 38
#define XOFFSET 213
#define YOFFSET 34
enum ChessType
{
    None = 0,
    Black = 1,
    White = -1
};

// 游戏结构
struct Game
{
    // 0 表示没有棋子 1表示黑棋 -1 表示白棋
    int map[ROWS][COLS];
    // 游戏是否在运行
    bool isRunning;
    // 定义消息变量
    ExMessage msg;

    // 鼠标当前所在的下标
    int row;
    int col;

    // 当前棋手
    ChessType currentChessType;
    // 游戏模式，0为人人对战，1为人机对战
    int gameMode;
    // 人机对战难度，0为简单，1为困难
    int difficulty;
};

// 游戏初始化
void init(Game* pthis, int w, int h);
// 游戏绘制
void render(Game* pthis);
// 游戏更新
void update(Game* pthis);

bool horiaontal(Game* pthis, int chess);
bool vertical(Game* pthis, int chess);
bool leftOblique(Game* pthis, int chess);
bool RightOblique(Game* pthis, int chess);
bool judge(Game* pthis);

// 困难难度人机落子void aiMoveHard(Game* pthis);

int main()
{
    Game game;
    init(&game, 960, 600);

    // 选择游戏模式
    int mode;
    printf("选择游戏模式：0 - 人人对战，1 - 人机对战\n");
    scanf_s("%d", &mode);
    game.gameMode = mode;

    if (game.gameMode == 1)
    {
        // 选择难度
        int diff;
        printf("选择难度：0 - 简单，1 - 困难\n");
        scanf_s("%d", &diff);
        game.difficulty = diff;
    }

    // 用于记录开始时间，以判断是否到了1秒
    clock_t start_time = clock();

    // 图片，先加载begin.jpg用于开始显示
    IMAGE img_begin, img_bg;
    // 使用宽字符字符串，解决字符集相关问题
    loadimage(&img_begin, L"Resource/images/begin.jpg");
    loadimage(&img_bg, L"Resource/images/bk.jpg");

    // 处理鼠标操作，不断地去处理
    // 游戏主循环
    while (game.isRunning)
    {
        // 判断是否已经过了1秒
        if ((clock() - start_time) / CLOCKS_PER_SEC >= 1)
        {
            // 超过1秒后切换为显示bk.jpg以及执行后续正常游戏逻辑
            start_time = 0;  // 重置时间标记，避免重复判断
            // 开始批量绘图
            BeginBatchDraw();
            // 清屏
            cleardevice();
            putimage(0, 0, &img_bg);

            if (judge(&game))
            {
                game.isRunning = false;
            }

            // 获取消息
            if (peekmessage(&game.msg))
            {
                update(&game);
            }

            // 人机对战，AI落子
            if (game.gameMode == 1 && game.currentChessType == White)
            {
                if (game.difficulty == 0)
                {
                    int count3 = 0;
                    if (game.map[7][7] == None)
                    {
                        game.map[7][7] = White;
                        game.currentChessType = (ChessType)-game.currentChessType;
                    }
                    else
                    {
                        if (game.currentChessType == White)
                        {
                            if (game.map[game.row][game.col] != None)
                            {
                               
                                // 简单难度下如果人已经落子，AI在四周随机落子
                                int count = 0;
                                int randPos[64][2];
                                // 八个方向的横坐标偏移量，对应上、右、下、左、右上、右下、左上、左下
                                int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
                                // 八个方向的纵坐标偏移量
                                int dy[] = { 0, -1, 0, 1, -1, 1, -1, 1 };

                                // 遍历八个方向
                                for (int i = 0; i < 8; i++)
                                {
                                    int newRow = game.row + dx[i];
                                    int newCol = game.col + dy[i];
                                    // 判断新坐标位置是否在棋盘范围内且该位置为空（无棋子）
                                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && game.map[newRow][newCol] == None)
                                    {
                                        // 进一步判断与已有AI棋子能否构成日字形状（这里简单示意，实际可能需要更严谨的判断逻辑）
                                        bool canFormRi = false;
                                        // 再次遍历八个方向，查找是否存在相邻的AI棋子能构成日字
                                        
                                        
                                        int checkRow = newRow +2;
                                        int checkCol = newCol +1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow -2;
                                        checkCol = newCol + 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 2;
                                        checkCol = newCol - 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 2;
                                        checkCol = newCol - 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 1;
                                        checkCol = newCol + 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 1;
                                        checkCol = newCol + 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 1;
                                        checkCol = newCol - 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 1;
                                        checkCol = newCol - 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // 如果在某个方向上找到相邻的AI棋子，标记为可以构成日字
                                            canFormRi = true;
                                        }
                                        if (canFormRi)
                                        {
                                            randPos[count][0] = newRow;
                                            randPos[count][1] = newCol;
                                            count++;
                                        }
                                    }
                                }
                                if (count > 0&&(count3%3==1))
                                {
                                    int randomIndex = rand() % count;
                                    game.map[randPos[randomIndex][0]][randPos[randomIndex][1]] = White;
                                    game.currentChessType = (ChessType)-game.currentChessType;
                                }
                                else {
                                    if (game.map[7][7] == None)
                                    {
                                        game.map[7][7] = White;
                                        game.currentChessType = (ChessType)-game.currentChessType;
                                    }
                                    else
                                    {
                                        if (game.currentChessType == White)
                                        {
                                            if (game.map[game.row][game.col] != None)
                                            {
                                                // 简单难度下如果人已经落子，AI在四周随机落子
                                                int dx[] = { -1,0,1,0 };
                                                int dy[] = { 0, -1,0,1 };
                                                int count = 0;
                                                int randPos[4][2];
                                                for (int i = 0; i < 4; i++)
                                                {
                                                    int newRow = game.row + dx[i];
                                                    int newCol = game.col + dy[i];
                                                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && game.map[newRow][newCol] == None)
                                                    {
                                                        randPos[count][0] = newRow;
                                                        randPos[count][1] = newCol;
                                                        count++;
                                                    }
                                                }
                                                if (count > 0)
                                                {
                                                    int randomIndex = rand() % count;
                                                    game.map[randPos[randomIndex][0]][randPos[randomIndex][1]] = White;
                                                    game.currentChessType = (ChessType)-game.currentChessType;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    count3++;
                }
                else if (game.difficulty == 1)
                {
                    // 困难难度AI落子
					if (game.map[7][7] == None)
					{
						game.map[7][7] = White;
						game.currentChessType = (ChessType)-game.currentChessType;
					}
					else
					{
						if (game.currentChessType == White)
						{
							if (game.map[game.row][game.col] != None)
							{
								int dx1[] = { -1,0,1,0 };
								int dy1[] = { 0, -1,0,1 };
								int count = 0;
								int randPos[4][2];
								int i = 0;
								int j = 0;
								int k = 0;
								int sum1 = 0;
								int sum2 = 0;
								//判断行电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
								for (i = 0; i < 15; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i][j + k] == None)
												{
													game.map[i][j + k] = White;
													//printf("行四子连五\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断列电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
								for (j = 0; j < 15; j++)
								{
									for (i = 0; i < 15 - 4; i++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j] == White)
											{
												sum2++;
											}
										}
										if (sum2 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j] == None)
												{
													game.map[i + k][j] = White;
													//printf("列四子连五\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j + k] == None)
												{
													game.map[i + k][j + k] = White;
													//printf("对角线四子连五\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断反对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 4; j < 15; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j - k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j - k] == White)
											{
												sum2++;
											}
										}
										if (sum2 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j - k] == None)
												{
													game.map[i + k][j - k] = White;
													//printf("反对角线四子连五\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断行玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
								for (i = 0; i < 15; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum1 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i][j + k] == None)
												{
													game.map[i][j + k] = White;
													//printf("行玩家四子，阻挡玩家五子\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断列玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
								for (j = 0; j < 15; j++)
								{
									for (i = 0; i < 15 - 4; i++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j] == White)
											{
												sum2++;
											}
										}
										if (sum1 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j] == None)
												{
													game.map[i + k][j] = White;
													//printf("列玩家四子，阻挡玩家五子\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//判断对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum1 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j + k] == None)
												{
													game.map[i + k][j + k] = White;
													//printf("对角线玩家四子，阻挡玩家五子\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//判断反对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 4; j < 15; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j - k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j - k] == White)
											{
												sum2++;
											}
										}
										if (sum1 > 3)
										{
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j - k] == None)
												{
													game.map[i + k][j - k] = White;
													//printf("反对角线玩家四子，阻挡玩家五子\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}
								//判断行电脑是否有三子，有的话连成四子
								for (i = 0; i < 15; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 == 3)
										{
											if (sum1 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i][j + k] == None && ((game.map[i][j + k + 1] == White || game.map[i][j + k - 1] == White))
													&& (j + k + 2) < COLS && (j + k - 2) > 0)
												{
													game.map[i][j + k] = White;
													//printf("行电脑三子，连三成四\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断列电脑是否有三子，有的话连成四子
								for (j = 0; j < 15; j++)
								{
									for (i = 0; i < 15 - 4; i++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j] == White)
											{
												sum2++;
											}
										}
										if (sum2 == 3)
										{
											if (sum1 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j] == None && ((game.map[i + k + 1][j] == White || game.map[i + k - 1][j] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j] = White;
													//printf("列电脑三子，连三成四\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断对角线电脑是否有三子，有的话连成四子
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 == 3)
										{
											if (sum1 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j + k] == None && ((game.map[i + k + 1][j + k + 1] == White || game.map[i + k - 1][j + k - 1] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j + k] = White;
													//printf("对角线电脑三子，连三成四\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断反对角线电脑是否有三子，有的话连成四子
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 4; j < 15; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j - k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j - k] == White)
											{
												sum2++;
											}
										}
										if (sum2 == 3)
										{
											if (sum1 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j - k] == None && ((game.map[i + k + 1][j - k - 1] == White || game.map[i + k - 1][j - k + 1] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j - k] = White;
													//printf("反对角线电脑三子，连三成四\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断行玩家是否连成三子，若连成三子，则堵住玩家
								for (i = 0; i < 15; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum1 == 3)
										{
											if (sum2 == 1)
											{
												j++;
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i][j + k] == None && (game.map[i][j + k + 1] == Black || game.map[i][j + k - 1] == Black)
													&& (j + k + 2) < COLS && (j + k - 2) > 0)
												{
													game.map[i][j + k] = White;
													//printf("行玩家三子，阻挡玩家四子\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//判断列玩家是否连成三子，若连成三子，则堵住玩家
								for (j = 0; j < 15; j++)
								{
									for (i = 0; i < 15 - 4; i++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j] == White)
											{
												sum2++;
											}
										}
										if (sum1 == 3)
										{
											if (sum2 == 1)
											{
												i++;
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j] == None && (game.map[i + k + 1][j] == Black || game.map[i + k - 1][j] == Black)
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j] = White;
													//printf("列玩家三子，阻挡玩家四子\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断对角线玩家是否连成三子，若连成三子，则堵住玩家
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum1 == 3)
										{
											if (sum2 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j + k] == None && (game.map[i + k + 1][j + k + 1] == Black || game.map[i + k - 1][j + k - 1] == Black)
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j + k] = White;
													//printf("对角线玩家三子，阻挡玩家四子\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断反对角线玩家是否连成三子，若连成三子，则堵住玩家
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 4; j < 15; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j - k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j - k] == White)
											{
												sum2++;
											}
										}
										if (sum1 == 3)
										{
											if (sum2 == 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j - k] == None && (game.map[i + k + 1][j - k - 1] == Black || game.map[i + k - 1][j - k + 1] == Black)
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j - k] = White;
													//printf("反对角线玩家三子，阻挡玩家四子\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断行电脑是否连成两子，若连成两子，则下子使电脑连成三子
								for (i = 0; i < 15; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 >= 1)
										{
											if (sum1 > 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i][j + k] == None && ((game.map[i][j + k + 1] == White || game.map[i][j + k - 1] == White))
													&& (j + k + 2) < COLS && (j + k - 2) > 0)
												{
													game.map[i][j + k] = White;
													//printf("行电脑二子，连二成三\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断列电脑是否连成两子，若连成两子，则下子使电脑连成三子
								for (j = 0; j < 15; j++)
								{
									for (i = 0; i < 15 - 4; i++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j] == White)
											{
												sum2++;
											}
										}
										if (sum2 >= 1)
										{
											if (sum1 > 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j] == None && ((game.map[i + k + 1][j] == White || game.map[i + k - 1][j] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j] = White;
													//printf("列电脑二子，连二成三\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 0; j < 15 - 4; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j + k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j + k] == White)
											{
												sum2++;
											}
										}
										if (sum2 >= 1)
										{
											if (sum1 > 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j + k] == None && ((game.map[i + k + 1][j + k + 1] == White || game.map[i + k - 1][j + k - 1] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j + k] = White;
													//printf("对角线电脑二子，连二成三\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//判断反对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
								for (i = 0; i < 15 - 4; i++)
								{
									for (j = 4; j < 15; j++)
									{
										for (k = 0; k < 5; k++)
										{
											if (game.map[i + k][j - k] == Black)
											{
												sum1++;
											}
											else if (game.map[i + k][j - k] == White)
											{
												sum2++;
											}
										}
										if (sum2 >= 1)
										{
											if (sum1 > 1)
											{
												break;
											}
											for (k = 0; k < 5; k++)
											{
												if (game.map[i + k][j - k] == None && ((game.map[i + k + 1][j - k - 1] == White || game.map[i + k - 1][j - k + 1] == White))
													&& (i + k + 2) < ROWS && (i + k - 2) > 0)
												{
													game.map[i + k][j - k] = White;
													//printf("反对角线电脑二子，连二成三\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
										
									}
								}
							// 如果人已经落子，AI在四周随机落子
											
								for (int i = 0; i < 4; i++)
											{
												int newRow = game.row + dx1[i];
												int newCol = game.col + dy1[i];
												if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && game.map[newRow][newCol] == None)
												{
													randPos[count][0] = newRow;
													randPos[count][1] = newCol;
													count++;
												}
											}
											if (count > 0)
											{
												int randomIndex = rand() % count;
												game.map[randPos[randomIndex][0]][randPos[randomIndex][1]] = White;
											}
											goto change;
							change:
								game.currentChessType = (ChessType)-game.currentChessType;
							}
						}
					}
				
                 }
            }

            render(&game);

            // 结束双缓冲绘图
            EndBatchDraw();
        }
        else
        {
            // 获取窗口宽度和高度
            int winWidth = getwidth();
            int winHeight = getheight();
            // 获取图片宽度和高度
            int imgWidth = img_begin.getwidth();
            int imgHeight = img_begin.getheight();
            // 计算图片居中显示的起始坐标
            int x = (winWidth - imgWidth) / 2;
            int y = (winHeight - imgHeight) / 2;

            // 在1秒内只显示begin.jpg图片并使其居中
            BeginBatchDraw();
            cleardevice();
            putimage(x, y, &img_begin);
            EndBatchDraw();
        }

    }

    return 0;
}

void init(Game* pthis, int w, int h)
{
    srand(time(NULL));
    // 创建一个窗口
    initgraph(w, h, EX_SHOWCONSOLE);
    pthis->isRunning = true;
    pthis->row = -1;
    pthis->col = -1;
    // 随机决定人机对战时谁先手
    if (pthis->gameMode == 1)
    {
        pthis->currentChessType = (rand() % 2 == 0) ? Black : White;
    }
    else
    {
        pthis->currentChessType = rand() % 2 ? Black : White;
    }
    // 初始化棋盘
    memset(pthis->map, 0, sizeof(pthis->map));
}

void render(Game* pthis)
{
	// 绘制棋子
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			if (pthis->map[i][k] != None)
			{
				// 求每个格子左上角的坐标
				int x = k * GRID_SIZE + XOFFSET;
				int y = i * GRID_SIZE + YOFFSET;

				// 绘制棋子
				if (pthis->map[i][k] == White)
				{
					setfillcolor(WHITE);
				}
				else if (pthis->map[i][k] == Black)
				{
					setfillcolor(BLACK);
				}

				solidcircle(x, y, 15);
			}

		}
	}
    // 在右上角显示当前下棋方提示信息
    settextcolor(WHITE);
    settextstyle(20, 0, _T("宋体"));
    if (pthis->currentChessType == Black)
    {
        outtextxy(800, 20, _T("当前轮到黑棋下棋"));
    }
    else
    {
        outtextxy(800, 20, _T("当前轮到白棋下棋"));
    }

    // 绘制当前鼠标所在的提示框
    printf("%d %d\n", pthis->row, pthis->col);
    if (pthis->row != -1 && pthis->col != -1)
    {
        setlinecolor(BLUE);
        int x = pthis->col * GRID_SIZE + XOFFSET;
        int y = pthis->row * GRID_SIZE + YOFFSET;
        circle(x, y, 17);
    }
}

void update(Game* pthis)
{
    // 鼠标移动
    if (pthis->msg.message == WM_MOUSEMOVE)
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int k = 0; k < COLS; k++)
            {
                int cx = k * GRID_SIZE + XOFFSET;
                int cy = i * GRID_SIZE + YOFFSET;

                if (abs(pthis->msg.x - cx) < GRID_SIZE / 2 && abs(pthis->msg.y - cy) < GRID_SIZE / 2)
                {
                    pthis->row = i;
                    pthis->col = k;
                    goto END_LOOP;
                }
            }
        }
    END_LOOP:;

    }
    else if (pthis->msg.message == WM_LBUTTONDOWN &&    // 鼠标左键点击
        pthis->row != -1 && pthis->col != -1 &&            // 点击了合法的位置
        pthis->map[pthis->row][pthis->col] == None)        // 当前位置没有棋子
    {
        pthis->map[pthis->row][pthis->col] = pthis->currentChessType;

        // 切换棋手
        pthis->currentChessType = (ChessType)-pthis->currentChessType;
    }
    else if (pthis->msg.message == WM_LBUTTONDOWN &&    // 鼠标左键点击
        pthis->row != -1 && pthis->col != -1 &&            // 点击了合法的位置
        pthis->map[pthis->row][pthis->col] != None)
    {
        MessageBox(GetHWnd(), L"这个位置已经有棋子了", L"", MB_OK);
    }
}

bool judge(Game* pthis)
{
    bool black_win = horiaontal(pthis, Black) || vertical(pthis, Black) || leftOblique(pthis, Black) || RightOblique(pthis, Black);
    bool white_win = horiaontal(pthis, White) || vertical(pthis, White) || leftOblique(pthis, White) || RightOblique(pthis, White);

    if (black_win)
    {
        MessageBox(GetHWnd(), L"黑棋获胜！游戏结束", L"", MB_OK);
        return true;
    }
    if (white_win)
    {
        MessageBox(GetHWnd(), L"白棋获胜！游戏结束", L"", MB_OK);
        return true;
    }

    return false;
}

bool horiaontal(Game* pthis, int chess)
{
    // 横的
    for (int c = pthis->col - 4; c <= pthis->col; c++)
    {
        int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            if (c + n >= 0 && c + n < COLS && pthis->map[pthis->row][c + n] == chess)
            {
                counter++;
            }
        }
        if (counter == 5)
            return true;
    }
    return false;
}

bool vertical(Game* pthis, int chess)
{
    // 垂直的
    for (int r = pthis->row - 4; r <= pthis->row; r++)
    {
        int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            if (r + n >= 0 && r + n < ROWS && pthis->map[r + n][pthis->col] == chess)
            {
                counter++;
            }
        }
        if (counter == 5)
            return true;
    }
    return false;
}

bool leftOblique(Game* pthis, int chess)
{
    // 左斜的
    for (int offset = 0; offset < 4; offset++)
    {
        int start_r = pthis->row - offset;
        int start_c = pthis->col - offset;
        int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            if (start_r + n >= 0 && start_r + n < ROWS && start_c + n >= 0 && start_c + n < COLS && pthis->map[start_r + n][start_c + n] == chess)
            {
                counter++;
            }
        }
        if (counter == 5)
            return true;
    }
    return false;
}

bool RightOblique(Game* pthis, int chess)
{
    // 右斜的
    for (int offset = 0; offset < 4; offset++)
    {
        int start_r = pthis->row + offset;
        int start_c = pthis->col - offset;
        int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            if (start_r - n >= 0 && start_r - n < ROWS && start_c + n >= 0 && start_c + n < COLS && pthis->map[start_r - n][start_c + n] == chess)
            {
                counter++;
            }
        }
        if (counter == 5)
            return true;
    }
    return false;
}


// 困难难度人机落子（此处仅为占位，实际需实现剪枝和决策树算法）






/*
int Isfull(char game.map[][col], int x, int y, int num)
{
	int i = 0;
	int j = 0;
	for (i = x - num; i <= x + num; i++)
	{
		for (j = y - num; j <= y + num; j++)
		{
			if (i < 0 || j < 0 || i >= row || j >= col)
			{
				continue;
			}
			if (game.map[i][j] == None)
			{
				return 0;
			}
		}
	}
	goto change;
}


int youhua(char game.map[][col], int 15, int 15)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int sum1 = 0;
	int sum2 = 0;
	//判断行电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum2 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i][j + k] == None)
					{
						game.map[i][j + k] = White;
						//printf("行四子连五\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断列电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15 - 4; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j] == White)
				{
					sum2++;
				}
			}
			if (sum2 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j] == None)
					{
						game.map[i + k][j] = White;
						//printf("列四子连五\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum2 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j + k] == None)
					{
						game.map[i + k][j + k] = White;
						//printf("对角线四子连五\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断反对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 4; j < 15; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j - k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j - k] == White)
				{
					sum2++;
				}
			}
			if (sum2 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j - k] == None)
					{
						game.map[i + k][j - k] = White;
						//printf("反对角线四子连五\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}



	//判断行玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum1 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i][j + k] == None)
					{
						game.map[i][j + k] = White;
						//printf("行玩家四子，阻挡玩家五子\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断列玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15 - 4; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j] == White)
				{
					sum2++;
				}
			}
			if (sum1 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j] == None)
					{
						game.map[i + k][j] = White;
						//printf("列玩家四子，阻挡玩家五子\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//判断对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum1 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j + k] == None)
					{
						game.map[i + k][j + k] = White;
						//printf("对角线玩家四子，阻挡玩家五子\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//判断反对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 4; j < 15; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j - k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j - k] == White)
				{
					sum2++;
				}
			}
			if (sum1 > 3)
			{
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j - k] == None)
					{
						game.map[i + k][j - k] = White;
						//printf("反对角线玩家四子，阻挡玩家五子\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}



	//判断行电脑是否有三子，有的话连成四子
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum2 == 3)
			{
				if (sum1 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i][j + k] == None && ((game.map[i][j + k + 1] == White || game.map[i][j + k - 1] == White))
						&& (j + k + 2) < col && (j + k - 2) > 0)
					{
						game.map[i][j + k] = White;
						//printf("行电脑三子，连三成四\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断列电脑是否有三子，有的话连成四子
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15 - 4; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j] == White)
				{
					sum2++;
				}
			}
			if (sum2 == 3)
			{
				if (sum1 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j] == None && ((game.map[i + k + 1][j] == White || game.map[i + k - 1][j] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j] = White;
						//printf("列电脑三子，连三成四\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断对角线电脑是否有三子，有的话连成四子
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j + k] == White)
				{ 
					sum2++;
				}
			}
			if (sum2 == 3)
			{
				if (sum1 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j + k] == None && ((game.map[i + k + 1][j + k + 1] == White || game.map[i + k - 1][j + k - 1] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j + k] = White;
						//printf("对角线电脑三子，连三成四\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断反对角线电脑是否有三子，有的话连成四子
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 4; j < 15; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j - k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j - k] == White)
				{
					sum2++;
				}
			}
			if (sum2 == 3)
			{
				if (sum1 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j - k] == None && ((game.map[i + k + 1][j - k - 1] == White || game.map[i + k - 1][j - k + 1] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j - k] = White;
						//printf("反对角线电脑三子，连三成四\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}


	//判断行玩家是否连成三子，若连成三子，则堵住玩家
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum1 == 3)
			{
				if (sum2 == 1)
				{
					j++;
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i][j + k] == None && (game.map[i][j + k + 1] == Black || game.map[i][j + k - 1] == Black)
						&& (j + k + 2) < col && (j + k - 2) > 0)
					{
						game.map[i][j + k] = White;
						//printf("行玩家三子，阻挡玩家四子\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//判断列玩家是否连成三子，若连成三子，则堵住玩家
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15 - 4; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j] == White)
				{
					sum2++;
				}
			}
			if (sum1 == 3)
			{
				if (sum2 == 1)
				{
					i++;
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j] == None && (game.map[i + k + 1][j] == Black || game.map[i + k - 1][j] == Black)
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j] = White;
						//printf("列玩家三子，阻挡玩家四子\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断对角线玩家是否连成三子，若连成三子，则堵住玩家
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum1 == 3)
			{
				if (sum2 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j + k] == None && (game.map[i + k + 1][j + k + 1] == Black || game.map[i + k - 1][j + k - 1] == Black)
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j + k] = White;
						//printf("对角线玩家三子，阻挡玩家四子\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断反对角线玩家是否连成三子，若连成三子，则堵住玩家
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 4; j < 15; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j - k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j - k] == White)
				{
					sum2++;
				}
			}
			if (sum1 == 3)
			{
				if (sum2 == 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j - k] == None && (game.map[i + k + 1][j - k - 1] == Black || game.map[i + k - 1][j - k + 1] == Black)
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j - k] = White;
						//printf("反对角线玩家三子，阻挡玩家四子\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}




	//判断行电脑是否连成两子，若连成两子，则下子使电脑连成三子
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum2 >= 1)
			{
				if (sum1 > 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i][j + k] == None && ((game.map[i][j + k + 1] == White || game.map[i][j + k - 1] == White))
						&& (j + k + 2) < col && (j + k - 2) > 0)
					{
						game.map[i][j + k] = White;
						//printf("行电脑二子，连二成三\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断列电脑是否连成两子，若连成两子，则下子使电脑连成三子
	for (j = 0; j < 15; j++)
	{
		for (i = 0; i < 15 - 4; i++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j] == White)
				{
					sum2++;
				}
			}
			if (sum2 >= 1)
			{
				if (sum1 > 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j] == None && ((game.map[i + k + 1][j] == White || game.map[i + k - 1][j] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j] = White;
						//printf("列电脑二子，连二成三\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 0; j < 15 - 4; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j + k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j + k] == White)
				{
					sum2++;
				}
			}
			if (sum2 >= 1)
			{
				if (sum1 > 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j + k] == None && ((game.map[i + k + 1][j + k + 1] == White || game.map[i + k - 1][j + k - 1] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j + k] = White;
						//printf("对角线电脑二子，连二成三\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//判断反对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
	for (i = 0; i < 15 - 4; i++)
	{
		for (j = 4; j < 15; j++)
		{
			for (k = 0; k < 5; k++)
			{
				if (game.map[i + k][j - k] == Black)
				{
					sum1++;
				}
				else if (game.map[i + k][j - k] == White)
				{
					sum2++;
				}
			}
			if (sum2 >= 1)
			{
				if (sum1 > 1)
				{
					break;
				}
				for (k = 0; k < 5; k++)
				{
					if (game.map[i + k][j - k] == None && ((game.map[i + k + 1][j - k - 1] == White || game.map[i + k - 1][j - k + 1] == White))
						&& (i + k + 2) < row && (i + k - 2) > 0)
					{
						game.map[i + k][j - k] = White;
						//printf("反对角线电脑二子，连二成三\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	return 0;
}

void Computermove(char game.map[][col], int 15, int 15, int a[2])
{
	int x = 0;
	int y = 0;
	int i = 0;
	int x1 = a[0];
	int y1 = a[1];
	printf("电脑下棋\n");
	int re = youhua(game.map, 15, 15);
	if (re == 0)
	{
		while (1)
		{
			x = rand() % 15;
			y = rand() % 15;
			int tmp = 0;
			if (game.map[x][y] == None)
			{
				if (x <= x1 + 1 && x >= x1 - 1 && y <= y1 + 1 && y >= y1 - 1)
				{
					game.map[x][y] = White;
					//printf("随机落子\n");
					break;
				}
				else
				{
					for (i = 1; i <= row / 2; i++)
					{
						if (Isfull(game.map, x1, y1, i))
						{
							if (x <= x1 + i + 1 && x >= x1 - (i + 1) && y <= y1 + i + 1 && y >= y1 - (i + 1))
							{
								game.map[x][y] = White;
								tmp = 1;
								//printf("随机落子\n");
								break;
							}
						}
						else
						{
							break;
						}
					}
					if (tmp)
					{
						break;
					}
				}
			}
		}
	}
}
void aiMoveHard(Game* pthis)
{
	char game.map[ROWS][COLS];
	// 将 Game 结构体中的棋盘信息转换为字符棋盘，方便复用已有的逻辑函数
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (pthis->map[i][j] == None) {
				game.map[i][j] = None;
			}
			else if (pthis->map[i][j] == White) {
				game.map[i][j] = White;
			}
			else if (pthis->map[i][j] == Black) {
				game.map[i][j] = Black;
			}
		}
	}

	int a[2] = { pthis->row, pthis->col };  // 传递当前鼠标所在位置（或玩家最近落子位置）
	Computermove(game.map, ROWS, COLS, a);

	// 将更新后的字符棋盘信息转换回 Game 结构体中的棋盘
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (game.map[i][j] == White) {
				pthis->map[i][j] = White;
			}
			else if (game.map[i][j] == Black) {
				pthis->map[i][j] = Black;
			}
			else {
				pthis->map[i][j] = None;
			}
		}
	}

	pthis->currentChessType = (ChessType)-pthis->currentChessType;
}
*/

/*
void aiMoveHard(Game* pthis) {

}

int gobang_getScore(int self, int e)
{
    if (self > 5) return 20000;
    if (self == 5 && e == 0) return 20000;
    if (self == 5 && e == 1) return 20000;
    if (self == 5 && e == 2) return 20000;
    if (self == 4 && e == 0) return 1000;
    if (self == 4 && e == 1) return 3000;
    if (self == 4 && e == 2) return 5000;
    if (self == 3 && e == 0) return 500;
    if (self == 3 && e == 1) return 1000;
    if (self == 3 && e == 2) return 3000;
    if (self == 2 && e == 0) return 100;
    if (self == 2 && e == 1) return 200;
    if (self == 2 && e == 2) return 500;
    if (self == 1 && e == 0) return 30;
    if (self == 1 && e == 1) return 50;
    if (self == 1 && e == 2) return 100;
    return 0;
}

int gobang_getHorizontalScore(Gobang* pthis, int r, int c, int pieces)
{
    int self = 1;
    int ai = 0;
    //从c向左遍历，直到遇到空白或者其他的棋子，停止统计
    for (int i = c - 1; i >= 0; i--)
    {
        if (pthis->map[r][i] == pieces)
        {
            self++;
        }
        else if (pthis->map[r][i] == None)
        {
            break;
        }
        else
        {
            ai++;
            break;
        }
    }
    for (int i = c + 1; i < COLS; i++)
    {
        if (pthis->map[r][i] == pieces)
        {
            self++;
        }
        else if (pthis->map[r][i] == None)
        {
            break;
        }
        else
        {
            ai++;
            break;
        }
    }
    return 0;
}

int gobang_getScore(Gobang* pthis, int r, int c)
{
    int numH1 = gobang_getHorizontalScore(pthis, r, c, Black);
    int numH2 = gobang_getHorizontalScore(pthis, r, c, White);
    int numV1 = gobang_getVerticalScore(pthis, r, c, Black);
    int numV2 = gobang_getVerticalScore(pthis, r, c, White);
    int numL1 = gobang_getLhtScore(pthis, r, c, Black);
    int numL2 = gobang_getLhtScore(pthis, r, c, White);
    int numR1 = gobang_getRhtScore(pthis, r, c, Black);
    int numR2 = gobang_getRhtScore(pthis, r, c, White);

    if (numH1 >= 200000 || numH2 >= 200000 || numV1 >= 200000 || numV2 >= 200000 ||
        numL1 >= 200000 || numL2 >= 200000 || numR1 >= 200000 || numR2 >= 200000)
    {
        return INT_MAX;
    }

    int xScore = gobang_getHorizontalScore(pthis, r, c, Black) + gobang_getHorizontalScore(pthis, r, c, White);
    int yScore = gobang_getVerticalScore(pthis, r, c, Black) + gobang_getVerticalScore(pthis, r, c, White);
    int lScore = gobang_getLhtScore(pthis, r, c, Black) + gobang_getLhtScore(pthis, r, c, White);
    int rScore = gobang_getRhtScore(pthis, r, c, Black) + gobang_getRhtScore(pthis, r, c, White);

    return xScore + yScore + lScore + rScore;
}
*/