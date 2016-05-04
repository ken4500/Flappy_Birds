//
//  CharacterReader.h
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/19.
//
//

#ifndef __Flappy_Birds__CharacterReader__
#define __Flappy_Birds__CharacterReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class CharacterReader : public cocostudio::NodeReader {
public:
    static CharacterReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__Flappy_Birds__Character__) */
