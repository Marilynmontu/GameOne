#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

class DistanceUpdater : public Node {

public:
	CREATE_FUNC(DistanceUpdater);

	virtual bool init() {
		this->scheduleUpdate();
		return true;
	}

	void setVars(Label *label, Sprite *sprite) {
		m_sprite = sprite;
		m_label = label;
	}

	virtual void update(float dt) {
		int x = m_sprite->getPosition().x-50;
		m_label->setString(StringUtils::format("%d", x));
	}

private:
	Sprite *m_sprite;
	Label *m_label;
};

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	
    addChild(rootNode);

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();

	auto background = DrawNode::create();
	background->drawSolidRect(origin, size, Color4F(1.0, 1.0, 1.0, 1.0));
	rootNode->addChild(background);

	m_player = Sprite::create("player.png");
	m_player->setPosition(Vec2(50,300));
	rootNode->addChild(m_player);

	auto moveby = MoveBy::create(3.0, Vec2(860, 0));
	m_player->runAction(moveby);

	m_label = Label::create("99","Arial",20);
	m_label->setColor(Color3B(0, 0, 0));
	m_label->setPosition(900, 550);
	rootNode->addChild(m_label);

	auto updater = DistanceUpdater::create();
	updater->setVars(m_label, m_player);
	rootNode->addChild(updater);

    return true;
}
