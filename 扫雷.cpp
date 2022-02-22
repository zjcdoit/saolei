#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h> 
#include <graphics.h>
#include <windows.h>

//管理员界面
#define row 22 //此数值为所需行数加二
#define col 22 //此数值为所需列数加二
#define boom 40 //雷数

#define esc 27
int map[row][col];
int winscore = 0;
double a[100],b[1];
IMAGE img[10];
clock_t start, end;
FILE* num;
FILE* cishu;
FILE* paihang;
FILE* fp = NULL;
FILE* win;

void set_boom()
{
	//布雷 
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= boom ; i++)
	{
		int r = rand() % (row-1);
		int c = rand() % (col-1);
		if (map[r][c] != -1)
		{
			if (r > 0 && r < row-1 && c>0 && c < col-1)
			{
				map[r][c] = -1;
			}
			//防止重复布雷
			else
			{
				i--;
			}
		}
		else
		{
			i--;
		}

	}
	//布其他格子	
	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			if (map[i][j] != -1)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (map[m][n] == -1)
						{
							map[i][j]++;
						}
					}
				}
			}
		}
	}
	//变成空白格
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			map[i][j] += 30;
		}
	}
}

void print_map()
{
	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			if (map[i][j] == -1)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[0]);
			}
			else if (map[i][j] == 0)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[4]);
			}
			else if (map[i][j] == 1)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[1]);
			}
			else if (map[i][j] == 2)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[2]);
			}
			else if (map[i][j] == 3)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[3]);
			}
			else if (map[i][j] == 4)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[5]);
			}
			else if (map[i][j] == 5)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[6]);
			}
			else if (map[i][j] == 6)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[7]);
			}
			else if (map[i][j] >=29&&map[i][j]<=36)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[9]);
			}
			else if (map[i][j]>37)
			{
				putimage((i - 1) * 30, (j - 1) * 30, &img[8]);
			}

		}
		printf("\n");
	}
}

void set_tu()
{
	loadimage(&img[0], L"boom.png", 30, 30);
	loadimage(&img[1], L"1.png", 30, 30);
	loadimage(&img[2], L"2.png", 30, 30);
	loadimage(&img[3], L"3.png", 30, 30);
	loadimage(&img[4], L"0.png", 30, 30);
	loadimage(&img[5], L"4.png", 30, 30);
	loadimage(&img[9], L"9.png", 30, 30);
	loadimage(&img[8], L"8.png", 30, 30);
	loadimage(&img[7], L"7.png", 30, 30);
	loadimage(&img[6], L"6.png", 30, 30);
}

void open_it(int r,int c)//让点到的零全部打开
{
	map[r][c] -= 30;
	winscore++;
	for (int m = r - 1; m <= r + 1; m++)
	{
		for (int n = c - 1; n <= c + 1; n++)
		{
			if (m > 0 && m < row - 1 && n>0 && n < col - 1)
			{
				if (map[m][n] >= 29 && map[m][n] <= 36)
				{
					if (map[m][n] != 30)
			        {
				       winscore++;
				       map[m][n] -= 30;
			        }
					else if (map[m][n] == 30)
					{
						open_it(m, n);
					}
				}
				
			}
			
		}
	}
}

//游戏运行
int play_it()
{
	MOUSEMSG msg = { 0 };
	int r, c;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			r = msg.x / 30 + 1;
			c = msg.y / 30 + 1;
			//翻开图片
			
			if (map[r][c] >= 29 && map[r][c] <= 36)
			{
				if (map[r][c] == 30)//翻开周围全部零
				{
					open_it(r, c);
				}
				else
				{
					map[r][c] -= 30;
					winscore++;
				}
				
			}
			return map[r][c];
			     break;
		case WM_RBUTTONDOWN:
			r = msg.x / 30 + 1;
			c = msg.y / 30 + 1;
			if (map[r][c] >= 29 && map[r][c] <= 36)
			{
				map[r][c] += 20;
			}
			else if (map[r][c] >37)
			{
				   map[r][c] -= 20;
			}
			return map[r][c];
			     break;
		}
		//退出时存档
	    if (_kbhit())
	    {
		    if (_getch() == esc)
		    {
				int a[(row - 2) * (col - 2)]; int k = 0;
				num = fopen("memory.txt", "w+");
				for (int i = 1; i < row - 1; i++)
				{
					for (int j = 1; j < col - 1; j++)
					{
						a[k] = map[i][j];
						k++;
					}
				}
				fwrite(a,sizeof(int),(row-2)*(col-2),num);
				fclose(num);
				win = fopen("winwin.txt", "w+");
				fprintf(win, "%d", winscore);
				fclose(win);
				break;
		    }
	    }
	}
}

