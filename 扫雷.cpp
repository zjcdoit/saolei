#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h> 
#include <graphics.h>
#include <windows.h>

//����Ա����
#define row 22 //����ֵΪ���������Ӷ�
#define col 22 //����ֵΪ���������Ӷ�
#define boom 40 //����

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
	//���� 
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
			//��ֹ�ظ�����
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
	//����������	
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
	//��ɿհ׸�
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

void open_it(int r,int c)//�õ㵽����ȫ����
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

//��Ϸ����
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
			//����ͼƬ
			
			if (map[r][c] >= 29 && map[r][c] <= 36)
			{
				if (map[r][c] == 30)//������Χȫ����
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
		//�˳�ʱ�浵
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

//������Ϸ����
int game_shu()
{
	int n=0;
	cishu = fopen("����.txt", "a+");
	if (cishu!=0)
	{
		fscanf_s(cishu, "%d",&n);
	}
	n++;
	fclose(cishu);
	
	cishu = fopen("����.txt", "w+");
	fprintf(cishu, "%d",n);
	fclose(cishu);
	return n;
}

//Ϊ�������
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

//������
int main()
{
	int n;
	int ret= MessageBox(NULL, L"�����ǡ���ʼɨ�ף�����esc���浵���������񡱿����а�", L"��ʼ���棺�Ƿ�ʼɨ�ף�", MB_YESNO);
	if (ret == IDYES)
	{
	   int rep= MessageBox(NULL, L"�����ǡ�������������ֱ�ӿ�", L"���棺�Ƿ�Ҫ������", MB_YESNO);
	   //������Ϸ
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
		          MessageBox(hwnd, L"�������㱻ը����  *_*", L"you   lose", MB_OK);
		          break;
	          }
	          if (winscore == ((row - 2) * (col - 2) - boom))
	          {
		          print_map();
		          end = clock();
		          double wintime = (double)(end-start) / CLOCKS_PER_SEC;
			      printf("����εĳɼ�Ϊ��%lf s������\n", wintime);
				  printf("����εĳɼ�Ϊ��%lf s������\n", wintime);
				  printf("����εĳɼ�Ϊ��%lf s������\n", wintime);
				  b[0]= wintime;
				  MessageBox(hwnd, L"NB NB �ǵò鿴�ɼ�ŷ", L"you    win", MB_OK);
				  
				  n=game_shu();
				  fp = fopen("list.txt", "a");
				  fwrite(b, sizeof(double), 1, fp);
				  fclose(fp);
				  fp = fopen("list.txt", "r");
				  fread(a, sizeof(double), n, fp);
				  fclose(fp);
				  rank(a, n);
				  paihang = fopen("���а�.txt","w+");
				  fprintf(paihang, "����    �ɼ�\n");
				  for (int i = 0; i < n; i++)
				  {
					  fprintf(paihang,"%d      %lf ��\n",i+1,a[i]);
				  }
				  fclose(paihang);
		          break;
	          }
	       }
	         closegraph();
	   }
	   //����
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
				   MessageBox(hwnd, L"�ؿ����ֵ�", L"you    lose", MB_OK);
				   break;
			   }
			   if (winscore == ((row - 2) * (col - 2) - boom))
			   {
				   print_map();
				   end = clock();
				   double wintime = (double)(end - start) / CLOCKS_PER_SEC;
				   printf("����εĳɼ�Ϊ��%lf,�浵��Ϸû������ŷ", wintime);
				   MessageBox(hwnd, L"you   win  ����û������ŷ", L"nb  nb", MB_OK);
				   break;
			   }
		   }
		   closegraph();
	   }
	}
	//�����а�
	else
	{
		ShellExecute(NULL,L"open", L"C:\\Users\\DELL\\Desktop\\ɨ����\\ɨ��2\\ɨ��2\\���а�.txt", NULL, NULL, SW_SHOW);
	}
	return 0;
}