#include "SmallSquare.h"

USING_NS_CC;

SmallSquare::SmallSquare() : _size(0, 0), _position(0, 0), _color(NULL)
{
    //_color = NULL;
}
SmallSquare::~SmallSquare()
{

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