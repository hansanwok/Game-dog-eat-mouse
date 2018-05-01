#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <math.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
char map[50][70];
int score =0;
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, 

		height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle

		(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle

		(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , 

		Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle

		(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void init()
{
	int i,j;
	for(i=0;i<30;i++)
		for(j=0;j<30;j++)
			map[i][j] = ' ';
}
void VeMap1()
{
	int i,j;
	for(i=0;i<23;i++)
		for( j=0;j<70;j++)
		{
			if(i ==22 || i==1 )
			{
				if(j==65 || j == 14 || j==35)
				map[i][j] = char(176);
				else map[i][j] = '_';
			
			}
			else if((j==0 || j==69) && i>=2) map[i][j] =char(177);
			else map[i][j] =' ';
		}
}
void VeDog(int x, int y)
{ /// ve than 
	map[x][y] = char(219);
	map[x][y+1] = char(219);
	map[x][y-1] = char(219);
	/// ve dau
	map[x][y+2] = char(2);
	/// ve chan sau
	map[x+1][y-1] = char(175);
	map[x+1][y+1] = char(175);
	//ve duoi
	map[x][y-2] = '~';
}
void VeMouse(int x1, int y1)
{
	//int Score = 0;
	if(map[x1][y1] == ' ')
	{
		map[x1][y1] = char(4);
		map[x1][y1-1] = char(1);
		map[x1][y1+1] = char(4);
		//Score++;
	}
}
void XoaMouse(int x1,int y1)
{
	//lay than
	map[x1][y1] = ' ';
	map[x1][y1+1] = ' ';
	map[x1][y1-1] = ' ';
}
void VeTrap(int x, int y)
{
	if(map[x][y] == ' ')
	{
		map[x][y] = char(15);
		//down
		map[x+1][y] = char(31);
		//up
		map[x-1][y] = char(30);
		//// left
		//map[x][y-1] = char(17);
		//// rifht
		//map[x][y+1] = char(16);
	}
}
void XoaTrap(int x, int y)
{
	map[x][y] = ' ';
	//down
	map[x+1][y] = ' ';
	//up
	map[x-1][y] = ' ';
	//// left
	//map[x][y-1] = ' ';
	//// rifht
	//map[x][y+1] = ' ';
}
//bool Eat(int x, int y, int x1, int y1)
//{
//	if(map[x][y+2] == char(1))
//		return true;
//	return false;
//}
void InMap()
{
	gotoxy(20,2);
	SetBGColor(12);
	textcolor(14);
	cout<<"Score: "<<score;
	/*gotoxy(30,2);
	cout<<"Life: "*/
	int i,j;
	for(i=0;i<30;i++)
	{
		for(j=0;j<70;j++)
		{           /////----IN NEN
			if(map[i][j] == '_')
			{
				textcolor(51);
				cout<<map[i][j];
				textcolor(7);
			}//      in diem
			else if(map[i][j] == char(176))
			{
				SetBGColor(14);
				textcolor(11);
				cout<<map[i][j];
				textcolor(7);
				//SetBGColor(0);
			}//--- in 2 ben
			else if(map[i][j] == char(177))
			{
				//SetBGColor(14);
				textcolor(2);
				cout<<map[i][j];
				textcolor(7);
				//SetBGColor(0);
			}
			// in trap
			else if(map[i][j] == char(30) || map[i][j] == char(31))
			{
				textcolor(12);
				cout<<map[i][j];
				textcolor(7);
			}
			else if(map[i][j] == char(15))
			{
				textcolor(15);
				cout<<map[i][j];
				textcolor(7);
			}
			// in chuot
			else if(map[i][j] == char(1)|| map[i][j] == char(4))
			{
				textcolor(14);
				cout<<map[i][j];
				textcolor(7);
			}
			else
			{    
				textcolor(15);
				cout<<map[i][j];
				textcolor(7);
			}
		}
		cout<<"\n";
	}
}
void XoaDog(int x,int y)
{
	map[x][y] = ' ';
	map[x][y+1] = ' ';
	map[x][y-1] = ' ';
	/// ve dau
	map[x][y+2] = ' ';
	/// ve chan sau
	map[x+1][y-1] = ' ';
	map[x+1][y+1] = ' ';
	//ve duoi
	map[x][y-2] = ' ';
}
void Move(int &x, int &y)
{
	if(GetAsyncKeyState(VK_LEFT))
	{
		//limit left y = 2
		if(y > 2)
		{
			if(map[x][y] == char(1) || map[x][y+1]== char(1) || map[x][y-1]== char(1) || map[x][y+2]== char(1) || map[x+1][y+1]== char(1) || map[x+1][y-1]== char(1) || map[x][y-2]== char(1) )
			{
				/*XoaMouse(x,y);
				score++;*/
			}
			XoaDog(x,y);
			y--;
			VeDog(x,y);
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		// limit 69
		if(y <= 66)
		{
			if(map[x][y] == char(1) || map[x][y+1]== char(1) || map[x][y-1]== char(1) || map[x][y+2]== char(1) || map[x+1][y+1]== char(1) || map[x+1][y-1]== char(1) || map[x][y-2]== char(1) )
			{
				/*XoaMouse(x,y);
				score++;*/
			}
			XoaDog(x,y);
			y++;
			VeDog(x,y);
		}
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		// limit 1
		if(x > 2)
		{
			if(map[x][y] == char(1) || map[x][y+1]== char(1) || map[x][y-1]== char(1) || map[x][y+2]== char(1) || map[x+1][y+1]== char(1) || map[x+1][y-1]== char(1) || map[x][y-2]== char(1) )
			{
				/*XoaMouse(x,y);
				score++*/;
			}
			XoaDog(x,y);
			x--;
			VeDog(x,y);
		}
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		// limit 21
		if(x < 20)
		{
			if(map[x][y] == char(1) || map[x][y+1]== char(1) || map[x][y-1]== char(1) || map[x][y+2]== char(1) || map[x+1][y+1]== char(1) || map[x+1][y-1]== char(1) || map[x][y-2]== char(1) )
			{
				/*XoaMouse(x,y);
				score++;*/
			}
			XoaDog(x,y);
			x++;
			VeDog(x,y);
		}
	}
}
void EndGame(int score)
{
	XoaManHinh();
	gotoxy(30,7);
	cout<<" Game Over ";
	gotoxy(30,9);
	cout<<"Your Score : "<<score;
	gotoxy(20,11);
	cout<<' ';
	system("pause");
}
int main()
{
	resizeConsole(600,480);
	//	int a = 0;
	int x =11, y =9;
	int x1, y1 = 69; // chuot chay lung tung
	int x8,y8 = 69;
	int x2 = 5, y2 = 69; // chuot chay thang hang
	int x7 = 13, y7 = 69;
	int x3 = 3,y3 = 30;// trap tinh di dong
	int x5 = 3,y5 = 14;
	// trap tren tinh
	int x9 = 2,y9 = 35;
	int x4 = 21,y4 = 25; // trap duoi tinh
	int x6 = 21, y6 = 65;
	while(true)
	{

		VeMap1();

		//------------------------------
		srand(time(0));
		x1 = 2 + rand() % 19;
		x8 = 2 + rand() % 20;
		VeDog(x,y);
		VeTrap(x3,y3);
		VeTrap(x5,y5);
		VeTrap(x4,y4);
		VeTrap(x9,y9);
		VeTrap(x6,y6);
		VeMouse(x1,y1);
		VeMouse(x8,y8);
		VeMouse(x7,y7);
		VeMouse(x2,y2);
		XoaManHinh();
		InMap();
		Move(x,y);
		Sleep(0);

		// an thit chuot dong
		if(map[x1][y1] == char(2)) 
		{
			PlaySound("Ping.wav", NULL, SND_ASYNC);
			XoaMouse(x1,y1);
			score++;
			y1 = 69;
		}
		else
			y1--;
		if(y1 == 1)
		{
			y1 = 69;
			x1 = 2 + rand() % 66;
		}
		//-----------
		if(map[x8][y8] == char(2)) 
		{
			PlaySound("Ping.wav", NULL, SND_ASYNC);
			XoaMouse(x8,y8);
			score++;
			y8 = 69;
		}
		else
			y8--;
		if(y8 == 1)
		{
			y8 = 69;
			x8 = 2 + rand() % 66;
		}
		// an thit chuot tinh
		if(map[x2][y2] == char(2)) 
		{
			PlaySound("Ping.wav", NULL, SND_ASYNC);
			XoaMouse(x2,y2);
			score++;
			y2 = 69;
			x2 = 2 + rand() % 20;
		}
		else
			y2--;
		if(y2 == 1)
		{
			y2 = 69;
			x2 = 2 + rand() % 20;
		}
		//---------------
			if(map[x7][y7] == char(2)) 
		{
			PlaySound("Ping.wav", NULL, SND_ASYNC);
			XoaMouse(x7,y7);
			score++;
			y7 = 69;
			x7 = 2 + rand() % 20;
		}
		else
			y7--;
		if(y7 == 1)
		{
			y7 = 69;
			x7 = 2 + rand() % 20;
		}

		// di chuyen trap tren
		if(map[x3][y3] == char(2) || map[x3][y3] == char(219) || map[x3][y3] == '~') // dung vo dog
		{
			PlaySound("dog.wav", NULL, SND_ASYNC);
			EndGame(score);
		}
		else
			x3++;
		if(x3 == 21)
		{
			x3 = 3;
			y3 = 2 + rand() % 66;

		}
		//----
        if( map[x5][y5] == char(2) || map[x5][y5] == char(219) || map[x5][y5] == '~') // dung vo dog
		{
			PlaySound("dog.wav", NULL, SND_ASYNC);
						EndGame(score);

		}
		else
			x5++;
		if(x5 == 21)
		{
			x5 = 3;
			y5 = 2 + rand() % 66;

		}
//trap duoi co dinh 1
		if(map[x4][y4] == char(2) || map[x4][y4] == char(219) || map[x4][y4] == '~') // dung vo dog
		{
			PlaySound("dog.wav", NULL, SND_ASYNC);
						EndGame(score);

		}
		else
			x4--;
		if(x4 == 3)
		{
			x4 = 21;
			y4 = 14;

		}
		//trap duoi co dinh 
		if(map[x6][y6-1] == char(2) || map[x6][y6] == char(2) || map[x6][y6] == char(219) || map[x6][y6] == '~' || map[x6][y6+1] == '~') // dung vo dog
		{
			PlaySound("dog.wav", NULL, SND_ASYNC);
					EndGame(score);

		}
		else
			x6--;
		if(x6 == 3)
		{
			x6 = 21;
			y6 = 65;

		}
		// trap tren co dinh
		if(map[x9][y9-1] == char(2) || map[x9][y9] == char(2) || map[x9][y9] == char(219) || map[x9][y9] == '~' || map[x9][y9+1] == '~') // dung vo dog
		{
			PlaySound("dog.wav", NULL, SND_ASYNC);
					EndGame(score);

		}
		else
			x9++;
		if(x9 == 21)
		{
			x9 = 3;
			y9 = 35;

		}
		//system("pause");
		//return 0;
	}
}
