//
//  Util.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/21.
//
//

#include "Util.hpp"

using namespace cocos2d;

Vec3 Util::toVec3(Vec2 vec2)
{
    return Vec3(vec2.x, vec2.y, 0);
}
