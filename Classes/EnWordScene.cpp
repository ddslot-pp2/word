#include "EnWordScene.h"
#include "Repository/WordRepository.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* EnWordScene::createScene() {
    return EnWordScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EnWordScene::init() {
    if ( !Scene::init() ) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    center_ = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EnWordScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    action_controller_ = Node::create();
    this->addChild(action_controller_);

    // 단어 가져오기 요청
    LoadWordInfos();

    // 버튼
    submit_button_ = ui::Button::create("Gui/StartNormalButton.png", "Gui/StartClickButton.png", "Gui/StartLockButton2.png");
    submit_button_->setTitleText("정답제출");
    submit_button_->setTitleFontSize(32);
    submit_button_->setScale(1.5f);
    submit_button_->getTitleRenderer()->setPositionY(50.0f);
    submit_button_->getTitleRenderer()->setAdditionalKerning(4.0f);
    // TODO(pp2): 글자색 체크
    //submit_button_->getTitleRenderer()->enableShadow(Color4B::GRAY, Size(1, -1), 0);
    //submit_button_->getTitleRenderer()->enableOutline(Color4B::GRAY, 0);
    submit_button_->setPosition(Vec2(center_.x, center_.y - 200.0f));

    submit_button_->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            auto audio = SimpleAudioEngine::getInstance();
            audio->playEffect("Sound/ButtonClick.mp3");
        }
        else if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("SUBMIT CLICKED END\n");
            /*
            auto answer = input_field_->getString();
            if (answer == "") {
                static_cast<TextFieldTTF*>(input_field_->getVirtualRenderer())->attachWithIME();
                return;
            }

            submit_button_->setEnabled(false);
            */
        }
    });

    this->addChild(submit_button_, 2);

    auto tutorial_label = Label::createWithTTF("Just Typing Words", "fonts/BMDOHYEON.ttf", 40);
    tutorial_label->setPosition(Vec2(center_.x,
                                     center_.y + 400.0f));
    this->addChild(tutorial_label, 1);
    
    auto callback = CallFunc::create([&] {
        start_down_words_ = true;
    });

    auto seq = Sequence::create(
        DelayTime::create(3.0f),
        callback,
        RemoveSelf::create(),
        nullptr);
    tutorial_label->runAction(seq);

    this->scheduleUpdate();

    return true;
}

void EnWordScene::update(float dt) {
    if (!start_down_words_) return;

    if (!complete_preparing_words_) {
        // 로딩 화면 보여주기
        return;
    }

    std::call_once(flag_, [&] { 
        StartWords();
    });
    
    for (auto i = 0; i < words_.size(); ++i) {
        const auto y = words_[i]->getPosition().y - (20.0f * dt);
        words_[i]->setPosition(words_[i]->getPosition().x, y);
    }

}

void EnWordScene::StartWords() {
    for (auto i = 0; i < word_infos_.size(); ++i) {
        auto callback = CallFunc::create([&, index = i] {
            words_.push_back(Label::createWithTTF(word_infos_[index]->word, "fonts/BMDOHYEON.ttf", 30));
            words_[index]->setPosition(center_);
            this->addChild(words_[index]);
        });

        auto seq = Sequence::create(
            DelayTime::create(static_cast<float>(i * 3)),
            callback,
            nullptr);
        action_controller_->runAction(seq);
    }
}

void EnWordScene::LoadWordInfos() {
    auto word0 = std::make_shared<WordInfo>();
    word0->word = "sediment";
    word_infos_.emplace_back(word0);

    auto word1 = std::make_shared<WordInfo>();
    word1->word = "prepare";
    word_infos_.emplace_back(word1);
}

void EnWordScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

// 나오는 단어를 쳐서 도착하기 전에 없애주세요.
// 기억나는 단어를 쳐서 없애주세요

// 모두 맞힐떄까지 반복합니다.
// 레벨 올라감 단어 많이 맞히면

// 더하기, 오늘은 그만하기
// 광고 제거 2천원
