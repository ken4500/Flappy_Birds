//
//  UserData.cpp
//  Flappy_Birds
//
//  Created by Ken Watanabe on 2016/04/24.
//
//

#include "UserData.hpp"

bool UserData::init()
{
    _data = ValueMap();
    return save();
}


bool UserData::save()
{   //保存箇所のフルパスを取得
    std::string path = UserData::getFilePath();
    
    // 保存
    if(FileUtils::getInstance()->writeToFile(_data, path)){
        CCLOG("save Success:%s", path.c_str());
        return true;
    }else{
        CCLOG("save Failed:%s", path.c_str());
        return false;
    }
}

UserData* UserData::load()
{
    UserData* result = new UserData();
    auto path = UserData::getFilePath();
    if (FileUtils::getInstance()->isFileExist(path) == false) {
        result->init();
    }
    result->_data = FileUtils::getInstance()->getValueMapFromFile(path);
    return result;
}

int UserData::getHighScore()
{
    if (_data.find("high_score") == _data.end()) {
        return 0;
    } else {
        return _data["high_score"].asInt();
    }
}

void UserData::setHighScore(int score)
{
    int highScore = this->getHighScore();
    if (score > highScore) {
        _data["high_score"] = score;
        this->save();
    }
}

std::string UserData::getFilePath()
{
    return FileUtils::getInstance()->getWritablePath() + "user_data";
}

