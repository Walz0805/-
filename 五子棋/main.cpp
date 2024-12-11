#include<stdio.h>
#include<easyx.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

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

//��Ϸ�ṹ
struct Game
{
	//0 ��ʾû������ 1��ʾ�� -1 ��ʾ����
	int map[ROWS][COLS];
	//��Ϸ�Ƿ�������
	bool isRunning;
	//������Ϣ����
	ExMessage msg;

	//��굱ǰ���ڵ��±�
	int row;
	int col;

	//��ǰ����
	ChessType currentChessType;

};

//��Ϸ��ʼ��
void init(Game* pthis,int w,int h);
//��Ϸ����
void render(Game* pthis);
//��Ϸ����
void update(Game* pthis);

bool horiaontal(Game* pthis, int chess);
bool vertical(Game* pthis, int chess);
bool leftOblique(Game* pthis, int chess);
bool RightOblique(Game* pthis, int chess);
bool judge(Game* pthis);

int main()
{
	Game game;
	init(&game,960, 600);

	//ͼƬ
	IMAGE img_bg;			//int a
	//error C2665: ��loadimage��: û�����غ�������ת�����в������� -> �ַ���
	loadimage(&img_bg, L"Resource/images/bk.jpg");	//scanf("%a",&a);

	//���������������ϵ�ȥ����
	
	//��Ϸ��ѭ��
	while (game.isRunning)
	{
		if (judge(&game))
		{
			MessageBox(GetHWnd(), L"������", L"....", MB_OK);
			game.isRunning = false;
		}

		//��ȡ��Ϣ
		if (peekmessage(&game.msg))
		{
			//...
			update(&game);
		}

		//��ʼ������ͼ
		BeginBatchDraw();
		//����
		cleardevice();
		putimage(0, 0, &img_bg);

		render(&game);

		//����˫�����ͼ
		EndBatchDraw();

	}

	return 0;
}

void init(Game* pthis,int w, int h)
{
	srand(time(NULL));
	//����һ������
	initgraph(w, h,EX_SHOWCONSOLE);
	pthis->isRunning = true;
	pthis->row = -1;
	pthis->col = -1;
	pthis->currentChessType = rand() % 2 ? Black : White;
	//��ʼ������

	int map[ROWS][COLS] = { 0,1,-1,0,0,0,0,-1,1 };
	memcpy(pthis->map, map, sizeof(int) * ROWS * COLS);
}

void render(Game* pthis)
{
	//��������
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
		{
			if (pthis->map[i][k] != None)
			{
				//��ÿ���������Ͻǵ�����
				int x = k * GRID_SIZE + XOFFSET;
				int y = i * GRID_SIZE + YOFFSET;

				//��������
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

	//���Ƶ�ǰ������ڵ���ʾ��
	printf("%d %d\n", pthis->row, pthis->col);
	if (pthis->row != -1 && pthis->col != -1)
	{
		setlinecolor(BLUE);
		int x = pthis->col * GRID_SIZE + XOFFSET;
		int y = pthis->row * GRID_SIZE + YOFFSET;
		//rectangle(x - 17, y - 17, x + 17, y+17);
		circle(x, y, 17);
	}
}

void update(Game* pthis)
{
	//����ƶ�
	if (pthis->msg.message == WM_MOUSEMOVE)
	{
		/*
		//��ȡ����������
		int mx = pthis->msg.x;
		int my = pthis->msg.y;

		//	int x = k * GRID_SIZE + 213;
		//  int y = i * GRID_SIZE + 34;

		int r = (my - YOFFSET) / GRID_SIZE;
		int c = (mx - XOFFSET) / GRID_SIZE;
		pthis->row = r;
		pthis->col = c;

		printf("(%d %d)------\n", r, c);
		*/

		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				int cx = k * GRID_SIZE + XOFFSET;
				int cy = i * GRID_SIZE + YOFFSET;

				if ( abs(pthis->msg.x - cx )< GRID_SIZE/2 && abs(pthis->msg.y - cy) <GRID_SIZE/2)
				{
					pthis->row = i;
					pthis->col = k;
					goto END_LOOP;
				}
			}
		}
	END_LOOP:;

	}
	else if (pthis->msg.message == WM_LBUTTONDOWN &&		//���������
		pthis->row !=-1 && pthis->col !=-1 &&				//����˺Ϸ���λ��
		pthis->map[pthis->row][pthis->col] == None)			//��ǰλ��û������
	{
		pthis->map[pthis->row][pthis->col] = pthis->currentChessType;

		//�л�����
		pthis->currentChessType =  (ChessType) -pthis->currentChessType;
	}
}

bool judge(Game* pthis)
{
	int who = -pthis->currentChessType;
	if (horiaontal(pthis, who))
		return true;

	if (vertical(pthis, who))
		return true;

	if (leftOblique(pthis, who))
		return true;

	if (RightOblique(pthis, who))
		return true;
	return false;
}

bool horiaontal(Game* pthis, int chess)
{
	//���
	for (int c = pthis->col - 4; c <=pthis->col; c++)
	{
		//����
		/*if (pthis->map[pthis->row][c] == chess && pthis->map[pthis->row][c + 1] == chess &&
			pthis->map[pthis->row][c+2] == chess && pthis->map[pthis->row][c+3] == chess && 
			pthis->map[pthis->row][c+4] == chess)
		{
			return true;
		}
		*/
		//����һ��
		int counter = 0;
		for (int n = 0; n < 5; n++)
		{
			if (pthis->map[pthis->row][c + n] == chess)
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
	return false;
}

bool leftOblique(Game* pthis, int chess)
{
	return false;
}

bool RightOblique(Game* pthis, int chess)
{
	return false;
}