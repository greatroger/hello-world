#pragma once
#include"Object/Map/MyMap.h"
#include"Global/Player.h"
#include"Global/Global.h"

namespace GameMap
{
	enum map {
		Village, Tomb, BunHouse
	};
	MyMap* create(int mapID);

	class Village :public MyMap
	{
	public:
		Village() {};
		~Village() {};
		MAP_CREATE_FUN(Village);
		bool init();
	};

	class Tomb :public MyMap
	{
	public:
		Tomb() {};
		~Tomb() {};
		MAP_CREATE_FUN(Tomb);
		bool init();
	};

	/*class  BunHouse :public MyMap
	{
	public:
		BunHouse() {};
		~BunHouse() {};
		MAP_CREATE_FUN(BunHouse);
	private:
		cocos2d::Vec2 m_bunpos[2];
		bool init();
		void bunCreate();
		void update(float det);
		void CheakEat();
		void loseBun(Player* player);
		int m_maxBunNum;
	};*/

}

