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

// ��Ϸ�ṹ
struct Game
{
    // 0 ��ʾû������ 1��ʾ���� -1 ��ʾ����
    int map[ROWS][COLS];
    // ��Ϸ�Ƿ�������
    bool isRunning;
    // ������Ϣ����
    ExMessage msg;

    // ��굱ǰ���ڵ��±�
    int row;
    int col;

    // ��ǰ����
    ChessType currentChessType;
    // ��Ϸģʽ��0Ϊ���˶�ս��1Ϊ�˻���ս
    int gameMode;
    // �˻���ս�Ѷȣ�0Ϊ�򵥣�1Ϊ����
    int difficulty;
};

// ��Ϸ��ʼ��
void init(Game* pthis, int w, int h);
// ��Ϸ����
void render(Game* pthis);
// ��Ϸ����
void update(Game* pthis);

bool horiaontal(Game* pthis, int chess);
bool vertical(Game* pthis, int chess);
bool leftOblique(Game* pthis, int chess);
bool RightOblique(Game* pthis, int chess);
bool judge(Game* pthis);

// �����Ѷ��˻�����void aiMoveHard(Game* pthis);

int main()
{
    Game game;
    init(&game, 960, 600);

    // ѡ����Ϸģʽ
    int mode;
    printf("ѡ����Ϸģʽ��0 - ���˶�ս��1 - �˻���ս\n");
    scanf_s("%d", &mode);
    game.gameMode = mode;

    if (game.gameMode == 1)
    {
        // ѡ���Ѷ�
        int diff;
        printf("ѡ���Ѷȣ�0 - �򵥣�1 - ����\n");
        scanf_s("%d", &diff);
        game.difficulty = diff;
    }

    // ���ڼ�¼��ʼʱ�䣬���ж��Ƿ���1��
    clock_t start_time = clock();

    // ͼƬ���ȼ���begin.jpg���ڿ�ʼ��ʾ
    IMAGE img_begin, img_bg;
    // ʹ�ÿ��ַ��ַ���������ַ����������
    loadimage(&img_begin, L"Resource/images/begin.jpg");
    loadimage(&img_bg, L"Resource/images/bk.jpg");

    // ���������������ϵ�ȥ����
    // ��Ϸ��ѭ��
    while (game.isRunning)
    {
        // �ж��Ƿ��Ѿ�����1��
        if ((clock() - start_time) / CLOCKS_PER_SEC >= 1)
        {
            // ����1����л�Ϊ��ʾbk.jpg�Լ�ִ�к���������Ϸ�߼�
            start_time = 0;  // ����ʱ���ǣ������ظ��ж�
            // ��ʼ������ͼ
            BeginBatchDraw();
            // ����
            cleardevice();
            putimage(0, 0, &img_bg);

            if (judge(&game))
            {
                game.isRunning = false;
            }

            // ��ȡ��Ϣ
            if (peekmessage(&game.msg))
            {
                update(&game);
            }

            // �˻���ս��AI����
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
                               
                                // ���Ѷ���������Ѿ����ӣ�AI�������������
                                int count = 0;
                                int randPos[64][2];
                                // �˸�����ĺ�����ƫ��������Ӧ�ϡ��ҡ��¡������ϡ����¡����ϡ�����
                                int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
                                // �˸������������ƫ����
                                int dy[] = { 0, -1, 0, 1, -1, 1, -1, 1 };

                                // �����˸�����
                                for (int i = 0; i < 8; i++)
                                {
                                    int newRow = game.row + dx[i];
                                    int newCol = game.col + dy[i];
                                    // �ж�������λ���Ƿ������̷�Χ���Ҹ�λ��Ϊ�գ������ӣ�
                                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && game.map[newRow][newCol] == None)
                                    {
                                        // ��һ���ж�������AI�����ܷ񹹳�������״�������ʾ�⣬ʵ�ʿ�����Ҫ���Ͻ����ж��߼���
                                        bool canFormRi = false;
                                        // �ٴα����˸����򣬲����Ƿ�������ڵ�AI�����ܹ�������
                                        
                                        
                                        int checkRow = newRow +2;
                                        int checkCol = newCol +1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow -2;
                                        checkCol = newCol + 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 2;
                                        checkCol = newCol - 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 2;
                                        checkCol = newCol - 1;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 1;
                                        checkCol = newCol + 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 1;
                                        checkCol = newCol + 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow + 1;
                                        checkCol = newCol - 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
                                            canFormRi = true;
                                        }
                                        checkRow = newRow - 1;
                                        checkCol = newCol - 2;
                                        if (checkRow >= 0 && checkRow < ROWS && checkCol >= 0 && checkCol < COLS && game.map[checkRow][checkCol] == White)
                                        {
                                            // �����ĳ���������ҵ����ڵ�AI���ӣ����Ϊ���Թ�������
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
                                                // ���Ѷ���������Ѿ����ӣ�AI�������������
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
                    // �����Ѷ�AI����
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
								//�ж��е����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
													//printf("����������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж��е����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
													//printf("����������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж϶Խ��ߵ����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
													//printf("�Խ�����������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�жϷ��Խ��ߵ����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
													//printf("���Խ�����������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
													//printf("��������ӣ��赲�������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
													//printf("��������ӣ��赲�������\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//�ж϶Խ�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
													//printf("�Խ���������ӣ��赲�������\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//�жϷ��Խ�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
													//printf("���Խ���������ӣ��赲�������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}
								//�ж��е����Ƿ������ӣ��еĻ���������
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
													//printf("�е������ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж��е����Ƿ������ӣ��еĻ���������
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
													//printf("�е������ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж϶Խ��ߵ����Ƿ������ӣ��еĻ���������
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
													//printf("�Խ��ߵ������ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�жϷ��Խ��ߵ����Ƿ������ӣ��еĻ���������
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
													//printf("���Խ��ߵ������ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж�������Ƿ��������ӣ����������ӣ����ס���
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
													//printf("��������ӣ��赲�������\n");
													goto change;
												}
											}
										}

										sum1 = sum2 = 0;
									}
								}

								//�ж�������Ƿ��������ӣ����������ӣ����ס���
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
													//printf("��������ӣ��赲�������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж϶Խ�������Ƿ��������ӣ����������ӣ����ס���
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
													//printf("�Խ���������ӣ��赲�������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�жϷ��Խ�������Ƿ��������ӣ����������ӣ����ס���
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
													//printf("���Խ���������ӣ��赲�������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж��е����Ƿ��������ӣ����������ӣ�������ʹ������������
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
													//printf("�е��Զ��ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж��е����Ƿ��������ӣ����������ӣ�������ʹ������������
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
													//printf("�е��Զ��ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�ж϶Խ��ߵ����Ƿ��������ӣ����������ӣ�������ʹ������������
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
													//printf("�Խ��ߵ��Զ��ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
									}
								}

								//�жϷ��Խ��ߵ����Ƿ��������ӣ����������ӣ�������ʹ������������
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
													//printf("���Խ��ߵ��Զ��ӣ���������\n");
													goto change;
												}
											}
										}
										sum1 = sum2 = 0;
										
									}
								}
							// ������Ѿ����ӣ�AI�������������
											
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

            // ����˫�����ͼ
            EndBatchDraw();
        }
        else
        {
            // ��ȡ���ڿ�Ⱥ͸߶�
            int winWidth = getwidth();
            int winHeight = getheight();
            // ��ȡͼƬ��Ⱥ͸߶�
            int imgWidth = img_begin.getwidth();
            int imgHeight = img_begin.getheight();
            // ����ͼƬ������ʾ����ʼ����
            int x = (winWidth - imgWidth) / 2;
            int y = (winHeight - imgHeight) / 2;

            // ��1����ֻ��ʾbegin.jpgͼƬ��ʹ�����
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
    // ����һ������
    initgraph(w, h, EX_SHOWCONSOLE);
    pthis->isRunning = true;
    pthis->row = -1;
    pthis->col = -1;
    // ��������˻���սʱ˭����
    if (pthis->gameMode == 1)
    {
        pthis->currentChessType = (rand() % 2 == 0) ? Black : White;
    }
    else
    {
        pthis->currentChessType = rand() % 2 ? Black : White;
    }
    // ��ʼ������
    memset(pthis->map, 0, sizeof(pthis->map));
}

