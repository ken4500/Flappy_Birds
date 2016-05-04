//
//  Ground.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/20.
//
//

#ifndef __Flappy_Birds__Ground__
#define __Flappy_Birds__Ground__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class Ground : public cocos2d::Node {
public:
    CREATE_FUNC(Ground);
    bool init() override;
    void onEnter() override;
    void moveLeft(float distance);

protected:
    cocostudio::timeline::ActionTimeline* timeline;
    cocos2d::Vector<cocos2d::Sprite*> grounds;

};

#endif /* defined(__Flappy_Birds__Ground__) */
