//
//  UserData.hpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/24.
//
//

#ifndef UserData_hpp
#define UserData_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class UserData {
public:
    bool init();
    bool save();
    static UserData* load();
    int getHighScore();
    void setHighScore(int score);
    
private:
    static std::string getFilePath();
    ValueMap _data;
};


#endif /* UserData_hpp */
