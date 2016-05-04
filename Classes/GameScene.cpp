#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "CharacterReader.hpp"
#include "Character.hpp"
#include "GroundReader.h"
#include "Ground.h"
#include "ObstacleReader.h"
#include "Config.h"
#include "Util.hpp"
#include "audio/include/AudioEngine.h"
#include "UserData.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("GroundReader", (ObjectFactory::Instance) GroundReader::getInstance);
    instance->registReaderObject("ObstacleReader", (ObjectFactory::Instance) ObstacleReader::getInstance);
    auto rootNode = CSLoader::createNode("GameScene.csb");

    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    this->tutorial = rootNode->getChildByName("tutorial");
    this->back = rootNode->getChildByName<Sprite*>("back");
    this->character = back->getChildByName<Character*>("character");
    this->character->setLocalZOrder(1);
    this->ground = back->getChildByName<Ground*>("ground");
    this->scoreLabel = rootNode->getChildByName<cocos2d::ui::TextBMFont*>("scoreLabel");
    this->ground->setLocalZOrder(2);
    this->stagePosition = 0;
    this->lastObstaclePosition = 0;
    this->timeline = CSLoader::createTimeline("GameScene.csb");
    this->timeline->retain();
    this->characterStartPosition = this->character->getPosition();
    auto scoreBoard = rootNode->getChildByName("scoreBoard");
    this->boardScoreLabel = scoreBoard->getChildByName<ui::TextBMFont*>("boardScoreLabel");
    this->boardHighScoreLabel = scoreBoard->getChildByName<ui::TextBMFont*>("boardHighScoreLabel");
    this->newImage = scoreBoard->getChildByName<Sprite*>("new");
    this->medalNode = scoreBoard->getChildByName("medalNode");
    this->playButton = rootNode->getChildByName<cocos2d::ui::Button*>("playButton");
    this->leaderboardButton = rootNode->getChildByName<cocos2d::ui::Button*>("leaderboardButton");
    this->playButton->addTouchEventListener(CC_CALLBACK_2(GameScene::pushPlayButton, this));
    this->leaderboardButton->addTouchEventListener(CC_CALLBACK_2(GameScene::pushLeaderboardButton, this));
    this->userData = UserData::load();
    
    triggerReady();

    addChild(rootNode);

    return true;
}


void GameScene::onEnter()
{
    Layer::onEnter();

    this->setupTouchHandling();
    this->scheduleUpdate();
}

void GameScene::update(float dt)
{
    switch (this->gameState) {
    case GameState::Ready:
        updateReady(dt);
        break;
    case GameState::Playing:
        updatePlaying(dt);
        break;
    case GameState::GameOver:
        updateGameOver(dt);
        break;
    default:
        break;
    }
}

void GameScene::updateReady(float dt)
{
    // 床の移動
    float moveDistance = dt * STAGE_MOVE_SPEED;
    this->ground->moveLeft(moveDistance);
    
    // 障害物の移動
    for (auto obstacle : this->obstacles) {
        obstacle->setPositionX(obstacle->getPositionX() - moveDistance);
    }
}

void GameScene::updatePlaying(float dt)
{
    // 床の移動
    float moveDistance = dt * STAGE_MOVE_SPEED;
    this->ground->moveLeft(moveDistance);
    this->stagePosition += moveDistance;
    
    // 障害物の移動
    for (auto obstacle : this->obstacles) {
        obstacle->setPositionX(obstacle->getPositionX() - moveDistance);
    }

    // 障害物の発生
    if (this->stagePosition - moveDistance < this->lastObstaclePosition + OBSTACLE_SPAN
    && this->lastObstaclePosition + OBSTACLE_SPAN <= this->stagePosition) {
        spawnObstacle();
        this->lastObstaclePosition = this->stagePosition;
    }

    // 床との判定
    float bottomY = this->character->getPosition().y - this->character->getRadius();
    float groundY = this->ground->getPosition().y;
    if (bottomY <= groundY) {
        experimental::AudioEngine::play2d("Assets/sounds/sfx_hit.mp3", false, 1.0f);
        this->character->setPositionY(groundY + this->character->getRadius());
        triggerGameOver();
    }
    
    // 障害物との衝突判定saz
    for (auto obstacle : this->obstacles) {
        bool isHit = isHitCharacter(obstacle);
        if (isHit) {
            experimental::AudioEngine::play2d("Assets/sounds/sfx_hit.mp3", false, 1.0f);
            this->character->runAction(Sequence::create(
                DelayTime::create(0.2f), CallFunc::create([]{
                experimental::AudioEngine::play2d("Assets/sounds/sfx_die.mp3", false, 1.0f);
            }), NULL));
            triggerGameOver();
        }
    }
    
    // 画面外の障害物の削除
    if (obstacles.empty() == false && obstacles.front()->getPositionX() < -100) {
        obstacles.front()->removeFromParent();
        obstacles.erase(obstacles.begin());
    }
    
    // スコアの計算
    for (auto obstacle : this->obstacles) {
        float obstacleX = obstacle->getPositionX();
        float characterX = this->character->getPositionX();
        if (characterX - moveDistance < obstacleX && characterX >= obstacleX) {
            this->setScore(this->score + 1);
            experimental::AudioEngine::play2d("Assets/sounds/sfx_point.mp3", false, 1.0f);
        }
    }

}

void GameScene::updateGameOver(float dt)
{
    // 床との判定
    float bottomY = this->character->getPosition().y - this->character->getRadius();
    float groundY = this->ground->getPosition().y;
    if (bottomY <= groundY) {
        this->character->setPositionY(groundY + this->character->getRadius());
        this->character->stopMove();
    }
}


void GameScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        switch (this->gameState) {
        case GameState::Ready:
            this->triggerPlaying();
            this->character->jump();
            break;
        case GameState::Playing:
            this->character->jump();
            break;
        case GameState::GameOver:
            break;
        case GameState::WaitNextGame:
            break;
        }
        return true;
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::triggerReady()
{
    this->gameState = GameState::Ready;
    this->character->setPosition(this->characterStartPosition);
    this->character->startHover();
    this->tutorial->setOpacity(255);
    this->setScore(0);
    this->stopAllActions();
    this->runAction(this->timeline);
    timeline->play("default", false);
}

void GameScene::triggerPlaying()
{
    this->gameState = GameState::Playing;
    this->character->startMove();
    this->tutorial->runAction(FadeOut::create(0.8f));
}

void GameScene::triggerGameOver()
{
    this->highScore = this->userData->getHighScore();
    this->boardHighScoreLabel->setString(std::to_string(this->highScore));
    
    this->gameState = GameState::GameOver;
    this->stopAllActions();
    this->runAction(this->timeline);
    timeline->play("gameOver", false);
    timeline->setLastFrameCallFunc([this]{
        scoreBoardCountUpAnimation();
    });

    this->runAction(Sequence::create(
        DelayTime::create(0.4f),
        CallFunc::create([]{
            experimental::AudioEngine::play2d("Assets/sounds/sfx_swooshing.mp3", false, 1.0f);
        }),
        DelayTime::create(1.0f),
        CallFunc::create([]{
            experimental::AudioEngine::play2d("Assets/sounds/sfx_swooshing.mp3", false, 1.0f);
        }),
        NULL
    ));
}

void GameScene::triggerWaitNextGame()
{
    this->gameState = GameState::WaitNextGame;
    this->playButton->setVisible(true);
    this->leaderboardButton->setVisible(true);
}

static int countUpScore;
void GameScene::scoreBoardCountUpAnimation()
{
    this->boardScoreLabel->setString("0");
    if (this->score <= 0) {
        showMedal();
        triggerWaitNextGame();
        return;
    }

    countUpScore = 0;
    int repeatCount = (this->score < 20) ? this->score : 20;
    this->runAction(Sequence::create(
        Repeat::create(Sequence::create(
            CallFunc::create([this, repeatCount]{
                countUpScore++;
                int score = floorf(this->score * countUpScore / (float)repeatCount);
                this->boardScoreLabel->setString(std::to_string(score));
            }),
            DelayTime::create(0.04f),
            NULL
        ), repeatCount),
        CallFunc::create([this]{
            highScoreCountUpAnimation();
        }),
    NULL));
}

void GameScene::highScoreCountUpAnimation()
{
    if (this->score <= this->highScore) {
        showMedal();
        triggerWaitNextGame();
        return;
    }
    
    userData->setHighScore(this->score);
    countUpScore = 0;
    int delta = this->score - this->highScore;
    int repeatCount = (delta < 20) ? delta : 20;
    this->runAction(Sequence::create(
        Repeat::create(Sequence::create(
            CallFunc::create([this, repeatCount, delta]{
                countUpScore++;
                int score = floorf(delta * countUpScore / (float)repeatCount) + this->highScore;
                this->boardHighScoreLabel->setString(std::to_string(score));
            }),
            DelayTime::create(0.04f),
            NULL
        ), repeatCount),
        CallFunc::create([this]{
            this->highScore = this->score;
            showMedal();
            triggerWaitNextGame();
        }),
    NULL));
}

void GameScene::spawnObstacle()
{
    auto obstacle = dynamic_cast<Obstacle*>(CSLoader::createNode("Obstacle.csb"));
    obstacle->setPositionX(this->back->getContentSize().width);
    float y = (OBSTACLE_MAX_Y - OBSTALCE_MIN_Y) * CCRANDOM_0_1() + OBSTALCE_MIN_Y;
    obstacle->setPositionY(y);
    this->back->addChild(obstacle);
    this->obstacles.pushBack(obstacle);
}

bool GameScene::isHitCharacter(Obstacle* obstacle)
{
    AABB charaAABB = this->character->getAABB();
    std::vector<AABB> AABBs = obstacle->getAABBs();
    bool isHit = false;
    for (auto obstalceAABB : AABBs) {
        isHit = isHit || charaAABB.intersects(obstalceAABB);
    }
    return isHit;
}

void GameScene::setScore(int score)
{
    this->score = score;
    this->scoreLabel->setString(std::to_string(score));
}

void GameScene::pushPlayButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    auto button = dynamic_cast<ui::Button*>(pSender);
    if (type == ui::Widget::TouchEventType::BEGAN) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, -4)));
    } else if (type == ui::Widget::TouchEventType::ENDED) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, 4)));
        goNextGame();
    } else if (type == ui::Widget::TouchEventType::CANCELED) {
        button->runAction(MoveBy::create(0.1f, Vec2(0, 4)));
    }
}

void GameScene::pushLeaderboardButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
}

void GameScene::goNextGame()
{
    experimental::AudioEngine::play2d("Assets/sounds/sfx_swooshing.mp3", false, 1.0f);
    auto nextGameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.9f, nextGameScene, Color3B(0,0,0)));
}

void GameScene::showMedal()
{
    Sprite* medalImage = nullptr;
    if (this->score > 40) {
        medalImage = Sprite::create("medal/medal_platium.png");
    } else if (this->score > 30) {
        medalImage = Sprite::create("medal/medal_gold.png");
    } else if (this->score > 20) {
        medalImage = Sprite::create("medal/medal_silver.png");
    } else if (this->score > 10) {
        medalImage = Sprite::create("medal/rmedal_bronze.png");
    }
    
    if (medalImage) {
        this->medalNode->addChild(medalImage);
    }
}
