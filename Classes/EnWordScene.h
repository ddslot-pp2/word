#ifndef __ENWORD_SCENE_H__
#define __ENWORD_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"
#include <thread>
#include <mutex>

class WordInfo;

using namespace cocos2d;

class EnWordScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void update(float dt) override;

    void StartWords();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EnWordScene);

private:
    void LoadWordInfos();

    std::vector<std::shared_ptr<WordInfo>> word_infos_;
    std::vector<Label*> words_;

    Vec2 center_;

    bool start_down_words_ = false;
    bool complete_preparing_words_ = true;

    std::once_flag flag_;

    Node* action_controller_;

    ui::Button* submit_button_;
};

#endif // __HELLOWORLD_SCENE_H__
