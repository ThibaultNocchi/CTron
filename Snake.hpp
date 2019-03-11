#pragma once

class Snake{
	public:
		Snake(int length=5);
	private:
		vector<pair<char,char>> body;
};

enum directions {
	UP, DOWN, LEFT, RIGHT
};
