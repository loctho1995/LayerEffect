#include "EffectNode.h"

EffectNode::EffectNode()
{

}

EffectNode::~EffectNode()
{

}

bool EffectNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	auto p = GLProgram::createWithFilenames(getVertName(), getFragName());
	
	this->setGLProgramState(GLProgramState::create(p));
	
	this->enable = true;

	return true;
}


void EffectNode::setupUniforms()
{

}

const char* EffectNode::getVertName()
{
	return "";
}

const char* EffectNode::getFragName()
{
	return "";
}

void EffectNode::setEffectEnable(bool flag)
{
	this->enable = flag;
}

bool EffectNode::isEffectEnable()
{
	return this->enable;
}
