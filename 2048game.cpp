#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

const int row = 4;
const int col = 4;
const int gamecontinue = 1;
const int gamewin = 2;
const int gamelose = 3;
int game[5][5] = {0};

//绘制游戏界面
void map()
{
	system("cls");
	cout << "	2048Game			" << endl;
	cout << "	created by misty			" << endl;
	cout << endl;
	for (int i = 0; i < row; i++)
	{

		cout << "---------------------------------"<<endl;
		for (int j = 0; j < col+1; j++)
		{
			if (game[i][j] == 0)
				cout << "|   \t";
			else
				cout << "|   " << game[i][j] << "\t";

		}
		cout << endl;
	}
	cout << "---------------------------------" << endl;
}
//设置随机出现的数字
bool shownum()
{
	int i , j;
	int maxgrid = row * col;
	vector <int > emptygrid;
	int prob = rand() % 3;
	for (i = 0; i < row; i++)
	{
		for ( j = 0; j < col; j++)
		{
			if (game[i][j] == 0)
				emptygrid.push_back(i*4+j);
		}
	}
	
	//2/3概率出现2，1/3概率出现4
	if (emptygrid.empty() == true)
		return false;
	else
	{
		//从空格中随机选取一个空格
		int pos = rand() % emptygrid.size();
		int show = emptygrid[pos];
		if (prob == 0 || prob == 1)
			game[show/4][show%4] = 2;
		if(prob==2)
			game[show / 4][show % 4] = 4;

	}
	return true;
	
	
}

//判断输入输出
int Input()
{
	int up = 0, down = 0, left = 0, right = 0;
	int direction;

	while (true)
	{
		up=GetAsyncKeyState(VK_UP);
		down = GetAsyncKeyState(VK_DOWN);
		left = GetAsyncKeyState(VK_LEFT);
		right = GetAsyncKeyState(VK_RIGHT);

		if (up)
		{
			direction = 1;
			break;
		}
		if (down)
		{
			direction = 2;
			break;
		}
		if (left)
		{
			direction = 3;
			break;
		}
		if (right)
		{
			direction = 4;
			break;
		}
		
	}
	Sleep(100);
	return direction;
	

}

void move(int direction)
{
	switch (direction)
	{
		case 1:
			for (int i = 1; i < row; i++)
			{
				for (int t = i; t >= 1; t--)
				{
					for (int j = 0; j < col; j++)
					{
						if (game[t - 1][j] == 0)
						{
							game[t - 1][j] = game[t][j];
							game[t][j] = 0;
						}
						else if(game[t-1][j]==game[t][j])
						{
							game[t - 1][j] = game[t - 1][j] * 2;
							game[t][j] = 0;
						}
					}
				}
				
			};
			break;
		case 2:
			for (int i = row - 2; i >= 0; i--)
			{
				for (int t = i; t <row-1; t++)
				{
					for (int j = 0; j < col; j++)
					{
						if (game[t + 1][j] == 0)
						{
							game[t + 1][j] = game[t][j];
							game[t][j] = 0;
						}
						else if (game[t+1][j]==game[t][j])
						{
							game[t + 1][j] = game[t + 1][j] * 2;
							game[t][j] = 0;
						}
					}
				}
			};
				
			 break;
		case 3:
			for (int j = 1; j < col; j++)
			{
				for (int t = j; t >= 1; t--)
				{
					for (int i = 0; i < row; i++)
					{
						if (game[i][t - 1] == 0)
						{
							game[i][t - 1] = game[i][t];
							game[i][t] = 0;
						}
						else if (game[i][t - 1] == game[i][t])
						{
							game[i][t - 1] = game[i][t - 1] * 2;
							game[i][t] = 0;

						}
					}
				}

			};
			 break;
		case 4:
			for (int j = col - 2; j >= 0; j--)
			{
				for (int t = j; t < col - 1; t++)
				{
					for (int i = 0; i < row; i++)
					{
						if (game[i][t + 1] == 0)
						{
							game[i][t + 1] = game[i][t];
							game[i][t] = 0;
						}
						else if (game[i][t + 1] == game[i][t])
						{
							game[i][t + 1] = game[i][t + 1] * 2;
							game[i][t] = 0;
						}

					}
				}

			};
			break;
	}
		


}
//判断游戏状态
int judge()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (game[i][j] == 2048)
				return gamewin;
		}
	}

	//检查
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col-1; j++)
		{
			if ((game[i][j] == game[i][j + 1]) || !game[i][j])
			{
				return gamecontinue;
				break;
			}
			
		}
	}

	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row-1; i++)
		{
			if (!game[i][j] || (game[i][j] == game[i + 1][j]))
			{
				return gamecontinue;
				break;
			}
		}
	}

	return gamelose;
}


int main()
{	
	//srand((unsigned int)time(0));
	shownum();
	shownum();
	map();
	int direction = -1;
	int gamestate = -1;
	while (true)
	{
		direction = Input();
		gamestate = judge();
		if (direction && gamestate == gamecontinue)
		{
			move(direction);
			shownum();
			map();
			Sleep(100);
		}
		else if (gamestate == gamewin)
		{
			map();
			MessageBox(NULL, TEXT("游戏胜利！"), TEXT("游戏结束"), MB_OK);
			break;
		}
		else if (gamestate == gamelose)
		{
			map();
			MessageBox(NULL, TEXT("游戏失败！"), TEXT("游戏结束"), MB_OK);
			break;
		}

		

	}
	
	return 0;
}