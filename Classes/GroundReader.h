//
//  GroundReader.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/20.
//
//

#ifndef __Flappy_Birds__GroundReader__
#define __Flappy_Birds__GroundReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class GroundReader : public cocostudio::NodeReader {
public:
    static GroundReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Flappy_Birds__Ground__) */
