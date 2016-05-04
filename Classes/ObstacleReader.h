//
//  ObstacleReader.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/21.
//
//

#ifndef __Flappy_Birds__ObstacleReader__
#define __Flappy_Birds__ObstacleReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class ObstacleReader : public cocostudio::NodeReader {
public:
    static ObstacleReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Flappy_Birds__Obstacle__) */
