#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "_chipmunk.h"
USING_NS_CC;
USING_NS_CC_EXT;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float delta) override;
	void onEnter() override;
	void onExit() override;
private:
	PhysicsSprite *m_player;
	Label *m_label;
	cpSpace *m_space;
	cpBody *m_playerBody;
	cpShape *m_playerShape;
	cpShape *m_ground1;
	Node *m_rootNode;
};

#endif // __HELLOWORLD_SCENE_H__
