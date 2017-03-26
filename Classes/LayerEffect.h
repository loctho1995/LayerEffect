/*
 Created by Loc Tho
 
 Create a new class and inherit EffectNode class 
 create shader and add put unifrom params on setupUniforms by override
 */

#pragma once
#include "cocos2d.h"
#include "EffectNode.h"

using namespace cocos2d;

#define LAYER_EFFECT_CHILD__NONE_EFFECT_TAG 8296

class LayerEffect : public Layer
{
public:
	LayerEffect();
	~LayerEffect();
	
	//add effect to whole layer
	virtual void    addChildEffect(EffectNode *child);

	//child which will not be affect
	virtual void    addChildWithoutEffect(Node *node);

	virtual bool    init() override;
    virtual void    update(float dt) override;
	virtual void    visit(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	virtual void    onChilrenEffectDraw(EffectNode *node);
	virtual void    removeEffect(EffectNode *node);
    
	virtual void    setDefaultProgram();
	virtual void    setContentSize(const Size & size) override;
	virtual void    setColor(Color3B color);

protected:
	RenderTexture           *texture,
                            *textureTemp;
	
	CustomCommand           childrenCommand;

	Vector<EffectNode*>     childrenEffect;

	Tex2F                   textCoords[6];
	Vec2                    vertices[6];
	Color4F                 colors[6];
	Color4F                 bgColor;
};

