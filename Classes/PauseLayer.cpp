/****************************************************************************
 
 Match 3 Source Code
 
 Copyright (c) 2014 GameAcademy.com
 
 www.GameAcademy.com
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "PauseLayer.h"
#include "GameConstants.h"
#include "PlayMenu.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

#define PAUSE_BACKGROUND "SocialUI/bgr_caption.png"

Scene* PauseLayer::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    PauseLayer *layer = PauseLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!cocos2d::Layer::init())
    {
        return false;
    }
    winSize = Director::sharedDirector()->getWinSize();//TARGET_DESIGN_RESOLUTION_SIZE;
    setupGUI();
    this->setTouchEnabled(true);
    
    return true;
}

void PauseLayer:: onEnter()
{
    //Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kMenuHandlerPriority, true);
    Layer::onEnter();
}

void PauseLayer::setupGUI()
{
    
    //add bg.
    background = Sprite::create(PAUSE_BACKGROUND);
    background->setPosition( ccp(winSize.width/2, winSize.height/2) );
    this->addChild(background);
    
    MenuItemImage *resumeMenuItem = MenuItemImage::create(BUTTON_START_GAME, BUTTON_START_GAME_PRESSED, this,menu_selector(PauseLayer::resumeGame));
    MenuItemImage *quitMenuItem = MenuItemImage::create(BUTTON_QUIT_GAME, BUTTON_QUIT_GAME_PRESSED, this,menu_selector(PauseLayer::quitGame));
    
    Menu *menu = Menu::create(resumeMenuItem,quitMenuItem,NULL);
    menu->setPosition(Vec2::ZERO);
    background->addChild(menu);
    
    resumeMenuItem->setPosition(ccp(winSize.width/2, winSize.height/2 + (250)));
    quitMenuItem->setPosition(ccp(winSize.width/2, winSize.height/2 ));
    
//    quitLabel->setString("QuitGame");

    
}

void PauseLayer::resumeGame(Ref *obj)
{
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameFieldMusic.mp3");
    this->removeFromParent();
}
void PauseLayer::quitGame(Ref *obj)
{
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MainMenuMusic.mp3");
    this->removeFromParent();
    Scene *scene = Scene::create();
    PlayMenu *playLayer = PlayMenu::create();
    scene->addChild(playLayer);
    Director::sharedDirector()->replaceScene(scene);
}
void PauseLayer::onExit()
{
	//Director::getInstance()->getTouchDispatcher()->removeDelegate(this);
	
	Layer::onExit();
}

//#pragma touches Delegate

bool PauseLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}
void PauseLayer::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    
}
void PauseLayer::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    
}
void PauseLayer::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    
}
