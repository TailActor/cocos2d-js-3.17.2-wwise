#include "sceneBase.h"
#include "WWiseHelper.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include "avg_log.h"
#include "cocos/ui/UIButton.h"

SceneBase* SceneBase::create() {
	auto ret = new (std::nothrow) SceneBase();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void SceneBase::update(float dt) {
	WWISE::update();
}

bool SceneBase::init() {
	mylog("SceneBase::init");
	if (!Scene::init()) {
		cocos2d::log("SceneBase::init failed");
		return false;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	auto sp = cocos2d::Sprite::create("res/png1.png");
	sp->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	sp->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(sp);

//#ifdef AK_ANDROID
//	AAssetManager* mgr = FileUtilsAndroid::getAssetManager();
//	__android_log_print("WWISE", "AppDelegate::applicationDidFinishLaunching", "AAssetManager:0x%x", mgr);
//#else
//	void* mgr = NULL;
//#endif
	//void* mgr = NULL;
	//WWISE::initialize(mgr);

	this->scheduleUpdate();

	AkBankID bankID;
	if (AK::SoundEngine::LoadBank("Main.bnk", bankID) != AK_Success) {
		mylog("SceneBase::init LoadBank Main.bnk failed");
	} else {
		mylog("SceneBase::init LoadBank Main.bnk success");
	}

	auto button = cocos2d::ui::Button::create("res/HelloWorld.png", "res/HelloWorld.png");
	auto size = cocos2d::Director::getInstance()->getWinSize();
	button->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2));
	button->setPressedActionEnabled(true);
	button->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType e) {
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED) {
			mylog("SceneBase::onTouch");

			AkUniqueID event = AK::SoundEngine::GetIDFromString("Play_jump1");

			AkGameObjectID gameObjId = 888;
			auto ret = AK::SoundEngine::RegisterGameObj(gameObjId, "PlayAtLocation");

			auto audioId = AK::SoundEngine::PostEvent("Play_jump1", gameObjId);
			//auto audioId = AK::SoundEngine::PostEvent(event, gameObjId);
			if (audioId == AK_INVALID_PLAYING_ID) {
				mylog("SceneBase::init PostEvent failed");
			} else {
				mylog("SceneBase::init PostEvent success");
			}
		}
	});
	this->addChild(button);

	return true;
}
