#pragma once

#include "cocos2d.h"

class Core : public cocos2d::Layer

{

public:

	// there's no 'id' in cpp, so we recommend returning the class instance pointer

	static cocos2d::Scene* createScene();



	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone

	virtual bool init() override;



	// a selector callback

	//void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// implement the "static create()" method manually

	CREATE_FUNC(Core);
	
	void Run(float);

};
