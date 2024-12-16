#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<graphics.h>
#include<stdlib.h>
        

void menu();

//全局变量
int r[4][4] = { { 241,180,515,226 }, {241,230,460,276},{241,282,460,333 }, {285,386,460,424 } };
int flag = 0;
int flag3 = 0;
int count = 0;
int arr[16][16] = { 0 };
int score[16][16] = { 0 };
int ret = 0;

int r1[4] = { 530,30,660,75 };
int r4[4] = { 530,200,680,250 };
int r5[4] = { 530,260,640,300 };
int r6[4] = { 530,320,640,350 };
int r7[4] = { 530,380,640,410 };
RECT R1 = { r1[0], r1[1], r1[2], r1[3] };
RECT R4 = { r4[0], r4[1], r4[2], r4[3] };
RECT R5 = { r5[0], r5[1], r5[2], r5[3] };
RECT R6 = { r6[0], r6[1], r6[2], r6[3] };
RECT R7 = { r7[0], r7[1], r7[2], r7[3] };

void find_max(int* x, int* y, int arr[16][16])
{
	int max = 0;
	int n = 0;
	int maxpoint[225][2];
	memset(maxpoint, 0, sizeof(int[225][2]));
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (arr[i][j] == 0)
			{
				if (score[i][j] > max)
				{
					max = score[i][j];
					*x = i;
					*y = j;
				}
			}
		}
	}
	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 15; j++)
		{
			if (score[i][j] == max)
			{
				maxpoint[n][0] = i;
				maxpoint[n++][1] = j;
			}
		}
	}
	srand((unsigned int)time(0));
	int index = rand() % n;
	*x = maxpoint[index][0];
	*y = maxpoint[index][1];

}

int button_judge(int x, int y)//判断点击的是哪个按钮
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])
		return 1;//人机
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])
		return 2;//机器
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])
		return 3;//rr
	if (x > r[3][0] && x<r[3][2] && y>r[3][1] && y < r[3][3])
		return 5;//退出
	return 0;
}

