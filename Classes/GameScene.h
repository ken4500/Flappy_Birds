#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Obstacle.h"

class Character;
class Ground;
class UserData;

enum class GameState {
    Ready,
    Playing,
    GameOver,
    WaitNextGame
};

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(GameScene);
    void onEnter() override;
    void update(float dt) override;

private:
    void setupTouchHandling();
    void triggerReady();
    void triggerPlaying();
    void triggerGameOver();
    void triggerWaitNextGame();
    void spawnObstacle();
    void updateReady(float dt);
    void updatePlaying(float dt);
    void updateGameOver(float dt);
    bool isHitCharacter(Obstacle* obstacle);
    cocos2d::Vec3 toVec3(cocos2d::Vec2 vec2);
    void setScore(int score);
    void scoreBoardCountUpAnimation();
    void highScoreCountUpAnimation();
    void pushPlayButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void pushLeaderboardButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void goNextGame();
    void showMedal();

    cocos2d::Node* tutorial;
    cocos2d::Sprite* back;
    Character* character;
    GameState gameState;
    Ground* ground;
    float stagePosition;
    float lastObstaclePosition;
    cocos2d::Vector<Obstacle*> obstacles;
    cocos2d::ui::TextBMFont* scoreLabel;
    int score;
    cocostudio::timeline::ActionTimeline* timeline;
    cocos2d::ui::TextBMFont* boardScoreLabel;
    cocos2d::ui::TextBMFont* boardHighScoreLabel;
    cocos2d::Sprite* newImage;
    cocos2d::Vec2 characterStartPosition;
    cocos2d::ui::Button* playButton;
    cocos2d::ui::Button* leaderboardButton;
    cocos2d::Node* medalNode;
    int highScore;
    UserData* userData;
};

#endif // __HELLOWORLD_SCENE_H__
