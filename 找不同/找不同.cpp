#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <math.h>

//ͼƬ����
IMAGE background;  //����ͼ
IMAGE game;  //��Ϸͼ

int count = 4;
time_t start, end;  //��ʱ

struct axis {  //����
	double x, y;
};

struct axis a[10];   //��ŵ��������
int a_len = 0;  //�����ʵ�ʳ���

struct axis b[10] = { {360,300},{380,510},{450,520},{290,500} };   //�����ȷ������

	
int main();

//��Ϸʤ��
bool isWin() {
	if (a_len < 4) {  //ѡ�����������  ������Ӯ
		return false;
	}
	int i, j;
	int flg;
	//�ж��ĸ��㶼��ѡ������
	for (i = 0; i < 4; i++) {
		flg = 0;
		for (j = 0; j < 4; j++) {
			if (pow(pow((a[i].x - b[j].x), 2) + pow((a[i].y - b[j].y), 2), 0.5) < 20) {  //Ȧ����ȷ��
				flg = 1;
				break;
			}
		}
		if (flg == 0) {
			return false;
		}
	}
	return true;
}

//������Ϸ
void drawGame() {
	putimage(0, 0, &background);  //���ñ���ͼƬ
	putimage(0, 0, &game);  //������ϷͼƬ

	//���� ���¿�ʼ �� �˳���Ϸ
	settextcolor(BLACK);          //����������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��

	outtextxy(550, 200, "ʣ��:");
	outtextxy(550, 250, "��ʱ:");
	char str[10];
	sprintf(str, "%d��", count);
	outtextxy(630, 200, str);
	sprintf(str, "%d��", end - start);
	outtextxy(630, 250, str);

	outtextxy(550, 400, "��Ϸ����");
	outtextxy(550, 450, "���¿�ʼ");
	outtextxy(550, 500, "�˳���Ϸ");

	setcolor(RED);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����

	//circle(360, 300, 25);
	//circle(380, 510, 25);
	//circle(450, 520, 25);
	//circle(290, 500, 25);
	//rectangle(260, 125, 480, 580);

	//�������ԲȦ
	int i;
	for (i = 0; i < a_len; i++) {
		circle(a[i].x, a[i].y, 25);
	}

	
}


//����Ϸ
void playGame() {
	start = time(NULL);  //��ʱ��ʼ

	MOUSEMSG m;  //������   ������ȡ�����Ϣ
	int n = 0;    //ÿ���ν���һ��
	int i, j;
	bool over = false; //��Ϸ����
	while (true) {
		
		//��ȡ���λ��
		if (MouseHit() || over) {  //���������Ϣ
			m = GetMouseMsg();
			if (m.x >= 550 && m.x <= 670 && m.y >= 400 && m.y <= 430 && !over) {  //��Ϸ����   ��ûӮ�������
				if (m.uMsg == WM_LBUTTONDOWN) {  //��갴��
					//��Ϸ����
					settextcolor(GREEN);          //����������ɫ
					settextstyle(30, 0, "������κ"); //����������ʽ
					setbkmode(TRANSPARENT);       //���ֱ���͸��
					outtextxy(550, 100, "��Ϸʧ��");

					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����
					circle(130, 300, 25);
					circle(150, 510, 25);
					circle(220, 520, 25);
					circle(60, 500, 25);

					//��ѡ�����ȷ�ʹ�������ж�
					
					for (i = 0; i < a_len; i++) {
						for (j = 0; j < 4; j++) {
							if (pow(pow((a[i].x - b[j].x), 2) + pow((a[i].y - b[j].y), 2), 0.5) < 20) {  //Ȧ����ȷ��
								setcolor(GREEN);
								circle(a[i].x, a[i].y, 25);
								break;
							}
						}
						if (j == 4) {
							setcolor(RED);
							circle(a[i].x, a[i].y, 25);
						}
					}
					over = true;
				}
			}
			else if (m.x >= 550 && m.x <= 670 && m.y >= 450 && m.y <= 480) {  //���¿�ʼ
				if (m.uMsg == WM_LBUTTONDOWN) {  //��갴��
					main(); //���¿�ʼ
				}
			}
			else if (m.x >= 550 && m.x <= 670 && m.y >= 500 && m.y <= 530) {  //�˳���Ϸ
				if (m.uMsg == WM_LBUTTONDOWN) {  //��갴��
					exit(0); //�˳���Ϸ
				}
			}
			else if (m.x >= 260 && m.x <= 480 && m.y >= 125 && m.y <= 580) {  //��ͼ��
				if (m.uMsg == WM_LBUTTONDOWN && count > 0) {  //������
					count--;  //������1
					//��¼�������������
					a[a_len].x = m.x;
					a[a_len].y = m.y;
					a_len++;
					if (isWin()) {  //��Ϸʤ��
						//��ʼ˫�����ͼ
						BeginBatchDraw();
						end = time(NULL);  //��ʱ����
						cleardevice();
						drawGame();
						//����˫�����ͼ
						EndBatchDraw();

						settextcolor(GREEN);          //����������ɫ
						settextstyle(30, 0, "������κ"); //����������ʽ
						setbkmode(TRANSPARENT);       //���ֱ���͸��
						outtextxy(550, 100, "��Ϸʤ��");

						setcolor(GREEN);
						setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //�Ӵ�����
						circle(130, 300, 25);
						circle(150, 510, 25);
						circle(220, 520, 25);
						circle(60, 500, 25);
						over = true;
					}
				}
				else if (m.uMsg == WM_RBUTTONDOWN && count < 4) { //����һ�
					//�ж���û��  ��ԲȦ�Ļ�����
					for (i = 0; i < a_len; i++) {
						if (pow(pow((a[i].x - m.x), 2) + pow((a[i].y - m.y), 2), 0.5) < 25) {   //��Ȧ��
							count++;  //������1
							a_len--;  //����һ��Ȧ
							for (j = i; j < a_len; j++) {
								a[j] = a[j + 1];
							}
							break;
						}
					}
				}
			}
		}

		else {
			//��ʼ˫�����ͼ
			BeginBatchDraw();
			end = time(NULL);  //��ʱ����
			cleardevice();
			drawGame();
			//����˫�����ͼ
			EndBatchDraw();
		}
		
	}
}


int main() {
	//��ʼ������
	count = 4;
	memset(a, 0, sizeof(a));
	a_len = 0;
	//������Դ
	loadimage(&background, "background.jpg", 800, 600);  //��ȡ����ͼƬ
	loadimage(&game, "game.jpg", 500, 600);  //��ȡ��ϷͼƬ
	initgraph(800, 600);  //���ɻ���
	drawGame();
	playGame();
}