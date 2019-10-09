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

Square * Square::creatSquare(const cocos2d::Size & size, const cocos2d::Vec2 & position, const cocos2d::Color4B color)
{
	Square *square= new (std::nothrow) Square();
	if (square && square->init())
	{
		square->autorelease();
		square->initSquare(size, position, color);
		return square;
	}
	CC_SAFE_DELETE(square);
	return nullptr;
}

void Square::initSquare(const cocos2d::Size & size, const cocos2d::Vec2 & position, const cocos2d::Color4B & color)
{
	auto layerColor = LayerColor::create(color, size.width, size.height);
	this->setContentSize(size);
	this->addChild(layerColor, 0);
	this->setPosition(position);
}

ComposeSquare* ComposeSquare::createComposeSquare(const cocos2d::Vec2 & position, std::function<void(Square *node[], int num)>& fun)
{
	ComposeSquare *square = new (std::nothrow) ComposeSquare();
	if (square && square->init())
	{
		square->autorelease();
		square->initComposeSquare(position, fun);
		return square;
	}
	CC_SAFE_DELETE(square);
	return nullptr;
}

void ComposeSquare::initComposeSquare(const cocos2d::Vec2 & position, std::function<void(Square *node[], int num)>& fun)
{
	for (int i = 0; i < 4; i++)
	{
		square[i] = Square::creatSquare(defaultSquareSize, Vec2::ZERO);
		if (i == 0)
		{
			auto squareBody = PhysicsBody::createBox(square[i]->getContentSize(), PhysicsMaterial(0.5, 0.1, 0.1));
			square[i]->setPhysicsBody(squareBody);
		}
	}
	fun(square, 4);
	for (int i = 0; i < 4; i++)
	{
		this->addChild(square[i]);
	}
	this->setPosition(position);
}

ShapeFactory* ShapeFactory::creatShapeFactory()
{
	ShapeFactory *shapeFactory = new (std::nothrow) ShapeFactory();
	if (shapeFactory)
	{
		shapeFactory->autorelease();
		return shapeFactory;
	}
	CC_SAFE_DELETE(shapeFactory);
	return nullptr;
}

ComposeSquare * ShapeFactory::createProduct(const cocos2d::Vec2 & position, BlockType type)
{
	std::function<void(Square *node[], int num)> fun;
	switch (type)
	{
	case BlockType::PENCIL:
		fun = [](Square *node[], int num) 
		{
			assert(num == 4);
			for (int i = 0; i < 4; i++)
			{
				node[i]->setPosition(Vec2(defaultSquareSize.width / 2, defaultSquareSize.height / 2 + defaultSquareSize.height * i));
			}
		}; break;
	case BlockType::LEFT_L:
		fun = [](Square *node[], int num) {}; break;
	case BlockType::RIGHT_L:
		fun = [](Square *node[], int num) {}; break;
	case BlockType::LEFT_Z:
		fun = [](Square *node[], int num) {}; break;
	case BlockType::RIGHT_Z:
		fun = [](Square *node[], int num) {}; break;
	case BlockType::T_SHAPE:
		fun = [](Square *node[], int num) {}; break;
	case BlockType::SQUARE:
		fun = [](Square *node[], int num) {}; break;
	default:
		fun = nullptr;
	}
	return 	ComposeSquare::createComposeSquare(position, fun);
}
