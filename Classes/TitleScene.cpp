//
//  TitleScene.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/23.
//
//

#include "TitleScene.h"
#include "CharacterReader.hpp"
#include "GroundReader.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Config.h"
#include "Ground.h"
#include "Character.hpp"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace cocostudio::timeline;

#pragma mark - Public methods

#pragma mark Initializer

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("GroundReader", (ObjectFactory::Instance) GroundReader::getInstance);
    auto rootNode = CSLoader::createNode("TitleScene.csb");
    
    auto back = rootNode->getChildByName("back");
    this->ground = back->getChildByName<Ground*>("ground");
    this->character = back->getChildByName<Character*>("character");
    this->character->startHover();
    
    auto playButton = rootNode->getChildByName<ui::Button*>("playButton");
    playButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::pushPlayButton, this));

    addChild(rootNode);

    return true;
}

void TitleScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}

void TitleScene::update(float dt)
{
    float moveDistance = dt * STAGE_MOVE_SPEED;
    this->ground->moveLeft(moveDistance);
}

#pragma mark - Private methods

void TitleScene::pushPlayButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    auto button = dynamic_cast<ui::Button*>(pSender);
    if (type == ui::Widget::TouchEventType::BEGAN) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, -4)));
    } else if (type == ui::Widget::TouchEventType::ENDED) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, 4)));
        goGameScene();
    } else if (type == ui::Widget::TouchEventType::CANCELED) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, 4)));
    }
}

void TitleScene::goGameScene()
{
    experimental::AudioEngine::play2d("Assets/sounds/sfx_swooshing.mp3", false, 1.0f);
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.8f, scene, Color3B(0, 0, 0)));
}