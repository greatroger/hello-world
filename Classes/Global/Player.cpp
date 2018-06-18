#include"Global/Player.h"
#include"Object/Bomb.h"
#include"Global/Global.h"
USING_NS_CC;

 std::map<std::string, Player*> Player::Players;
 std::string Player::local_Username="";
 Player* Player::local_player=NULL;


Player::Player(const std::string& name):m_name(name)
{
	m_speed = 0.16f;
	m_isdead = false;
	msg_bomb = Vec2(0, 0);
	msg_walk = 0;
	msg_dir = -1;
	msg_createprop_pos = Vec2(0, 0);
	msg_createprop_type = -1;
	msg_pickupProp = -1;
	msg_changeMode = -1;
	m_stopwatch = 0;
	msg_useProp = -1;
	m_life = 5;
	m_bombNum = 0;
	m_propType = -1;
	m_propNum = 0;
	m_maxBombNum = 2;
	m_bombWidth = 2;
	m_isunhurtable = false;
	isconnect = true;
	isgold = false;
	isinpop = false;
	msg_changeMap = -1;
	m_team = -1;
	m_bunType = 0;
}

Player::~Player()
{

}

void Player::setRoomID(int ID)
{
	m_roomID = ID;
}

void Player::setBunType(int type)
{
	assert(type <= 2);
	assert(type >= 0);
	m_bunType = type;
}

void Player ::setDirection(int dir)
{
	assert(dir <= 3 && dir>=0);
	m_dir =direction(dir);
}

void Player::setNumber(int number)
{
	m_number = number;

}

void Player::pickupProp(int type,int number)
{
	assert(number > 0);
	assert(type > -1);
	m_propType = type;
	m_propNum = number;
}

void Player::useProp()
{
	if (m_propNum == 0) return;
	--m_propNum;
	if (m_propNum == 0) m_propType = -1;
}


std::string Player::getName()
{
	return m_name;
}

Sprite* Player::getSprite()
{
	return m_sprite;
}

int Player::getRoomID()
{
	return m_roomID;
}

int Player::getBombWidth()
{
	return m_bombWidth;
}
cocos2d::Vec2 Player::getPostion()
{
	return m_sprite->getPosition();
}

float Player::getSpeed()
{
	return m_speed;
}

int Player::getPropType()
{
	return m_propType;
}

int Player::getNumber()
{
	return m_number;
}

int Player::getStopwatch()
{
	return m_stopwatch;
}

Vec2 Player::getDirection()
{
	if (m_dir == up) return Vec2(0, 1);
	if (m_dir == down) return Vec2(0, -1);
	if (m_dir == left) return Vec2(-1, 0);
	if (m_dir == right) return Vec2(1, 0);
}

int Player::getLife()
{
	return m_life;
}


Sprite* Player::createSprite()
{
    m_sprite = Sprite::create(Path::Player::getPicSprite(m_number,1));
	setDirection(down);
	m_sprite->setScale(1.1f);
	return m_sprite;
}

void Player::runAction(MyMap* map)
{
	if (msg_dir != -1)
	{
		setDirection(msg_dir);
		m_sprite->setTexture(Path::Player::getPicSprite(m_number, m_dir));
		msg_dir = -1;
	}

	if (msg_walk != 0)
	{
		Vec2 walk = getDirection()*msg_walk;
		auto moveBy = MoveBy::create(m_speed,walk);
		m_sprite->runAction(moveBy);
		msg_walk = 0;
	}

	if (msg_bomb != Vec2(0, 0))
	{
		auto bomb = Bomb::create();
		bomb->start(msg_bomb,this,map);
		map->addChild(bomb,1);
		msg_bomb = Vec2(0, 0);
	}
}

void Player::addStopwatch(int m)
{
	m_stopwatch += m;
}

void Player::addLife(const int& i)
{
	m_life = m_life + i;
}

constexpr float MAXSpeed = 0.12f;

void Player::addSpeed(const float& i)
{
	m_speed += i;
	if (m_speed < MAXSpeed) m_speed = MAXSpeed;
}

constexpr int MAXBombNum = 6;
void Player::addMaxBombNmu(const int& i)
{
	if (m_maxBombNum + i <= MAXBombNum)
		m_maxBombNum += i;
	else
		m_maxBombNum = MAXBombNum;
}

constexpr int MAXBombWidth = 6;
void Player::addBombWidth(const int& i)
{
	if (m_bombWidth + i <= MAXBombWidth)
		m_bombWidth += i;
	else
		m_bombWidth = MAXBombWidth;
}


void Player::addBombNum(const int& i)
{
	m_bombNum += i;
}

void Player::getDamageByBomb()
{
	if (isgold) return;
	if (isinpop) return;
	isinpop = true;
}


bool Player::isDead()
{
	return m_isdead;
}


bool Player::ifcanBomb()
{
	if (m_life <= 0) return false;
	if (m_maxBombNum <= m_bombNum)return false;
	if (isgold)return false;
	if (isinpop)return false;
	return true;
}
int Player::getBunType()
{
	return m_bunType;
}
bool Player::ifcanMove()
{
	if (m_life <= 0) return false;
	if (isgold) return false;
	if (isinpop) return false;
	return true;
}