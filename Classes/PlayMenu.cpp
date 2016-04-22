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

#include "PlayMenu.h"


#include "SimpleAudioEngine.h"

#include "GameConstants.h"
#include "GameLayer.h"
#include "GameUtils.h"
#include "GameState.h"

#define FACEBOOK_LOGIN_IMAGE_PRESSED "SocialUI/btn_fblogin_pressed.png"
#define FACEBOOK_LOGOUT_IMAGE_PRESSED "SocialUI/btn_fblogout_pressed.png"
#define ENVLOPE_IMAGE_PRESSED  "SocialUI/FriendHelp/envelope_pressed.png"
#define ENVLOPE_IMAGE  "SocialUI/FriendHelp/envelope.png"
#define FACEBOOK_LOGIN_IMAGE "SocialUI/btn_fblogin.png"
#define FACEBOOK_LOGOUT_IMAGE "SocialUI/btn_fblogout.png"
#define PLAY_IMAGE_PRESSED "SocialUI/btn_play_pressed.png"
#define PLAY_IMAGE "SocialUI/btn_play.png"
#define BACKGROUND "SocialUI/background.png"
#define LOGO "SocialUI/img_logo.png"
#define LIFE_COUNT_STRING "Life Count %i"


using namespace cocos2d;

void PlayMenu:: onEnter()
{
  
  Layer::onEnter();
}


Scene* PlayMenu::scene()
{
    // 'scene' is an autorelease object
  Scene *scene = Scene::create();
  
    // 'layer' is an autorelease object
  PlayMenu *layer = PlayMenu::create();
  
    // add layer as a child to scene
  scene->addChild(layer);
  
    // return the scene
  return scene;
}

  // on "init" you need to initialize your instance
bool PlayMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!cocos2d::Layer::init())
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//    winSize = TARGET_DESIGN_RESOLUTION_SIZE;
    winSize = Director::sharedDirector()->getWinSize();

    setupGUI();
    this->setKeypadEnabled(true);

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MainMenuMusic.mp3",true);
  return true;
}

//void PlayMenu:: keyBackClicked(void) {
//    Layer::keyBackClicked();
//    Director::sharedDirector()->end();
//}
void PlayMenu::timerForLifeCheck()
{
    float totalSec=GAME_SHARED_HANDLER->getRemainingTimeForLife();
   
    if (totalSec<=0)
    {
        GAME_SHARED_HANDLER->timerForLifeCheck();

    }
    
    int hour=(int)totalSec/3600;
    totalSec=totalSec-3600*hour;
    
    int minute=(int)totalSec/60;
    
    totalSec=(int)totalSec-60*minute;

    
    
    string hourString = static_cast<ostringstream*>( &(ostringstream() << hour) )->str();
    string minuteString = static_cast<ostringstream*>( &(ostringstream() << minute) )->str();
    string SecondString = static_cast<ostringstream*>( &(ostringstream() << totalSec) )->str();

    SecondString=hourString + ":" + minuteString+":" + SecondString ;
    timerForLife->setString(SecondString.c_str());
    
   
    
}
void PlayMenu::play(Ref* obj)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
    Scene *scene = Scene::create();
    GameLayer *gameLayer = GameLayer::create();
    gameLayer->GameStart();
    scene->addChild(gameLayer);
    
    Director::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.5,scene));

}
void PlayMenu:: onExit()
{
    Layer::onExit();
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);

}
void PlayMenu::setupGUI()
{

    LabelTTF*  timerLabel=  LabelTTF::create(NEXT_LIFE_IN, GAME_LABEL_FONT_NATHAN, 29);
    timerLabel->setPosition(ccp(winSize.width/2-170,winSize.height/2+430));
	timerLabel->setColor(Color3B::BLUE);
    timerLabel->setTag(KTAG_PLYMENU_COINSLBL);

    timerForLife=  LabelTTF::create("", GAME_LABEL_FONT_NATHAN, 29);
    timerForLife->setPosition(ccp(winSize.width/2-20,winSize.height/2+430));
	timerForLife->setColor(Color3B::BLACK);
    timerForLife->setTag(KTAG_PLYMENU_COINSLBL);
    
    Sprite* bckg = Sprite::create(BACKGROUND);
    bckg->setPosition( ccp(winSize.width/2,winSize.height/2) );
    CCLOG("win size %f ",winSize.width);
    this->addChild(bckg, 0-KTAG_LAYERING_PARAM);
    
    MenuItemImage *playMenuItem = MenuItemImage::create(PLAY_IMAGE, PLAY_IMAGE_PRESSED, this,menu_selector(PlayMenu::play));
    
    Menu *menu = Menu::create(playMenuItem,NULL);
    
    menu->setPosition(ccp(0, 0));
    playMenuItem->setPosition(ccp(winSize.width/2, winSize.height/2-(275)));
      
    this->addChild(menu);
    
}


void PlayMenu::updateLifeCountLabel(){
    LabelTTF *lifeCountLabel = (LabelTTF *) this->getChildByTag(KTAG_Life_Count);
    string TotalLifeCount = static_cast<ostringstream*>( &(ostringstream() << GAME_SHARED_HANDLER->getLives()) )->str();
    TotalLifeCount="Life Count " + TotalLifeCount;
    lifeCountLabel->setString(TotalLifeCount.c_str());
}



