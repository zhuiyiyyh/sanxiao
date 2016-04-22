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

#include "EndGameLayer.h"
#include "GameConstants.h"
#include "PlayMenu.h"
#include "GameLayer.h"
#include "GameState.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

#define ENDGAME_BACKGROUND "SocialUI/background_no_logo.png"
#define LEVELCOMPELTE_LABEL "SocialUI/levelComplete.png"
#define GAMEOVER_LABEL "SocialUI/gameOver.png"

Scene* EndGameLayer::scene()
{
    Scene *scene = Scene::create();
    EndGameLayer *layer = EndGameLayer::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool EndGameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    winSize = Director::sharedDirector()->getWinSize();
    setupGUI();
    this->setTouchEnabled(true);
    
    return true;
}

void EndGameLayer:: onEnter()
{
 //   Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kMenuHandlerPriority, true);
	//_eventDispatcher->addEventListenerWithFixedPriority(this, -128);
    Layer::onEnter();
}

void EndGameLayer::setupGUI()
{
    
    //add bg.
    background = Sprite::create(ENDGAME_BACKGROUND);
    background->setPosition( ccp(winSize.width/2, winSize.height/2) );
    this->addChild(background);
    
    MenuItemImage *restartMenuItem = MenuItemImage::create(BUTTON_RESTART_GAME, BUTTON_RESTART_GAME_PRESSED, this,menu_selector(EndGameLayer::restartGame));
    MenuItemImage *quitMenuItem = MenuItemImage::create(BUTTON_QUIT_GAME, BUTTON_QUIT_GAME_PRESSED, this,menu_selector(EndGameLayer::quitGame));
    
    Menu *menu = Menu::create(restartMenuItem,quitMenuItem,NULL);
	menu->setPosition(Vec2::ZERO);
    background->addChild(menu);
    
    restartMenuItem->setPosition(ccp(winSize.width/2 - 150, winSize.height/2 - 250 ));
    restartMenuItem->setScale(0.65);
    
    quitMenuItem->setPosition(ccp(winSize.width/2 + 150, winSize.height/2 - 250 ));
    quitMenuItem->setScale(0.65);

    GameState *gs = GameState::sharedGameState();
    if(gs->score >= gs->getScoreTarget( gs->getCurrentLevelNumber() )){
        Sprite *sprite = Sprite::create(LEVELCOMPELTE_LABEL);
        sprite->setPosition(ccp(winSize.width/2, winSize.height/2 + 320));
        this->addChild(sprite, 26);
//        LabelBMFont* levelComlete = LabelBMFont::create("LEVEL COMPLETE",cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename("font.fnt").c_str(), 35);
//        levelComlete->setAlignment( kCCTextAlignmentCenter );
//        levelComlete->setAnchorPoint( ccp(0.5,0.5) );
//        levelComlete->setWidth(winSize.width);
//        levelComlete->setPosition(ccp(winSize.width/2, winSize.height/2 + 360));
//        levelComlete->setScale(0.8);
//        this->addChild(levelComlete,26);
        
        
        LabelBMFont* score = LabelBMFont::create("Score: ", FileUtils::sharedFileUtils()->fullPathForFilename("font.fnt").c_str(), 35);
        score->setAlignment( kCCTextAlignmentCenter );
        score->setAnchorPoint( ccp(0.5,0.5) );
        score->setPosition(ccp(winSize.width/2, winSize.height/2 + 100));
        
        char buffer[64];
        sprintf(buffer, "Score: %d", GameState::sharedGameState()->score);
        score->setString(buffer);
        
        this->addChild(score, 26);
    }
    else{
        Sprite *sprite = Sprite::create(GAMEOVER_LABEL);
        sprite->setPosition(ccp(winSize.width/2, winSize.height/2 + 160));
        this->addChild(sprite, 26);

//        LabelBMFont* levelComlete = LabelBMFont::create("GAME OVER",cocos2d::FileUtils::sharedFileUtils()->fullPathForFilename("font.fnt").c_str(), 35);
//        levelComlete->setAlignment( kCCTextAlignmentCenter );
//        levelComlete->setAnchorPoint( ccp(0.5,0.5) );
//        levelComlete->setWidth(winSize.width);
//        levelComlete->setPosition(ccp(winSize.width/2, winSize.height/2 + 360));
//        levelComlete->setScale(1.0);
//        this->addChild(levelComlete,26);
    }
}

void EndGameLayer::restartGame(Ref* obj){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
    Scene *scene = Scene::create();
    GameLayer *gameLayer = GameLayer::create();
    gameLayer->GameStart();
    scene->addChild(gameLayer);
  
    Director::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3,scene));
}
void EndGameLayer::quitGame(Ref* obj){
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ButtonClick.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MainMenuMusic.mp3");
    this->removeFromParent();
    Scene *scene = Scene::create();
    PlayMenu *playLayer = PlayMenu::create();
    scene->addChild(playLayer);
    Director::sharedDirector()->replaceScene(scene);
}
void EndGameLayer::onExit()
{
    //Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}


