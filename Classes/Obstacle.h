//
//  Obstacle.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/21.
//
//

#ifndef __Flappy_Birds__Obstacle__
#define __Flappy_Birds__Obstacle__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class Obstacle : public cocos2d::Node {
public:
    CREATE_FUNC(Obstacle);
    bool init() override;
    std::vector<cocos2d::AABB> getAABBs();

protected:
    cocostudio::timeline::ActionTimeline* timeline;

};

#endif /* defined(__Flappy_Birds__Obstacle__) */
