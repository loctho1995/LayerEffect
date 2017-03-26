#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class EffectNode : public Node
{
public:
	EffectNode();
	~EffectNode();

	virtual bool            init() override;
    
	virtual void            setupUniforms();
	virtual void            setEffectEnable(bool flag);
	
	virtual const char*     getFragName() = 0;
	virtual const char*     getVertName() = 0;
	virtual bool            isEffectEnable();
	
protected:
	
	bool enable;
};

