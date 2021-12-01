#pragma once

#include "cocos2d.h"

class SceneBase : public cocos2d::Scene {
public:
	static SceneBase* create();

	virtual void update(float dt) override;

	virtual bool init() override;
};
