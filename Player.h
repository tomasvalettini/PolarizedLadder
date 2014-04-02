#ifndef PLAYER_H
#define PLAYER_H

class Player
{
	public:
		virtual bool move();
		virtual bool isaComputer();

	protected:
		int token;
		bool isComputer;
};


#endif