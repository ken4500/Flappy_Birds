//
//  GroundReader.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/20.
//
//

#include "GroundReader.h"
#include "Ground.h"

using namespace cocos2d;

static GroundReader* _instanceGroundReader = nullptr;

GroundReader* GroundReader::getInstance() {
    if (!_instanceGroundReader) {
        _instanceGroundReader = new GroundReader();
    }
    return _instanceGroundReader;
}

void GroundReader::purge() {
    CC_SAFE_DELETE(_instanceGroundReader);
}

Node* GroundReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions) {
    Ground* node = Ground::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
