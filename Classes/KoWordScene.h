#ifndef __KOWORD_SCENE_H__
#define __KOWORD_SCENE_H__

#include "cocos2d.h"

class KoWordScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(KoWordScene);

private:
    //std::vector<WordInfo> word_infos_;
};

#endif // __HELLOWORLD_SCENE_H__
