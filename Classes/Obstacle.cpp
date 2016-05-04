//
//  Obstacle.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/21.
//
//

#include "Obstacle.h"
#include "Util.hpp"
using namespace cocos2d;

bool Obstacle::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = CSLoader::createTimeline("Obstacle.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    return true;
}

std::vector<AABB> Obstacle::getAABBs()
{
    std::vector<AABB> AABBs;
    auto pipeDown = getChildByName<Sprite*>("pipeDown");
    auto pipeUp   = getChildByName<Sprite*>("pipeUp");
    Vec2 pipeDownMin = getPosition() + pipeDown->getPosition();
    Vec2 pipeDownMax = getPosition() + pipeDown->getPosition() + pipeDown->getContentSize();
    Vec2 pipeUpMin   = getPosition() + pipeUp->getPosition() - Vec2(0,pipeUp->getContentSize().height);
    Vec2 pipeUpMax   = getPosition() + pipeUp->getPosition() + Vec2(pipeUp->getContentSize().width, 0);
    AABB pipeDownAABB = AABB(Util::toVec3(pipeDownMin), Util::toVec3(pipeDownMax));
    AABB pipeUpAABB   = AABB(Util::toVec3(pipeUpMin), Util::toVec3(pipeUpMax));
    AABBs.push_back(pipeDownAABB);
    AABBs.push_back(pipeUpAABB);
    return AABBs;
}
