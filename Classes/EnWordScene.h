#ifndef __ENWORD_SCENE_H__
#define __ENWORD_SCENE_H__

#include "cocos2d.h"

class WordInfo;

class EnWordScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EnWordScene);

private:
    std::vector<std::shared_ptr<WordInfo>> word_infos_;
};

#endif // __HELLOWORLD_SCENE_H__
