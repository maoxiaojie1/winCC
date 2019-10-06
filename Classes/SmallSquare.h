#ifndef __SmallSquare_2019_10_3_13_55_H__
#define __SmallSquare_2019_10_3_13_55_H__

#include "cocos2d.h"
#include <vector>

#define SQUARE_FALLING_SPEED      100
#define SQUARE_HORIZONTAL_SPEED   50

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
