//
//  MainScene.h
//  50Numbers
//
//  Created by Bui Tho on 10/4/16.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "cocos2d.h"
#include "LayerEffect.h"

class MainScene : public LayerEffect
{
public:
    CREATE_FUNC(MainScene);
    
    static cocos2d::Scene* createScene();
    
    virtual bool    init() override;
    virtual void    update(float dt) override;
    
    virtual bool    onTouchBegan(Touch *touch, Event *uevent) override;
    virtual void    onTouchMoved(Touch *touch, Event *uevent) override;
    virtual void    onTouchEnded(Touch *touch, Event *uevent) override;
    
    MainScene();
    ~MainScene();
    
protected:
    Sprite              *sprite;
};

#endif /* MainScene_hpp */
