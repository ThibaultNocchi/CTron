#pragma once

class Snake{
	public:
		Snake(int length=5);
		void move(int direction);
	private:
		vector<pair<char,char>> body;
};

