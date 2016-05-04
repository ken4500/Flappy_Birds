//
//  Character.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/19.
//
//

#ifndef __Flappy_Birds__Character__
#define __Flappy_Birds__Character__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class Character : public cocos2d::Node {
public:
    CREATE_FUNC(Character);
    bool init() override;
    void onEnter() override;
    void update(float dt) override;
    void jump();
    void startMove();
    void stopMove();
    void startHover();
    float getRadius();
    cocos2d::AABB getAABB();

protected:
    cocostudio::timeline::ActionTimeline* timeline;
    cocos2d::Vec2 velocity;
    cocos2d::Vec2 acceleration;
    float lastJumpTime;
    bool move;
};

#endif /* defined(__Flappy_Birds__Character__) */
