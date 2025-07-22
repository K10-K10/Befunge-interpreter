#include <iostream>
#include <string>
#include <stack>

int main()
{
	std::stack<int> sk;
	char code[25][80];
	int ptr_x = 0, ptr_y = 0;
	bool flag_done = false, skip = false;
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
		if (!skip)
		{
			char c = code[ptr_x][ptr_y];
			switch (c)
			{
			case '>':
				a = RIGHT;
				break;
			case '<':
				a = LEFT;
				break;
			case 'v':
				a = DOWN;
				break;
			case '^':
				a = UP;
				break;

			case '_':
				if (!sk.empty())
				{
					if (sk.top() == 0)
						a = RIGHT;
					else
						a = LEFT;
					sk.pop();
				}
				break;

			case '|':
				if (!sk.empty())
				{
					if (sk.top() == 0)
						a = DOWN;
					else
						a = UP;
					sk.pop();
				}
				break;

			case '#':
				skip = true;
				break;

			case '@':
				return 0;

			default:
				break;
			}
		}

		// 移動処理
		if (a == UP)
			ptr_x = (ptr_x + 24) % 25;
		else if (a == DOWN)
			ptr_x = (ptr_x + 1) % 25;
		else if (a == RIGHT)
			ptr_y = (ptr_y + 1) % 80;
		else if (a == LEFT)
			ptr_y = (ptr_y + 79) % 80;

		if (skip)
			skip = false;
	}
}
