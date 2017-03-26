//
//  MainScene.cpp
//  50Numbers
//
//  Created by Bui Tho on 10/4/16.
//
//

#include "MainScene.h"
#include "EffectGrayscale.h"
#include "EffectHorizontalBlur.h"
#include "EffectVerticalBlur.h"

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

MainScene::MainScene()
{
    
}

MainScene::~MainScene()
{
    
}

bool MainScene::init()
{
    if(!LayerEffect::init())
    {
        return false;
    }

    auto size = Director::getInstance()->getVisibleSize();

    auto grayscale = EffectGrayscale::createEffectGrayscale();
    this->addChildEffect(grayscale);
    
    auto horizontalBlur = EffectHorizontalBlur::createEffectHorizontalBlur();
    this->addChildEffect(horizontalBlur);
    
    auto verticalBlur = EffectVerticalBlur::createEffectVerticalBlur();
    this->addChildEffect(verticalBlur);
    
    sprite = Sprite::create("test.jpg");
    sprite->setPosition(size.width / 2, size.height / 2);
    this->addChild(sprite);
    
    auto cocos = Sprite::create("HelloWorld.png");
    cocos->setPosition(size.width / 2, size.height / 2);
    this->addChild(cocos);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleUpdate();
    
    return true;
}

void MainScene::update(float dt)
{
    LayerEffect::update(dt);
}

bool MainScene::onTouchBegan(Touch *touch, Event *uevent)
{

    return true;
}

void MainScene::onTouchMoved(Touch *touch, Event *uevent)
{

}

void MainScene::onTouchEnded(Touch *touch, Event *uevent)
{

}
