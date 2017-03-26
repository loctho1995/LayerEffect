//
//  EffectBlur.h
//  LayerEffect
//
//  Created by Bui Dinh Loc Tho on 3/16/17.
//  Blog: http://loctho95.blogspot.com
//  Youtube: https://www.youtube.com/user/BuiDinhTho1/playlists
//  Forums: http://gameuit.club
//  Github: https://github.com/loctho1995
//
//
#ifndef EffectVerticalBlur_h
#define EffectVerticalBlur_h

#include "EffectNode.h"

class EffectVerticalBlur : public EffectNode
{
public:
    EffectVerticalBlur();
    ~EffectVerticalBlur();
    
    static EffectVerticalBlur* createEffectVerticalBlur();
    
    bool init() override;
    
    virtual const char*     getVertName() override;
    virtual const char*     getFragName() override;
    virtual void            setupUniforms() override;
};

#endif /* EffectBlur_h */