//储存游戏次数
int game_shu()
{
	int n=0;
	cishu = fopen("次数.txt", "a+");
	if (cishu!=0)
	{
		fscanf_s(cishu, "%d",&n);
	}
	n++;
	fclose(cishu);
	
	cishu = fopen("次数.txt", "w+");
	fprintf(cishu, "%d",n);
	fclose(cishu);
	return n;
}

//为结果排序
double rank(double a[100], int n)
{
	double t = 0.0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
	return a[100];
}

//主函数
int main()
{
	int n;
	int ret= MessageBox(NULL, L"按“是”开始扫雷（按“esc”存档），按“否”看排行榜", L"开始界面：是否开始扫雷？", MB_YESNO);
	if (ret == IDYES)
	{
	   int rep= MessageBox(NULL, L"按“是”读档，按“否”直接开", L"界面：是否要读档？", MB_YESNO);
	   //正常游戏
	   if (rep == IDNO)
	   {
		   HWND hwnd = initgraph((row - 2) * 30, (col - 2) * 30,SHOWCONSOLE);
	       set_tu();
	       set_boom();
	       start = clock();
	       while (1)
	       {
	           print_map();
	          if (play_it() == -1)
	          { 
		          print_map();
		          MessageBox(hwnd, L"呜呜呜你被炸死了  *_*", L"you   lose", MB_OK);
		          break;
	          }
	          if (winscore == ((row - 2) * (col - 2) - boom))
	          {
		          print_map();
		          end = clock();
		          double wintime = (double)(end-start) / CLOCKS_PER_SEC;
			      printf("你这次的成绩为：%lf s！！！\n", wintime);
				  printf("你这次的成绩为：%lf s！！！\n", wintime);
				  printf("你这次的成绩为：%lf s！！！\n", wintime);
				  b[0]= wintime;
				  MessageBox(hwnd, L"NB NB 记得查看成绩欧", L"you    win", MB_OK);
				  
				  n=game_shu();
				  fp = fopen("list.txt", "a");
				  fwrite(b, sizeof(double), 1, fp);
				  fclose(fp);
				  fp = fopen("list.txt", "r");
				  fread(a, sizeof(double), n, fp);
				  fclose(fp);
				  rank(a, n);
				  paihang = fopen("排行榜.txt","w+");
				  fprintf(paihang, "排名    成绩\n");
				  for (int i = 0; i < n; i++)
				  {
					  fprintf(paihang,"%d      %lf 秒\n",i+1,a[i]);
				  }
				  fclose(paihang);
		          break;
	          }
	       }
	         closegraph();
	   }
	   //读档
	   else
	   {
		   int n = 0;
		   int a[(row - 2) * (col - 2)];
		   HWND hwnd = initgraph((row - 2) * 30, (col - 2) * 30, SHOWCONSOLE);
		   set_tu();
		   if ((num = fopen("memory.txt", "r")) != NULL)
		   {
			   fread(a, sizeof(int), (row - 2) * (col - 2), num);
		   }
		   if (fclose(num))
		   {
			   exit(0);
		   }
		   int k = 0;
		   for (int i = 1; i < row - 1; i++)
		   {
			   for (int j = 1; j < col - 1; j++)
			   {
				   map[i][j] = a[k];
				   k++;
			   }
		   }
		   if ((win = fopen("winwin.txt","r")) != NULL)
		   {
			   fscanf_s(win, "%d", &winscore);
		   }
		   fclose(win);
		   start = clock();
		   while (1)
		   {
			   print_map();
			   if (play_it() == -1)
			   {
				   print_map();
				   MessageBox(hwnd, L"重开吧兄弟", L"you    lose", MB_OK);
				   break;
			   }
			   if (winscore == ((row - 2) * (col - 2) - boom))
			   {
				   print_map();
				   end = clock();
				   double wintime = (double)(end - start) / CLOCKS_PER_SEC;
				   printf("你这次的成绩为：%lf,存档游戏没有排名欧", wintime);
				   MessageBox(hwnd, L"you   win  读档没有排名欧", L"nb  nb", MB_OK);
				   break;
			   }
		   }
		   closegraph();
	   }
	}
	//打开排行榜
	else
	{
		ShellExecute(NULL,L"open", L"C:\\Users\\DELL\\Desktop\\扫个雷\\扫雷2\\扫雷2\\排行榜.txt", NULL, NULL, SW_SHOW);
	}
	return 0;
}