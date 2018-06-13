#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x, y, Fx, Fy, score, Tx[100], Ty[100], Tlen=1;
enum eDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDir dir;
char name[100];
class Score
{
    char Name[100];
    int score;
public:
    Score()
    {
        Name[0]=' ';
        score=0;
    }
    Score(char name[100],int scr)
    {
        strcpy(Name,name);
        score=scr;
    }
    void Display()
    {
        cout<<Name<<":"<<score<<endl;
    }
};
void Setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	score = 0;
	Fx = rand() % (width-1)+1;
	Fy = rand() % (height-1)+1;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (i == 0 || i == width - 1)
				cout << "#";
			else if (i == x && j == y)
				cout << "O";
			else if (i == Fx && j == Fy)
				cout << "@";
			else
			{
				bool print = false;
				for (int k = 0; k < Tlen; k++)
				{
					if (Tx[k] == i && Ty[k] == j)
					{
						cout << "o";
						print = true;
					}
				}
				if(!print)
				cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "SCORE: " << score << endl << endl;
	Score s;
ifstream fout("Score.dat",ios::binary);
while(!fout.eof() && fout.read((char *)&s,sizeof(s)))
     {
      s.Display();
     }
fout.close();


}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP; break;
		case 's':
			dir = DOWN; break;
		case 'a':
			dir = LEFT; break;
		case 'd':
			dir = RIGHT; break;
		case 'x':
			gameover = true; break;
		}
	}

}


void Logic()
{
	int prevX = Tx[0];
	int prevY = Ty[0];
	int prev2X, prev2y;
	for (int i = 1; i < Tlen; i++)
	{
		prev2X = Tx[i];
		prev2y = Ty[i];
		Tx[i] = prevX;
		Ty[i] = prevY;
		prevX = prev2X;
		prevY = prev2y;
		Tx[0] = x;
		Ty[0] = y;

	}
	switch (dir)
	{
	case LEFT:
		x--; break;
	case RIGHT:
		x++; break;
	case UP:
		y--; break;
	case DOWN:
		y++; break;
	}
	if (x > width || x < 0 || y>height || y < 0)
		gameover = true;
	if (x == Fx && y == Fy)
	{
		score++;
		Fx = (rand() % (width-2))+1;
		Fy = (rand() % (height-2))+1;
		Tlen++;
	}
}

void Write_score(Score s)
{
ofstream fout("Score.dat",ios::binary|ios::app);
fout.write((char *)&s,sizeof(s));
fout.close();
}
int main()
{
	Setup();
	while (!gameover)
	{
		Draw();
		Input();
		Logic();
		Sleep(20);
	}
	if(score!=0)
    {
    cout<<"Enter your Name: ";
	cin>>name;
	Score s(name,score);
	Write_score(s);
    }

	return 0;
}
