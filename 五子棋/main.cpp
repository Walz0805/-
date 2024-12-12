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

// �����Ѷ��˻�����
void aiMoveHard(Game* pthis);

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
                    // �����Ѷ�AI���ӣ��˴�Ϊռλ��ʵ����ʵ�ּ�֦�;������㷨
                    aiMoveHard(&game);
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
void aiMoveHard(Game* pthis) {

}