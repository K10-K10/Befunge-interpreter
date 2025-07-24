#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " file.bef" << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		std::cerr << "Cannot open file: " << argv[1] << std::endl;
		return 1;
	}

	const int y_max = 80;
	std::vector<std::string> code;
	std::string line;
	while (std::getline(file, line))
	{
		while (line.length() < y_max)
			line += ' ';
		code.push_back(line);
	}
	int x_max = code.size();

	std::stack<int> sk;
	int ptr_x = 0, ptr_y = 0;
	int x = 0, y = 0, z = 0;
	char input_char, code_char;
	int input_int;
	bool skip = false, quote = false;

	enum Direction
	{
		UP,
		RIGHT,
		LEFT,
		DOWN
	};
	Direction a = RIGHT;
	while (true)
	{
		char c = code[ptr_x][ptr_y];
		if (quote)
		{
			if (c == '"')
			{
				quote = false;
			}
			else
			{
				sk.push(int(c));
			}
		}
		else if (!skip)
		{
			switch (c)
			{
			case '>':
				a = RIGHT;
				break;
			case '<':
				a = LEFT;
				break;
			case '^':
				a = UP;
				break;
			case 'v':
				a = DOWN;
				break;
			case '_':
				if (!sk.empty())
				{
					a = (sk.top() == 0) ? RIGHT : LEFT;
					sk.pop();
				}
				break;
			case '|':
				if (!sk.empty())
				{
					a = (sk.top() == 0) ? DOWN : UP;
					sk.pop();
				}
				break;
			case '#':
				skip = true;
				break;
			case '@':
				return 0;
			case '"':
				quote = true;
				break;
			case '&':
				std::cin >> input_int;
				sk.push(input_int);
				break;
			case '~':
				std::cin >> input_char;
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
			case '-':
			case '*':
			case '/':
			case '%':
			case '`':
			{
				x = sk.top();
				sk.pop();
				y = sk.top();
				sk.pop();
				switch (c)
				{
				case '+':
					sk.push(y + x);
					break;
				case '-':
					sk.push(y - x);
					break;
				case '*':
					sk.push(y * x);
					break;
				case '/':
					sk.push(x == 0 ? 0 : y / x);
					break;
				case '%':
					sk.push(x == 0 ? 0 : y % x);
					break;
				case '`':
					sk.push(y > x ? 1 : 0);
					break;
				}
				break;
			}
			case '!':
				x = sk.top();
				sk.pop();
				sk.push(x == 0 ? 1 : 0);
				break;
			case ':':
				if (!sk.empty())
					sk.push(sk.top());
				break;
			case '\\':
				x = sk.top();
				sk.pop();
				y = sk.empty() ? 0 : sk.top();
				if (!sk.empty())
					sk.pop();
				sk.push(x);
				sk.push(y);
				break;
			case '$':
				if (!sk.empty())
					sk.pop();
				break;
			case 'g':
				x = sk.top();
				sk.pop();
				y = sk.top();
				sk.pop();
				if (x >= 0 && x < x_max && y >= 0 && y < y_max)
					sk.push(code[x][y]);
				else
					sk.push(0);
				break;
			case 'p':
				x = sk.top();
				sk.pop();
				y = sk.top();
				sk.pop();
				z = sk.top();
				sk.pop();
				if (x >= 0 && x < x_max && y >= 0 && y < y_max)
					code[x][y] = char(z);
				break;
			default:
				if (c >= '0' && c <= '9')
					sk.push(c - '0');
				break;
			}
		}

		switch (a)
		{
		case UP:
			ptr_x = (ptr_x + x_max - 1) % x_max;
			break;
		case DOWN:
			ptr_x = (ptr_x + 1) % x_max;
			break;
		case RIGHT:
			ptr_y = (ptr_y + 1) % y_max;
			break;
		case LEFT:
			ptr_y = (ptr_y + y_max - 1) % y_max;
			break;
		}

		if (skip)
			skip = false;
	}
}
