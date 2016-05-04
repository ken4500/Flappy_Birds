//
//  Ground.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/20.
//
//

#include "Ground.h"
using namespace cocos2d;

bool Ground::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = CSLoader::createTimeline("Ground.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    return true;
}

void Ground::onEnter()
{
    Node::onEnter();
    grounds.pushBack(this->getChildByName<Sprite*>("ground1"));
    grounds.pushBack(this->getChildByName<Sprite*>("ground2"));
}


void Ground::moveLeft(float distance)
{
    for (auto ground : this->grounds) {
        ground->setPositionX(ground->getPositionX() - distance);
        if (ground->getPositionX() <= 0.0f) {
            ground->setPositionX(ground->getPositionX() + ground->getContentSize().width * 2);
        }
    }
}
