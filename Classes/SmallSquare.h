#ifndef __SmallSquare_2019_10_3_13_55_H__
#define __SmallSquare_2019_10_3_13_55_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include <string>
#include "ParamDef.h"

static const cocos2d::Color4B defaultColorValue = cocos2d::Color4B(255, 0, 255, 255);
static const cocos2d::Size defaultSquareSize = cocos2d::Size(EACH_SQUARE_EDGE_LEN, EACH_SQUARE_EDGE_LEN);

class Square : public cocos2d::Node
{
public:
	Square() {};
	static Square* creatSquare(const cocos2d::Size &size, const cocos2d::Vec2 &position, const cocos2d::Color4B color = defaultColorValue);
	void initSquare(const cocos2d::Size &size, const cocos2d::Vec2 &position, const cocos2d::Color4B &color);

private:
	CC_DISALLOW_COPY_AND_ASSIGN(Square);
};

class ComposeSquare : public cocos2d::Sprite
{
public:
	ComposeSquare(){};
	static ComposeSquare* createComposeSquare(const cocos2d::Vec2 &position, std::function<void(Square *node[], int num)> &fun);
	void initComposeSquare(const cocos2d::Vec2 & position, std::function<void(Square *node[], int num)>& fun);
private:
	CC_DISALLOW_COPY_AND_ASSIGN(ComposeSquare);
	Square * square[4];
};

class ShapeFactory : public cocos2d::Ref
{
public:
	ShapeFactory() {};
	static ShapeFactory * creatShapeFactory();
	ComposeSquare* createProduct(const cocos2d::Vec2 & position, BlockType type);

private:
	CC_DISALLOW_COPY_AND_ASSIGN(ShapeFactory);
};

class SmallSquare : public cocos2d::Sprite
{
public:
    SmallSquare();
    static SmallSquare* createSmallSquare(const cocos2d::Size &size, const cocos2d::Vec2 &position);
    virtual ~SmallSquare();
    bool initSmallSquare(const cocos2d::Size &size, const cocos2d::Vec2 &position);
    CREATE_FUNC(SmallSquare);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    std::vector<bool> getKeyState()
    {
        return keyState;
    }
    void updatePosition(float dt);
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(SmallSquare);
    cocos2d::Size _size;
    cocos2d::Vec2 _position;
    cocos2d::LayerColor *_color;
    std::vector<bool> keyState;
};

#endif
