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
    
    m_rootNode = CSLoader::createNode("MainScene.csb");
	
    addChild(m_rootNode);

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto size = Director::getInstance()->getVisibleSize();

	auto background = DrawNode::create();
	background->drawSolidRect(origin, size, Color4F(0.5098f, 0.9098f, 0.6078f, 1.0));
	background->drawSegment(Vec2(0.0, 200.0), Vec2(960.0, 200.0), 1.0f, Color4F(0.6196f, 0.4745f, 0.1294f, 1.0));
	m_rootNode->addChild(background);

	


	m_label = Label::create("99","Arial",20);
	m_label->setColor(Color3B(0, 0, 0));
	m_label->setPosition(900, 550);
	m_rootNode->addChild(m_label);

	
	this->scheduleUpdate();


    return true;
}

void HelloWorld::update(float delta)
{
	int x = m_player->getPosition().x - 50;
	m_label->setString(StringUtils::format("%d", x));

	cpSpaceStep(m_space, delta);
}

void HelloWorld::onEnter()
{
	Node::onEnter();
	m_space = cpSpaceNew();

	cpVect gravity = { 0.0f, -350.0f };
	cpSpaceSetGravity(m_space, gravity);

	m_player = PhysicsSprite::create("player.png");
	//m_player->setPosition(Vec2(50, 300));
	m_rootNode->addChild(m_player);

	auto moveby = MoveBy::create(3.0, Vec2(860, 0));
	

	auto playerSize = m_player->getContentSize();
	m_playerBody = cpBodyNew(1.0f, cpMomentForBox(1.0f, playerSize.width, playerSize.height));
	cpSpaceAddBody(m_space, m_playerBody);
	cpVect bodyPos = { 50.0f, 300.0f };
	cpBodySetPos(m_playerBody, bodyPos);

	m_playerShape = cpBoxShapeNew(m_playerBody, playerSize.width, playerSize.height);
	cpSpaceAddShape(m_space, m_playerShape);
	m_player->setCPBody(m_playerBody);
	//m_player->runAction(moveby);

	auto m_debugNode = PhysicsDebugNode::create(m_space);
	this->addChild(m_debugNode, 10);

	cpVect beginPonit = { 0, 200.0f };
	cpVect endPoint = { 300.0f, 200.0f };
	m_ground1 = cpSegmentShapeNew(cpSpaceGetStaticBody(m_space), beginPonit, endPoint, 0.0f);
	cpSpaceAddStaticShape(m_space, m_ground1);
	cpVect j = { 120.0f, 0.0f };
	cpBodyApplyImpulse(m_playerBody, j, cpvzero);


}

void HelloWorld::onExit()
{
	cpSpaceFree(m_space);
	m_space = nullptr;

	cpBodyFree(m_playerBody);
	m_playerBody = nullptr;
	Node::onExit();
}