void render(Game* pthis)
{
	// ��������
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			if (pthis->map[i][k] != None)
			{
				// ��ÿ���������Ͻǵ�����
				int x = k * GRID_SIZE + XOFFSET;
				int y = i * GRID_SIZE + YOFFSET;

				// ��������
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
    // �����Ͻ���ʾ��ǰ���巽��ʾ��Ϣ
    settextcolor(WHITE);
    settextstyle(20, 0, _T("����"));
    if (pthis->currentChessType == Black)
    {
        outtextxy(800, 20, _T("��ǰ�ֵ���������"));
    }
    else
    {
        outtextxy(800, 20, _T("��ǰ�ֵ���������"));
    }

    // ���Ƶ�ǰ������ڵ���ʾ��
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
    // ����ƶ�
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
    else if (pthis->msg.message == WM_LBUTTONDOWN &&    // ���������
        pthis->row != -1 && pthis->col != -1 &&            // ����˺Ϸ���λ��
        pthis->map[pthis->row][pthis->col] == None)        // ��ǰλ��û������
    {
        pthis->map[pthis->row][pthis->col] = pthis->currentChessType;

        // �л�����
        pthis->currentChessType = (ChessType)-pthis->currentChessType;
    }
    else if (pthis->msg.message == WM_LBUTTONDOWN &&    // ���������
        pthis->row != -1 && pthis->col != -1 &&            // ����˺Ϸ���λ��
        pthis->map[pthis->row][pthis->col] != None)
    {
        MessageBox(GetHWnd(), L"���λ���Ѿ���������", L"", MB_OK);
    }
}

bool judge(Game* pthis)
{
    bool black_win = horiaontal(pthis, Black) || vertical(pthis, Black) || leftOblique(pthis, Black) || RightOblique(pthis, Black);
    bool white_win = horiaontal(pthis, White) || vertical(pthis, White) || leftOblique(pthis, White) || RightOblique(pthis, White);

    if (black_win)
    {
        MessageBox(GetHWnd(), L"�����ʤ����Ϸ����", L"", MB_OK);
        return true;
    }
    if (white_win)
    {
        MessageBox(GetHWnd(), L"�����ʤ����Ϸ����", L"", MB_OK);
        return true;
    }

    return false;
}

bool horiaontal(Game* pthis, int chess)
{
    // ���
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
    // ��ֱ��
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
    // ��б��
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
    // ��б��
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


// �����Ѷ��˻����ӣ��˴���Ϊռλ��ʵ����ʵ�ּ�֦�;������㷨��






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
	//�ж��е����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
						//printf("����������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж��е����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
						//printf("����������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж϶Խ��ߵ����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
						//printf("�Խ�����������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�жϷ��Խ��ߵ����Ƿ��Ѿ��������ӣ�����������ӣ����µ����ӻ��ʤ��
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
						//printf("���Խ�����������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}



	//�ж�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
						//printf("��������ӣ��赲�������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
						//printf("��������ӣ��赲�������\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//�ж϶Խ�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
						//printf("�Խ���������ӣ��赲�������\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//�жϷ��Խ�������Ƿ��Ѿ��������ӣ�����������ӣ��������赲��һ��ʤ��
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
						//printf("���Խ���������ӣ��赲�������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}



	//�ж��е����Ƿ������ӣ��еĻ���������
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
						//printf("�е������ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж��е����Ƿ������ӣ��еĻ���������
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
						//printf("�е������ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж϶Խ��ߵ����Ƿ������ӣ��еĻ���������
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
						//printf("�Խ��ߵ������ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�жϷ��Խ��ߵ����Ƿ������ӣ��еĻ���������
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
						//printf("���Խ��ߵ������ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}


	//�ж�������Ƿ��������ӣ����������ӣ����ס���
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
						//printf("��������ӣ��赲�������\n");
						goto change;
					}
				}
			}

			sum1 = sum2 = 0;
		}
	}

	//�ж�������Ƿ��������ӣ����������ӣ����ס���
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
						//printf("��������ӣ��赲�������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж϶Խ�������Ƿ��������ӣ����������ӣ����ס���
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
						//printf("�Խ���������ӣ��赲�������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�жϷ��Խ�������Ƿ��������ӣ����������ӣ����ס���
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
						//printf("���Խ���������ӣ��赲�������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}




	//�ж��е����Ƿ��������ӣ����������ӣ�������ʹ������������
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
						//printf("�е��Զ��ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж��е����Ƿ��������ӣ����������ӣ�������ʹ������������
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
						//printf("�е��Զ��ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�ж϶Խ��ߵ����Ƿ��������ӣ����������ӣ�������ʹ������������
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
						//printf("�Խ��ߵ��Զ��ӣ���������\n");
						goto change;
					}
				}
			}
			sum1 = sum2 = 0;
		}
	}

	//�жϷ��Խ��ߵ����Ƿ��������ӣ����������ӣ�������ʹ������������
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
						//printf("���Խ��ߵ��Զ��ӣ���������\n");
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
	printf("��������\n");
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
					//printf("�������\n");
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
								//printf("�������\n");
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
	// �� Game �ṹ���е�������Ϣת��Ϊ�ַ����̣����㸴�����е��߼�����
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

	int a[2] = { pthis->row, pthis->col };  // ���ݵ�ǰ�������λ�ã�������������λ�ã�
	Computermove(game.map, ROWS, COLS, a);

	// �����º���ַ�������Ϣת���� Game �ṹ���е�����
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
    //��c���������ֱ�������հ׻������������ӣ�ֹͣͳ��
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