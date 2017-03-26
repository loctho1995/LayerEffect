#include "LayerEffect.h"

LayerEffect::LayerEffect():
textureTemp(nullptr),
texture(nullptr)
{
	
}

LayerEffect::~LayerEffect()
{
	CC_SAFE_RELEASE_NULL(texture);
	CC_SAFE_RELEASE_NULL(textureTemp);
}

bool LayerEffect::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = this->getContentSize();
	
	this->setDefaultProgram();
	
    //init texture which have size equal Layer's size
	texture = RenderTexture::create(this->getContentSize().width, this->getContentSize().height);
	texture->getSprite()->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	texture->getSprite()->getTexture()->setAntiAliasTexParameters();
	texture->retain();

    //texture temp
	textureTemp = RenderTexture::create(this->getContentSize().width, this->getContentSize().height);
	textureTemp->getSprite()->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	textureTemp->getSprite()->getTexture()->setAntiAliasTexParameters();
	textureTemp->retain();

    //texture coord which use bind texture to shader program
	textCoords[0] = Tex2F(0.0, 0.0);
	textCoords[1] = Tex2F(0.0, 1.0);
	textCoords[2] = Tex2F(1.0, 1.0);
	textCoords[3] = Tex2F(0.0, 0.0);
	textCoords[4] = Tex2F(1.0, 1.0);
	textCoords[5] = Tex2F(1.0, 0.0);

    //vertices
	vertices[0] = Vec2(0, 0);
	vertices[1] = Vec2(0, size.height);
	vertices[2] = Vec2(size.width, size.height);
	vertices[3] = Vec2(0, 0);
	vertices[4] = Vec2(size.width, size.height);
	vertices[5] = Vec2(size.width, 0);

	colors[0] = Color4F::WHITE;
	colors[1] = Color4F::WHITE;
	colors[2] = Color4F::WHITE;
	colors[3] = Color4F::WHITE;
	colors[4] = Color4F::WHITE;
	colors[5] = Color4F::WHITE;

	this->scheduleUpdate();
	
	return true;
}

void LayerEffect::update(float dt)
{
	Node::update(dt);
	
	for (auto child : childrenEffect)
	{
		if(child->isEffectEnable())
			child->update(dt);
	}
}

void LayerEffect::setColor(Color3B color)
{
	this->bgColor = Color4F(color);
}

void LayerEffect::setDefaultProgram()
{
    //er will need a default program which pass Vertices info to it's Shader program
	this->setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
}

void LayerEffect::setContentSize(const Size & size)
{
    //we must resize the texture size after change the ContentSize
	Layer::setContentSize(size);

	if (texture != nullptr)
	{
		texture->removeFromParentAndCleanup(true);

		texture = RenderTexture::create(size.width, size.height);
		texture->getSprite()->setAnchorPoint(Vec2(0.0, 0.0));
		this->addChild(texture);
	}
    
    if (textureTemp != nullptr)
    {
        textureTemp->removeFromParentAndCleanup(true);
        
        textureTemp = RenderTexture::create(size.width, size.height);
        textureTemp->getSprite()->setAnchorPoint(Vec2(0.0, 0.0));
        this->addChild(textureTemp);
    }
}

void LayerEffect::addChildEffect(EffectNode *child)
{
	child->retain();
	
	childrenEffect.pushBack(child);
}

void LayerEffect::addChildWithoutEffect(Node *node)
{
	node->setTag(LAYER_EFFECT_CHILD__NONE_EFFECT_TAG);
	this->addChild(node);
}

void LayerEffect::visit(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	
    /*
     I will re-write the visit method of Layer. I render all of Layer's children on
     variable texture (RenderTexture). Then I copy it to textureTemp to use textureTemp bind to 
     Shader program (use on onChilrenEffectDraw function)
     */
    
    //clear the texture
	texture->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	
	// quick return if not visible. children won't be drawn.
	if (!_visible)
	{
		return;
	}

	// IMPORTANT:
	// To ease the migration to v3.0, we still support the Mat4 stack,
	// but it is deprecated and your code should not rely on it
	_director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

	bool visibleByCamera = isVisitableByVisitingCamera();

	int i = 0;

	if (!_children.empty())
	{
		sortAllChildren();
		// draw children zOrder < 0
		
		for (; i < _children.size(); i++)
		{
			auto node = _children.at(i);
			
			if (node->getTag() == LAYER_EFFECT_CHILD__NONE_EFFECT_TAG)
				continue;

			if (node && node->getLocalZOrder() < 0)
				node->visit(renderer, _modelViewTransform, flags);
			else
				break;
		}
		// self draw
		if (visibleByCamera)
			this->draw(renderer, _modelViewTransform, flags);

		for (auto it = _children.cbegin() + i; it != _children.cend(); ++it)
		{
			if ((*it)->getTag() == LAYER_EFFECT_CHILD__NONE_EFFECT_TAG)
				continue;

			(*it)->visit(renderer, _modelViewTransform, flags);
		}
	}

	_director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	
	//all child drawn on texture
	texture->end();
    
    //finish draw Layer's children to texture
	
    //clear textureTemp and visit texture to textureTemp
	textureTemp->beginWithClear(0, 0, 0, 0);
	texture->getSprite()->visit(renderer, transform, flags);
	textureTemp->end();
	
    //then I fore cocos to render to draw texture to textureTemp
	Director::getInstance()->getRenderer()->render();
	
    //Apply Effect. Use multi-effect
	for (auto child : childrenEffect)
	{
		if(child->isEffectEnable())
		{
            //I will not clear the texture, because which pixel on Shader Program is not process
            //I will discard to make performance better
            
			texture->begin();
			//apply children effect to texture
			childrenCommand.init(this->getGlobalZOrder());
			childrenCommand.func = CC_CALLBACK_0(LayerEffect::onChilrenEffectDraw, this, child);
			renderer->addCommand(&childrenCommand);
			texture->end();
				
			//copy to texture
			textureTemp->beginWithClear(0, 0, 0, 0);
			texture->getSprite()->visit(renderer, transform, flags);
			textureTemp->end();
			
            //fore cocos render to apply Effect to texture and use it to next Effect
			Director::getInstance()->getRenderer()->render();
		}
	}
	
    //render texture to backbuffer which will show on screen
	textureTemp->getSprite()->visit(renderer, transform, flags);

    //render node which we dont want to apply effect
	for (size_t i = 0; i < _children.size(); i++)
	{
		auto child = _children.at(i);

		if (child->getTag() == LAYER_EFFECT_CHILD__NONE_EFFECT_TAG)
		{
			child->visit(renderer, transform, flags);
		}
	}
}

void LayerEffect::removeEffect(EffectNode *node)
{
	node->release();
	
	childrenEffect.eraseObject(node);
}

void LayerEffect::onChilrenEffectDraw(EffectNode *node)
{
	auto p = node->getGLProgramState()->getGLProgram();
	p->use();
	p->setUniformsForBuiltins();
	
	node->setupUniforms();
	
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
	GL::bindTexture2D(textureTemp->getSprite()->getTexture()->getName());
	
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, textCoords);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)6);
}