void judge_winPVP(int t)
{
	if (t == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("黑棋胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 2)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("白棋胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 4)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("平局"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setfillcolor(WHITE);
	fillrectangle(r6[0], r6[1], r6[2], r6[3]);
	drawtext(_T("复盘"), &R6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void judge_winPVE(int t)
{
	if (t == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("电脑胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 2)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("玩家胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 4)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("平局"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setfillcolor(WHITE);
	fillrectangle(r6[0], r6[1], r6[2], r6[3]);
	drawtext(_T("复盘"), &R6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void judge_winEVE(int t)
{
	if (t == 1)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("玩家2胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 2)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("玩家2胜利"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (t == 4)
	{
		setfillcolor(WHITE);
		fillrectangle(r5[0], r5[1], r5[2], r5[3]);
		setfillcolor(RED);
		drawtext(_T("平局"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	setfillcolor(WHITE);
	fillrectangle(r6[0], r6[1], r6[2], r6[3]);
	drawtext(_T("复盘"), &R6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

int is_win(int arr[16][16], int count)
{
	int i = 0;
	int j = 0;
	//竖行
	for (i = 1; i < 16; i++)
	{
		for (j = 1; j < 12; j++)
		{
			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j + 2] == arr[i][j + 3] && arr[i][j + 3] == arr[i][j + 4] && arr[i][j] != 0)
				return arr[i][j];
		}
	}
	//横行
	for (j = 1; j < 16; j++)
	{
		for (i = 1; i < 12; i++)
		{
			if (arr[i][j] == arr[i + 1][j] && arr[i + 1][j] == arr[i + 2][j] && arr[i + 2][j] == arr[i + 3][j] && arr[i + 3][j] == arr[i + 4][j] && arr[i][j] != 0)
				return arr[i][j];
		}
	}

	//右下
	for (j = 1; j < 12; j++)
	{
		for (i = 1; i < 12; i++)
		{
			if (arr[i][j] == arr[i + 1][j + 1] && arr[i + 1][j + 1] == arr[i + 2][j + 2] && arr[i + 2][j + 2] == arr[i + 3][j + 3] && arr[i + 3][j + 3] == arr[i + 4][j + 4] && arr[i][j] != 0)
				return arr[i][j];
		}
	}
	//左下
	for (i = 1; i < 12; i++)
	{
		for (j = 15; j > 4; j--)
		{
			if (arr[i][j] == arr[i + 1][j - 1] && arr[i + 1][j - 1] == arr[i + 2][j - 2] && arr[i + 2][j - 2] == arr[i + 3][j - 3] && arr[i + 3][j - 3] == arr[i + 4][j - 4] && arr[i][j] != 0)
				return arr[i][j];
		}
	}
	if (count == 225)
		return 4;
	return 0;

}

void print_board()
{
	initgraph(800, 525);
	//贴图    
	IMAGE back1;//定义图片接收
	loadimage(&back1, _T("棋盘.png"));//接收图片
	putimage(0, 0, &back1);//输出图片
	int i = 0;
	for (i = 15; i <= 542; i += 32)
	{
		line(i, 5, i, 517);
	}
	for (i = 5; i <= 525; i += 32)
	{
		line(15, i, 527, i);
	}
	line(16, 5, 16, 517);
	line(528, 5, 528, 517);
	line(15, 6, 527, 6);
	line(15, 518, 527, 518);
	
}

void fupanPVP()
{
	int a, b;
	int r4[4] = { 530,200,680,250 };
	RECT R4 = { r4[0], r4[1], r4[2], r4[3] };
	flag = 0;
	count = 0;
	print_board();
	FILE* fq = fopen("PVP.txt", "a+");
	memset(arr, 0, sizeof(int[16]));
	while (fscanf_s(fq, "%d %d ", &a, &b) == 2)
	{
		if (flag % 2 == 0)
		{
			setfillcolor(WHITE);
			fillrectangle(r4[0], r4[1], r4[2], r4[3]);
			drawtext(_T("该白方下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在R3中输入文字，水平居中，垂直居中，单行显示
			setfillcolor(BLACK);
			solidcircle(a * 32 + 15, b * 32 + 5, 12);
			flag++;
			count++;
			arr[a][b] = 1;
		}
		else
		{
			setfillcolor(WHITE);
			fillrectangle(r4[0], r4[1], r4[2], r4[3]);
			setfillcolor(BLACK);
			drawtext(_T("该黑方下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			setfillcolor(WHITE);
			solidcircle(a * 32 + 15, b * 32 + 5, 12);
			flag++;
			count++;
			arr[a][b] = 2;
		}
		Sleep(500);
	}
	ret = is_win(arr, count);
	judge_winPVP(ret);
}

void fupanPVE()
{
	int a, b;
	int r4[4] = { 530,200,680,250 };
	RECT R4 = { r4[0], r4[1], r4[2], r4[3] };
	count = 0;
	flag = flag3;
	print_board();
	FILE* fq = fopen("PVE.txt", "a+");
	memset(arr, 0, sizeof(int[16]));
	while (fscanf_s(fq, "%d %d ", &a, &b) == 2)
	{
		if (flag % 2 == 0)
		{
			setfillcolor(WHITE);
			fillrectangle(r4[0], r4[1], r4[2], r4[3]);
			setfillcolor(BLACK);
			solidcircle(a * 32 + 15, b * 32 + 5, 12);
			flag++;
			count++;
			arr[a][b] = 1;
		}
		else
		{
			setfillcolor(WHITE);
			fillrectangle(r4[0], r4[1], r4[2], r4[3]);
			solidcircle(a * 32 + 15, b * 32 + 5, 12);
			flag++;
			count++;
			arr[a][b] = 2;
		}
		Sleep(500);
	}
	ret = is_win(arr, count);
	judge_winPVE(ret);
}


void computer(int arr[16][16])
{
	int i, x, y, k, r, c;
	int persennum = 0;
	int ainum = 0;
	int emptynum = 0;
	memset(score, 0, sizeof(int[16][16]));
	for (r = 1; r < 16; r++)
	{
		for (c = 1; c < 16; c++)
		{
			if (arr[r][c] == 0)
			{
				int direction[4][2] = { {1,0},{1,1},{0,1},{-1,1} };
				//规定正方向
				for (k = 0; k < 4; k++)
				{
					x = direction[k][0];
					y = direction[k][1];
					//遍历不同方向

					//清空积分器
					persennum = 0;
					ainum = 0;
					emptynum = 0;
					//预测人下棋的分数（防御）
					// 
					//正向
					for (i = 1; i <= 4; i++)
					{
						if (r + i * y <= 15 && c + i * x <= 15 && arr[r + i * y][c + i * x] == 2)
						{
							persennum++;
						}
						//玩家的棋子
						else if (r + i * y <= 15 && c + i * x <= 15 && arr[r + i * y][c + i * x] == 0)
						{
							emptynum++;
							break;
						}
						//空白的棋子
						else
						{
							break;
						}
					}
					//反向
					for (i = 1; i <= 4; i++)
					{
						if (r - i * y >= 1 && c - i * x >= 1 && arr[r - i * y][c - i * x] == 2)
						{
							persennum++;
						}
						//玩家的棋子
						else if (r - i * y >= 1 && c - i * x >= 1 && arr[r - i * y][c - i * x] == 0)
						{
							emptynum++;
							break;
						}
						//搜索到空白的棋子，停止搜索
						else
						{
							break;
						}
						//搜索到越界的棋子和ai棋子，停止搜索
					}
					//杀二
					if (persennum == 1)
					{
						score[r][c] += 10;
					}
					//杀三
					else if (persennum == 2)
					{
						//死三
						if (emptynum == 1)
							score[r][c] += 30;
						//活三
						else if (emptynum == 2)
							score[r][c] += 40;
					}
					//杀四
					else if (persennum == 3)
					{
						//死四
						if (emptynum == 1)
							score[r][c] += 60;
						//活四
						else if (emptynum == 2)
							score[r][c] += 200;
					}
					//杀五
					else if (persennum == 4)
					{
						score[r][c] += 20000;
					}
					//清空
					emptynum = 0;

					//预测ai的分数(进攻）
					//正向
					for (i = 1; i <= 4; i++)
					{
						if (r + i * y <= 15 && c + i * x <= 15 && arr[r + i * y][c + i * x] == 1)
						{
							ainum++;
						}
						//玩家的棋子
						else if (r + i * y <= 15 && c + i * x <= 15 && arr[r + i * y][c + i * x] == 0)
						{
							emptynum++;
							break;
						}
						//空白的棋子
						else
						{
							break;
						}
					}
					//反向
					for (i = 1; i <= 4; i++)
					{
						if (r - i * y >= 1 && c - i * x >= 1 && arr[r - i * y][c - i * x] == 1)
						{
							ainum++;
						}
						//玩家的棋子
						else if (r - i * y >= 1 && c - i * x >= 1 && arr[r - i * y][c - i * x] == 0)
						{
							emptynum++;
							break;
						}
						//搜索到空白的棋子，停止搜索
						else
						{
							break;
						}
						//搜索到越界的棋子和ai棋子，停止搜索
					}
					//杀二
					if (ainum == 0)
					{
						score[r][c] += 5;
					}
					if (ainum == 1)
					{
						score[r][c] += 10;
					}
					//杀三
					else if (ainum == 2)
					{
						//死三
						if (emptynum == 1)
							score[r][c] += 25;
						//活三
						else if (emptynum == 2)
							score[r][c] += 50;
					}
					//杀四
					else if (ainum == 3)
					{
						//死四
						if (emptynum == 1)
							score[r][c] += 55;
						//活四
						else if (emptynum == 2)
							score[r][c] += 300;
					}
					//杀五
					else if (ainum == 4)
					{
						score[r][c] += 999999;
					}
				}
			}
		}
	}
}

void PVP()
{
	memset(arr, 0, sizeof(int[16][16]));
	print_board();
	fillrectangle(r4[0], r4[1], r4[2], r4[3]);
	drawtext(_T("该黑方下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	int x = 0, y = 0;
	int a, b, i, j;
	flag = 0;
	count = 0;
	FILE* file = fopen("PVP.txt", "w");
	fclose(file);
	FILE* fq = fopen("PVP.txt", "a+");
	MOUSEMSG m;//保存鼠标消息
	while (1)
	{
		m = GetMouseMsg();
		for (i = 1; i < 16; i++)
		{
			for (j = 1; j < 16; j++)
			{
				if (abs(m.x - i * 32 - 15) < 16 && abs(m.y - j * 32 - 5) < 16)
				{
					x = i * 32 + 15;
					y = j * 32 + 5;
					a = i;
					b = j;
				}
			}
		}
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			if (arr[a][b])
			{
				MessageBox(NULL,L"这里已经有了", L"提示", MB_OK);
				continue;
			}
			if (m.x < 15 || m.x>517 || m.y < 5 || m.y > 527)
			{
				MessageBox(NULL, L"你下的棋子超出范围",L"提示", MB_OK);
				continue;
			}
			if (flag % 2 == 0)
			{
				setfillcolor(WHITE);
				fillrectangle(r4[0], r4[1], r4[2], r4[3]);
				drawtext(_T("该白方下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在R3中输入文字，水平居中，垂直居中，单行显示
				setfillcolor(BLACK);
				solidcircle(x, y, 12);
				flag++;
				count++;
				arr[a][b] = 1;
				fprintf(fq, "%d ", a);
				fprintf(fq, "%d ", b);
				ret = is_win(arr, count);
				if (ret)
				{
					judge_winPVP(ret);
					break;
				}
			}
			else
			{
				setfillcolor(WHITE);
				fillrectangle(r4[0], r4[1], r4[2], r4[3]);
				setfillcolor(BLACK);
				drawtext(_T("该黑方下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				setfillcolor(WHITE);
				solidcircle(x, y, 12);
				arr[a][b] = 2;
				fprintf(fq, "%d ", a);
				fprintf(fq, "%d ", b);
				flag++;
				count++;
				ret = is_win(arr, count);
				if (ret)
				{
					judge_winPVP(ret);
					break;
				}
			}
		}
	}
	fclose(fq);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			else if (m.x > r6[0] && m.x<r6[2] && m.y>r6[1] && m.y < r6[3])
			{
				closegraph();
				fupanPVP();
			}
			else if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3])
			{
				closegraph();
				menu();
			}
		}
	}
}

void PVE2()
{
	int x = 0, y = 0;
	int a = 0, b = 0, i = 0, j = 0;
	memset(arr, 0, sizeof(int[16][16]));
	FILE* file = fopen("PVE.txt", "w");
	fclose(file);
	count = 0;
	FILE* fq = fopen("PVE.txt", "a+");
	print_board();
	fillrectangle(r4[0], r4[1], r4[2], r4[3]);
	drawtext(_T("电脑先下"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	fillrectangle(r5[0], r5[1], r5[2], r5[3]);
	drawtext(_T("我先下"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r4[0] && m.x<r4[2] && m.y>r4[1] && m.y < r4[3])
			{
				flag3 = 0;
				flag = 0;
				break;
			}
			else if (m.x > r5[0] && m.x<r5[2] && m.y>r5[1] && m.y < r5[3])
			{
				flag3 = 1;
				flag = 1;
				break;
			}
			else
			{
				MessageBox(NULL, L"请选择先后", L"", MB_OK);
			}
		}
	}
	while (1)
	{
		//机器部分
		if (flag == 0)
		{
			setfillcolor(BLACK);
			solidcircle(271, 261, 12);
			arr[8][8] = 1;
			flag++;
			count++;
			fprintf(fq, "%d ", 8);
			fprintf(fq, "%d ", 8);
		}
		if (flag % 2 == 0)
		{
			Sleep(500);
			if (arr[a][b] != 0)
			{
				int dx1[] = { -1,0,1,0 };
				int dy1[] = { 0, -1,0,1 };
				int count = 0;
				int randPos[4][2];
				int k = 0;
				int sum1 = 0;
				int sum2 = 0;
				//判断行电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
				for (i = 0; i < 16; i++)
				{
					for (j = 0; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i][j + k] == 1)
							{
								sum2++;
							}
						}
						if (sum2 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i][j + k] == 0)
								{
									j += k;
									goto change;
									//printf("行四子连五\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断列电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
				for (j = 0; j < 16; j++)
				{
					for (i = 0; i < 16 - 4; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j] == 1)
							{
								sum2++;
							}
						}
						if (sum2 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j] == 0)
								{
									i += k;
									goto change;
									//printf("列四子连五\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j + k] == 1)
							{
								sum2++;
							}
						}
						if (sum2 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j + k] == 0)
								{
									i += k;
									j += k;
									goto change;
									//printf("对角线四子连五\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断反对角线电脑是否已经连成四子，如果连成四子，则下第五子获得胜利
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 4; j < 16; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j - k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j - k] == 1)
							{
								sum2++;
							}
						}
						if (sum2 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j - k] == 0)
								{
									i += k;
									j -= k;
									goto change;
									//printf("反对角线四子连五\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断行玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
				for (i = 1; i < 16; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i][j + k] == 1)
							{
								sum2++;
							}
						}
						if (sum1 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i][j + k] == 0)
								{
									
									j += k;
									goto change;
									//printf("行玩家四子，阻挡玩家五子\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断列玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
				for (j = 1; j < 16; j++)
				{
					for (i = 1; i < 16 - 4; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j] == 1)
							{
								sum2++;
							}
						}
						if (sum1 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j] == 0)
								{
									i += k;
									goto change;
									//printf("列玩家四子，阻挡玩家五子\n");

								}
							}
						}

						sum1 = sum2 = 0;
					}
				}

				//判断对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j + k] == 1)
							{
								sum2++;
							}
						}
						if (sum1 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j + k] == 0)
								{
									i = i + k;
									j += k;
									goto change;
									//printf("对角线玩家四子，阻挡玩家五子\n");

								}
							}
						}

						sum1 = sum2 = 0;
					}
				}

				//判断反对角线玩家是否已经连成四子，如果连成四子，则下子阻挡玩家获得胜利
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 4; j < 16; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j - k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j - k] == 1)
							{
								sum2++;
							}
						}
						if (sum1 > 3)
						{
							for (k = 0; k < 5; k++)
							{
								if (arr[i + k][j - k] == 0)
								{
									i = i + k;
									j = j - k;
									goto change;
									//printf("反对角线玩家四子，阻挡玩家五子\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}
				//判断行电脑是否有三子，有的话连成四子
				for (i = 1; i < 16; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i][j + k] == 1)
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
								if (arr[i][j + k] == 0 && ((arr[i][j + k + 1] == 1 || arr[i][j + k - 1] == 1))
									&& (j + k + 2) < 16 && (j + k - 2) > 0)
								{
									j += k;
									goto change;
									//printf("行电脑三子，连三成四\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断列电脑是否有三子，有的话连成四子
				for (j = 1; j < 16; j++)
				{
					for (i = 1; i < 16 - 4; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j] == 1)
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
								if (arr[i + k][j] == 0 && ((arr[i + k + 1][j] == 1 || arr[i + k - 1][j] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									goto change;
									//printf("列电脑三子，连三成四\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断对角线电脑是否有三子，有的话连成四子
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j + k] == 1)
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
								if (arr[i + k][j + k] == 0 && ((arr[i + k + 1][j + k + 1] == 1 || arr[i + k - 1][j + k - 1] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									j = j + k;
									goto change;
									//printf("对角线电脑三子，连三成四\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断反对角线电脑是否有三子，有的话连成四子
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 4; j < 16; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j - k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j - k] == 1)
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
								if (arr[i + k][j - k] == 0 && ((arr[i + k + 1][j - k - 1] == 1 || arr[i + k - 1][j - k + 1] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									j = j - k;
									goto change;
									//printf("反对角线电脑三子，连三成四\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断行玩家是否连成三子，若连成三子，则堵住玩家
				for (i = 1; i < 16; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i][j + k] == 1)
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
								if (arr[i][j + k] == 0 && (arr[i][j + k + 1] == 2 || arr[i][j + k - 1] == 2)
									&& (j + k + 2) < 16 && (j + k - 2) > 0)
								{
									j = j + k;
									goto change;
									//printf("行玩家三子，阻挡玩家四子\n");

								}
							}
						}

						sum1 = sum2 = 0;
					}
				}

				//判断列玩家是否连成三子，若连成三子，则堵住玩家
				for (j = 1; j < 16; j++)
				{
					for (i = 1; i < 16 - 4; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j] == 1)
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
								if (arr[i + k][j] == 0 && (arr[i + k + 1][j] == 2 || arr[i + k - 1][j] == 2)
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									goto change;
									//printf("列玩家三子，阻挡玩家四子\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断对角线玩家是否连成三子，若连成三子，则堵住玩家
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j + k] == 1)
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
								if (arr[i + k][j + k] == 0 && (arr[i + k + 1][j + k + 1] == 2 || arr[i + k - 1][j + k - 1] == 2)
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									j = j + k;
									i = i + k;
									goto change;
									//printf("对角线玩家三子，阻挡玩家四子\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断反对角线玩家是否连成三子，若连成三子，则堵住玩家
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 4; j < 16; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j - k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j - k] == 1)
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
								if (arr[i + k][j - k] == 0 && (arr[i + k + 1][j - k - 1] == 2 || arr[i + k - 1][j - k + 1] == 2)
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									j = j - k;
									goto change;
									//printf("反对角线玩家三子，阻挡玩家四子\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断行电脑是否连成两子，若连成两子，则下子使电脑连成三子
				for (i = 1; i < 16; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i][j + k] == 1)
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
								if (arr[i][j + k] == 0 && ((arr[i][j + k + 1] == 1 || arr[i][j + k - 1] == 1))
									&& (j + k + 2) < 16 && (j + k - 2) > 0)
								{
									j = j + k;
									goto change;
									//printf("行电脑二子，连二成三\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断列电脑是否连成两子，若连成两子，则下子使电脑连成三子
				for (j = 1; j < 16; j++)
				{
					for (i = 1; i < 16 - 4; i++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j] == 1)
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
								if (arr[i + k][j] == 0 && ((arr[i + k + 1][j] == 1 || arr[i + k - 1][j] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									goto change;
									//printf("列电脑二子，连二成三\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 1; j < 16 - 4; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j + k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j + k] == 1)
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
								if (arr[i + k][j + k] == 0 && ((arr[i + k + 1][j + k + 1] == 1 || arr[i + k - 1][j + k - 1] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									j = j + k;
									goto change;
									//printf("对角线电脑二子，连二成三\n");

								}
							}
						}
						sum1 = sum2 = 0;
					}
				}

				//判断反对角线电脑是否连成两子，若连成两子，则下子使电脑连成三子
				for (i = 1; i < 16 - 4; i++)
				{
					for (j = 4; j < 16; j++)
					{
						for (k = 0; k < 5; k++)
						{
							if (arr[i + k][j - k] == 2)
							{
								sum1++;
							}
							else if (arr[i + k][j - k] == 1)
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
								if (arr[i + k][j - k] == 0 && ((arr[i + k + 1][j - k - 1] == 1 || arr[i + k - 1][j - k + 1] == 1))
									&& (i + k + 2) < 16 && (i + k - 2) > 0)
								{
									i = i + k;
									j = j - k;
									goto change;
									//printf("反对角线电脑二子，连二成三\n");

								}
							}
						}
						sum1 = sum2 = 0;

					}
				}

				// 如果人已经落子，AI在四周随机落子
				for (int o = 0; o < 4; o++)
				{
					int newRow = a + dx1[o];
					int newCol = b + dy1[o];
					if (newRow >= 0 && newRow < 16 && newCol >= 0 && newCol < 16 && arr[newRow][newCol] == 0)
					{
						randPos[count][0] = newRow;
						randPos[count][1] = newCol;
						count++;
					}
				}
				if (count > 0)
				{
					int randomIndex = rand() % count;
					i = randPos[randomIndex][0];
					j = randPos[randomIndex][1];
				}
			}
		change:
			setfillcolor(BLACK);
			solidcircle(i * 32 + 16, j * 32 + 5, 12);
			arr[i][j] = 1;
			fprintf(fq, "%d ", i);
			fprintf(fq, "%d ", j);
			setfillcolor(BLACK);
			drawtext(_T("该你下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			ret = is_win(arr, count);
			if (ret)
			{
				judge_winPVE(ret);
				break;
			}
			flag++;
			count++;
		}
		//人的部分
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (i = 1; i < 16; i++)
			{
				for (j = 1; j < 16; j++)
				{
					if (abs(m.x - i * 32 - 16) < 16 && abs(m.y - j * 32 - 5) < 16)
					{
						x = i * 32 + 16;
						y = j * 32 + 5;
						a = i;
						b = j;
					}
				}
			}
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			if (arr[a][b])
			{
				MessageBox(NULL, L"这里已经有棋子了", L"", MB_OK);
				continue;
			}
			if (m.x < 16 || m.x>517 || m.y < 5 || m.y > 527)
			{
				MessageBox(NULL, L"你下的棋子不在棋盘内", L"", MB_OK);
				continue;
			}
			if (flag % 2 == 1)
			{
				setfillcolor(WHITE);
				fillrectangle(r4[0], r4[1], r4[2], r4[3]);
				solidcircle(x, y, 12);
				arr[a][b] = 2;
				flag++;
				count++;
				fprintf(fq, "%d ", a);
				fprintf(fq, "%d ", b);
				ret = is_win(arr, count);
				if (ret)
				{
					judge_winPVE(ret);
					break;
				}
			}
		}
	}
	fclose(fq);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			else if (m.x > r6[0] && m.x<r6[2] && m.y>r6[1] && m.y < r6[3])
			{
				closegraph();
				fupanPVE();
			}
			else if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3])
			{
				closegraph();
				menu();
			}
		}
	}
}
void PVE()
{
	int x = 0, y = 0;
	int a = 0, b = 0, i = 0, j = 0;
	memset(arr, 0, sizeof(int[16][16]));
	FILE* file = fopen("PVE.txt", "w");
	fclose(file);
	count = 0;
	FILE* fq = fopen("PVE.txt", "a+");
	print_board();
	fillrectangle(r4[0], r4[1], r4[2], r4[3]);
	drawtext(_T("电脑先下"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	fillrectangle(r5[0], r5[1], r5[2], r5[3]);
	drawtext(_T("我先下"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r4[0] && m.x<r4[2] && m.y>r4[1] && m.y < r4[3])
			{
				flag3 = 0;
				flag = 0;
				break;
			}
			else if (m.x > r5[0] && m.x<r5[2] && m.y>r5[1] && m.y < r5[3])
			{
				flag3 = 1;
				flag = 1;
				break;
			}
			else
			{
				MessageBox(NULL, L"请选择先后", L"", MB_OK);
			}
		}
	}
	while (1)
	{
		//机器部分
		if (flag == 0)
		{
			setfillcolor(BLACK);
			solidcircle(271, 261, 12);
			arr[8][8] = 1;
			flag++;
			count++;
			fprintf(fq, "%d ", 8);
			fprintf(fq, "%d ", 8);
		}
		if (flag % 2 == 0)
		{
			Sleep(500);
			computer(arr);
			find_max(&i, &j, arr);
			setfillcolor(BLACK);
			solidcircle(i * 32 + 15, j * 32 + 5, 12);
			arr[i][j] = 1;
			fprintf(fq, "%d ", i);
			fprintf(fq, "%d ", j);
			setfillcolor(BLACK);
			drawtext(_T("该你下棋了"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			ret = is_win(arr, count);
			if (ret)
			{
				judge_winPVE(ret);
				break;
			}
			flag++;
			count++;
		}
		//人的部分
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (i = 1; i < 16; i++)
			{
				for (j = 1; j < 16; j++)
				{
					if (abs(m.x - i * 32 - 15) < 16 && abs(m.y - j * 32 - 5) < 16)
					{
						x = i * 32 + 15;
						y = j * 32 + 5;
						a = i;
						b = j;
					}
				}
			}
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			if (arr[a][b])
			{
				MessageBox(NULL, L"这里已经有棋子了", L"", MB_OK);
				continue;
			}
			if (m.x < 15 || m.x>517 || m.y < 5 || m.y > 527)
			{
				MessageBox(NULL, L"你下的棋子不在棋盘内", L"", MB_OK);
				continue;
			}
			if (flag % 2 == 1)
			{
				setfillcolor(WHITE);
				fillrectangle(r4[0], r4[1], r4[2], r4[3]);
				solidcircle(x, y, 12);
				arr[a][b] = 2;
				flag++;
				count++;
				fprintf(fq, "%d ", a);
				fprintf(fq, "%d ", b);
				ret = is_win(arr, count);
				if (ret)
				{
					judge_winPVE(ret);
					break;
				}
			}
		}
	}
	fclose(fq);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > r7[0] && m.x<r7[2] && m.y>r7[1] && m.y < r7[3])
			{
				exit(0);
			}
			else if (m.x > r6[0] && m.x<r6[2] && m.y>r6[1] && m.y < r6[3])
			{
				closegraph();
				fupanPVE();
			}
			else if (m.x > r1[0] && m.x<r1[2] && m.y>r1[1] && m.y < r1[3])
			{
				closegraph();
				menu();
			}
		}
	}
}

void menu()
{
	initgraph(520, 550);//初始化界面
	IMAGE back;//定义图片接收
	loadimage(&back, _T("背景图片.png"));//接收图片
	putimage(0, 0, &back);//输出图片
	MOUSEMSG m;//鼠标指针
	while (1)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)//当鼠标落下时
		{
			switch (button_judge(m.x, m.y))
			{
			case 0:
				break;
			case 1:
				closegraph();
				PVP();
				break;
			case 2:
				closegraph();
				PVE2();
				break;
			case 3:
				closegraph();
				PVE();
				break;
			case 5:
				closegraph();
				exit(0);
			}
		}
	}
}

int main()
{
	menu();
	return 0;
}