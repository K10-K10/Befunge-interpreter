#include <iostream>
#include <string>
#include <stack>

int main()
{
	std::stack<int> sk;
	char code[25][80];
	int ptr_x = 0, ptr_y = 0;
	bool flag_done = false;
	enum Direction
	{
		UP,
		RIGHT,
		LEFT,
		DOWN
	};
	Direction a = RIGHT;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			std::cin >> code[i][j];
		}
	}
	while (true)
	{
		if (a == UP)
		{
			if (ptr_x == 0)
				ptr_x = 24;
			else
				ptr_x--;
		}
		else if (a == DOWN)
		{
			if (ptr_x == 24)
				ptr_x = 0;
			else
				ptr_x++;
		}
		else if (a == RIGHT)
		{
			if (ptr_y == 79)
				ptr_y = 0;
			else
				ptr_y++;
		}
		else if (DOWN)
			char c = code[ptr_x][ptr_y];
		switch (c)
		{
		case '>':
			a = RIGHT;
			break;
		case '<':
			a = LEFT;
			if (ptr_y == 0)
				ptr_y = 79;
			else
				ptr_y--;
			break;
		case 'v':
			a = DOWN;
			break;
		case '^':
			a = UP;
			break;
		case '_':
			if (sk.top() == 0)
			{
				sk.pop();
			}
		}
	}
}
