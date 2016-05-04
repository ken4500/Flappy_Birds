//
//  Character.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/19.
//
//

#include "Character.hpp"
#include "Util.hpp"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
using namespace cocos2d;

bool Character::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    this->move = false;
    this->velocity = Vec2::ZERO;
    this->acceleration = Vec2(0, -1000);

    return true;
}

void Character::onEnter()
{
    Node::onEnter();
    this->scheduleUpdate();
}

void Character::update(float dt)
{
    if (this->move == false) {
        return;
    }

    if (this->velocity.y < 0) {
        this->velocity = this->velocity + 2 * this->acceleration * dt;
    } else {
        this->velocity = this->velocity + this->acceleration * dt;
    }
 
    lastJumpTime += dt;
    if (lastJumpTime > 0.5f) {
        float rotation = getRotation();
        rotation += 360 * dt;
        rotation = MIN(90, rotation);
        setRotation(rotation);
    }

    this->setPosition(this->getPosition() + this->velocity * dt);    
}

void Character::jump()
{
    this->velocity = Vec2(0, 350);
    this->lastJumpTime = 0;
    setRotation(-20);
    this->stopAllActions();
    runAction(this->timeline);
    this->timeline->setTimeSpeed(1.0f);
    this->timeline->play("fly", false);
    AudioEngine::play2d("Assets/sounds/sfx_wing.mp3", false, 1.0f);
}

void Character::startMove()
{
    this->move = true;
}

void Character::stopMove()
{
    this->move = false;
}


void Character::startHover()
{
    this->stopAllActions();
    runAction(this->timeline);
    this->timeline->play("fly", true);
    this->timeline->setTimeSpeed(0.5f);
    this->setRotation(0);
    Vec2 moveDistance = Vec2(0, 10.0f);
    auto up   = EaseInOut::create(MoveBy::create(0.35f, moveDistance), 2);
    auto down = EaseInOut::create(MoveBy::create(0.35f, -moveDistance), 2);
    this->runAction(RepeatForever::create(Sequence::create(up, down, NULL)));
}


float Character::getRadius()
{
    return this->getChildByName<Sprite*>("bird")->getContentSize().height / 2;
}

AABB Character::getAABB()
{
    auto birdImage = getChildByName<Sprite*>("bird");
    Vec2 characterMin = getPosition() - birdImage->getContentSize() * 0.8f / 2;
    Vec2 characterMax = getPosition() + birdImage->getContentSize() * 0.8f / 2;
    AABB charaAABB = AABB(Util::toVec3(characterMin), Util::toVec3(characterMax));
    return charaAABB;
}
