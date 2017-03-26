//
//  EffectGrayscale.cpp
//  LayerEffect
//
//  Created by Bui Dinh Loc Tho on 3/16/17.
//  Blog: http://loctho95.blogspot.com
//  Youtube: https://www.youtube.com/user/BuiDinhTho1/playlists
//  Forums: http://gameuit.club
//  Github: https://github.com/loctho1995
//
//

#include "EffectGrayscale.h"

EffectGrayscale* EffectGrayscale::createEffectGrayscale()
{
    EffectGrayscale *node = new EffectGrayscale();
    
    if(node && node->init())
    {
        node->autorelease();
        return node;
    }
    
    CC_SAFE_DELETE(node);
    
    return nullptr;
}

bool EffectGrayscale::init()
{
    if(! EffectNode::init())
        return false;
    
    return true;
}

void EffectGrayscale::update(float dt)
{
    EffectNode::update(dt);
}

const char* EffectGrayscale::getVertName()
{
    return "Shader/grayscale.vert";
}

const char* EffectGrayscale::getFragName()
{
    return "Shader/grayscale.frag";
}

void EffectGrayscale::setupUniforms()
{
    
}
