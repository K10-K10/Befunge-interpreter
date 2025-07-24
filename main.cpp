#include <iostream>
#include <string>
#include <stack>

int main()
{
	std::stack<int> sk;
	char code[25][80];
	int ptr_x = 0, ptr_y = 0;
	int x = 0, y = 0, z = 0;
	char input_char, code_char;
	int input_int;
	bool flag_done = false, skip = false, quote = false;
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
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			std::cout << code[i][j];
		}
		std::cout << std::endl;
	}
	while (true)
	{
		if (!skip)
		{
			if (!quote)
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
				case '&':
					std::cin >> input_int;
					sk.push(input_int);
					break;
				case '~':
					sk.push(int(input_char));
					break;
				case '.':
					std::cout << sk.top() << " ";
					sk.pop();
					break;
				case ',':
					std::cout << char(sk.top());
					sk.pop();
					break;
				case '+':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(x + y);
					break;
				case '-':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(y - x);
					break;
				case '/':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(y / x);
					break;
				case '*':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(y * x);
					break;
				case '%':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(y % x);
					break;
				case '`':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(y > x ? 1 : 0);
					break;
				case '!':
					x = sk.top();
					sk.pop();
					sk.push(x == 0 ? 1 : 0);
					break;
				case ':':
					x = sk.top();
					sk.push(x);
					break;
				case '\\':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					sk.push(x);
					sk.push(y);
					break;
				case '$':
					sk.pop();
					break;
				case 'g':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					code_char = code[x][y];
					sk.push(int(code_char));
					break;
				case 'p':
					x = sk.top();
					sk.pop();
					y = sk.top();
					sk.pop();
					z = sk.top();
					sk.pop();
					code[x][y] = char(z);
					break;
				case '1':
					sk.push(1);
					break;
				case '2':
					sk.push(2);
					break;
				case '3':
					sk.push(3);
					break;
				case '4':
					sk.push(4);
					break;
				case '5':
					sk.push(5);
					break;
				case '6':
					sk.push(6);
					break;
				case '7':
					sk.push(7);
					break;
				case '8':
					sk.push(8);
					break;
				case '9':
					sk.push(9);
					break;
				default:
					break;
				}
			}
			if (quote)
			{
				char c = code[ptr_x][ptr_y];
				if (c == '"')
				{
					quote = false;
				}
				else
				{
					sk.push(int(c));
				}
			}
		}

		if (a == UP)
			ptr_x = (ptr_x + 24) % 25;
		else if (a == DOWN)
			ptr_x = (ptr_x + 1) % 25;
		else if (a == RIGHT)
			ptr_y = (ptr_y + 1) % 80;
		else if (a == LEFT)
			ptr_y = (ptr_y + 79) % 80;
		std::cout << ptr_x << " " << ptr_y << std::endl;
		if (skip)
			skip = false;
	}
	return 0;
}
