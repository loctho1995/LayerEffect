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

#include "EffectHorizontalBlur.h"

EffectHorizontalBlur::EffectHorizontalBlur()
{
    
}

EffectHorizontalBlur::~EffectHorizontalBlur()
{
    
}

EffectHorizontalBlur* EffectHorizontalBlur::createEffectHorizontalBlur()
{
    auto p = new EffectHorizontalBlur();
    
    if(p && p->init())
    {
        p->autorelease();
        return p;
    }
    
    CC_SAFE_DELETE(p);
    
    return nullptr;
}

bool EffectHorizontalBlur::init()
{
    return EffectNode::init();
}
const char* EffectHorizontalBlur::getVertName()
{
    return "Shader/blur.vert";
}

const char* EffectHorizontalBlur::getFragName()
{
    return "Shader/horizontal_blur.frag";
}

void EffectHorizontalBlur::setupUniforms()
{
    auto p = this->getGLProgramState();
    
    auto resolution = Director::getInstance()->getVisibleSize();
    
    p->setUniformVec2("resolution", resolution);
    p->applyUniforms();
}
