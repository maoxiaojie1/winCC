#include "SmallSquare.h"

USING_NS_CC;

SmallSquare::SmallSquare() : _size(0, 0), _position(0, 0), _color(NULL)
{
    //_color = NULL;
    keyState.push_back(false);
	keyState.push_back(false);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SmallSquare::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SmallSquare::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

SmallSquare::~SmallSquare()
{

}

void SmallSquare::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        keyState[0] = true;
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        keyState[1] = true;
    }
}

void SmallSquare::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        keyState[0] = false;
    }

    if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        keyState[1] = false;
    }
}

SmallSquare* SmallSquare::createSmallSquare(const Size &size, const Vec2 &position)
{
    SmallSquare *sprite = new (std::nothrow) SmallSquare();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        sprite->initSmallSquare(size, position);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool SmallSquare::initSmallSquare(const Size &size, const Vec2 &position)
{
    _size = size;
    _position = position;
    _color = LayerColor::create(Color4B(238, 59, 59,255), size.width, size.height);
    _color->setPosition(position);
    this->addChild(_color);
    return true;
}

void SmallSquare::updatePosition(float dt)
{
    static bool flag = false;
	float y = 0;
    float x = 0;
	if (!flag)
	{
		y = this->getPosition().y - SQUARE_FALLING_SPEED * dt;
		//auto point = convertToWorldSpaceAR(Vec2(x, y));
		if (y < 25)
		{
			//point = convertToNodeSpaceAR(Vec2(0, 0));
			this->setPosition(this->getPosition().x, 25);
			//log("%f, %f\n", point.x, point.y);
			flag = true;
			return;
		}
		//SmallSquare* sprite0 = dynamic_cast<SmallSquare*>(sprite);
        x = this->getPosition().x;
        if (keyState[0])
        {
            x -= SQUARE_HORIZONTAL_SPEED * dt;
        }

        if (keyState[1])
        {
            x += SQUARE_HORIZONTAL_SPEED * dt;
        }

		this->setPosition(x, y);
	}	
}