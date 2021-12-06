#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <math.h>

//图片变量
IMAGE background;  //背景图
IMAGE game;  //游戏图

int count = 4;
time_t start, end;  //计时

struct axis {  //坐标
	double x, y;
};

struct axis a[10];   //存放点击的坐标
int a_len = 0;  //数组的实际长度

struct axis b[10] = { {360,300},{380,510},{450,520},{290,500} };   //存放正确的坐标

	
int main();

//游戏胜利
bool isWin() {
	if (a_len < 4) {  //选择次数不到四  不可能赢
		return false;
	}
	int i, j;
	int flg;
	//判断四个点都被选中了吗
	for (i = 0; i < 4; i++) {
		flg = 0;
		for (j = 0; j < 4; j++) {
			if (pow(pow((a[i].x - b[j].x), 2) + pow((a[i].y - b[j].y), 2), 0.5) < 20) {  //圈中正确点
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

//绘制游戏
void drawGame() {
	putimage(0, 0, &background);  //放置背景图片
	putimage(0, 0, &game);  //放置游戏图片

	//绘制 重新开始 和 退出游戏
	settextcolor(BLACK);          //设置字体颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明

	outtextxy(550, 200, "剩余:");
	outtextxy(550, 250, "用时:");
	char str[10];
	sprintf(str, "%d个", count);
	outtextxy(630, 200, str);
	sprintf(str, "%d秒", end - start);
	outtextxy(630, 250, str);

	outtextxy(550, 400, "游戏认输");
	outtextxy(550, 450, "重新开始");
	outtextxy(550, 500, "退出游戏");

	setcolor(RED);
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线

	//circle(360, 300, 25);
	//circle(380, 510, 25);
	//circle(450, 520, 25);
	//circle(290, 500, 25);
	//rectangle(260, 125, 480, 580);

	//画点击的圆圈
	int i;
	for (i = 0; i < a_len; i++) {
		circle(a[i].x, a[i].y, 25);
	}

	
}


//玩游戏
void playGame() {
	start = time(NULL);  //计时开始

	MOUSEMSG m;  //鼠标变量   用来获取鼠标信息
	int n = 0;    //每两次交换一次
	int i, j;
	bool over = false; //游戏结束
	while (true) {
		
		//获取鼠标位置
		if (MouseHit() || over) {  //存在鼠标消息
			m = GetMouseMsg();
			if (m.x >= 550 && m.x <= 670 && m.y >= 400 && m.y <= 430 && !over) {  //游戏认输   在没赢的情况下
				if (m.uMsg == WM_LBUTTONDOWN) {  //鼠标按下
					//游戏认输
					settextcolor(GREEN);          //设置字体颜色
					settextstyle(30, 0, "华文新魏"); //设置文字样式
					setbkmode(TRANSPARENT);       //文字背景透明
					outtextxy(550, 100, "游戏失败");

					setcolor(GREEN);
					setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线
					circle(130, 300, 25);
					circle(150, 510, 25);
					circle(220, 520, 25);
					circle(60, 500, 25);

					//对选择的正确和错误进行判断
					
					for (i = 0; i < a_len; i++) {
						for (j = 0; j < 4; j++) {
							if (pow(pow((a[i].x - b[j].x), 2) + pow((a[i].y - b[j].y), 2), 0.5) < 20) {  //圈中正确点
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
			else if (m.x >= 550 && m.x <= 670 && m.y >= 450 && m.y <= 480) {  //重新开始
				if (m.uMsg == WM_LBUTTONDOWN) {  //鼠标按下
					main(); //重新开始
				}
			}
			else if (m.x >= 550 && m.x <= 670 && m.y >= 500 && m.y <= 530) {  //退出游戏
				if (m.uMsg == WM_LBUTTONDOWN) {  //鼠标按下
					exit(0); //退出游戏
				}
			}
			else if (m.x >= 260 && m.x <= 480 && m.y >= 125 && m.y <= 580) {  //在图内
				if (m.uMsg == WM_LBUTTONDOWN && count > 0) {  //鼠标左击
					count--;  //个数减1
					//记录下来点击的坐标
					a[a_len].x = m.x;
					a[a_len].y = m.y;
					a_len++;
					if (isWin()) {  //游戏胜利
						//开始双缓冲绘图
						BeginBatchDraw();
						end = time(NULL);  //计时结束
						cleardevice();
						drawGame();
						//结束双缓冲绘图
						EndBatchDraw();

						settextcolor(GREEN);          //设置字体颜色
						settextstyle(30, 0, "华文新魏"); //设置文字样式
						setbkmode(TRANSPARENT);       //文字背景透明
						outtextxy(550, 100, "游戏胜利");

						setcolor(GREEN);
						setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);  //加粗虚线
						circle(130, 300, 25);
						circle(150, 510, 25);
						circle(220, 520, 25);
						circle(60, 500, 25);
						over = true;
					}
				}
				else if (m.uMsg == WM_RBUTTONDOWN && count < 4) { //鼠标右击
					//判断有没有  有圆圈的话消除
					for (i = 0; i < a_len; i++) {
						if (pow(pow((a[i].x - m.x), 2) + pow((a[i].y - m.y), 2), 0.5) < 25) {   //在圈内
							count++;  //次数加1
							a_len--;  //减少一个圈
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
			//开始双缓冲绘图
			BeginBatchDraw();
			end = time(NULL);  //计时结束
			cleardevice();
			drawGame();
			//结束双缓冲绘图
			EndBatchDraw();
		}
		
	}
}


int main() {
	//初始化变量
	count = 4;
	memset(a, 0, sizeof(a));
	a_len = 0;
	//加载资源
	loadimage(&background, "background.jpg", 800, 600);  //读取背景图片
	loadimage(&game, "game.jpg", 500, 600);  //读取游戏图片
	initgraph(800, 600);  //生成画布
	drawGame();
	playGame();
}