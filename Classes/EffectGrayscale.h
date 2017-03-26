//
//  EffectGrayscale.h
//  LayerEffect
//
//  Created by Bui Dinh Loc Tho on 3/16/17.
//  Blog: http://loctho95.blogspot.com
//  Youtube: https://www.youtube.com/user/BuiDinhTho1/playlists
//  Forums: http://gameuit.club
//  Github: https://github.com/loctho1995
//
//
#ifndef EffectGrayscale_h
#define EffectGrayscale_h

#include "cocos2d.h"
#include "EffectNode.h"

class EffectGrayscale : public EffectNode
{
public:
    static EffectGrayscale* createEffectGrayscale();
    
    virtual bool            init() override;
    virtual void            update(float dt) override;
    
    virtual const char*     getVertName() override;
    virtual const char*     getFragName() override;
    virtual void            setupUniforms() override;
};

#endif /* EffectGrayscale_h */
