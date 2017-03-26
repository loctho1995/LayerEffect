//
//  EffectBlur.cpp
//  LayerEffect
//
//  Created by Bui Dinh Loc Tho on 3/16/17.
//  Blog: http://loctho95.blogspot.com
//  Youtube: https://www.youtube.com/user/BuiDinhTho1/playlists
//  Forums: http://gameuit.club
//  Github: https://github.com/loctho1995
//
//

#include "EffectVerticalBlur.h"

EffectVerticalBlur::EffectVerticalBlur()
{
    
}

EffectVerticalBlur::~EffectVerticalBlur()
{
    
}

EffectVerticalBlur* EffectVerticalBlur::createEffectVerticalBlur()
{
    auto p = new EffectVerticalBlur();
    
    if(p && p->init())
    {
        p->autorelease();
        return p;
    }
    
    CC_SAFE_DELETE(p);
    
    return nullptr;
}

bool EffectVerticalBlur::init()
{
    return EffectNode::init();
}
const char* EffectVerticalBlur::getVertName()
{
    return "Shader/blur.vert";
}

const char* EffectVerticalBlur::getFragName()
{
    return "Shader/vertical_blur.frag";
}

void EffectVerticalBlur::setupUniforms()
{
    auto p = this->getGLProgramState();
    
    auto resolution = Director::getInstance()->getVisibleSize();
    
    p->setUniformVec2("resolution", resolution);
    p->applyUniforms();
}
