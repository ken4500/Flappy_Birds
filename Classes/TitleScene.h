//
//  TitleScene.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/23.
//
//

#ifndef __Flappy_Birds__TitleScene__
#define __Flappy_Birds__TitleScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class Ground;
class Character;

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(TitleScene);
    void onEnter() override;
    void update(float dt) override;
    

private:
    Ground* ground;
    Character* character;
 
    void pushPlayButton(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    void goGameScene();
};

#endif /* defined(__Flappy_Birds__TitleScene__) */
