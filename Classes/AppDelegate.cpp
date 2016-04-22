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
#include "AppDelegate.h"
#include "cocos2d.h"
#include "GameConstants.h"
#include "GameLayer.h"
#include "PlayMenu.h"
#include "GameState.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
	CCLOG("log:: in finish lauching");
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect("My Game",Rect(0, 0, 640, 960));
		director->setOpenGLView(glview);
	}
	
	ResolutionPolicy policy = ResolutionPolicy::EXACT_FIT;

    //******************************setting resource directories*****************************
    vector<string> searchPath;
    Size designResolutionSize = TARGET_DESIGN_RESOLUTION_SIZE;
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, policy);
	Size frameSize = glview->getFrameSize();
    
	CCLOG("log:: designResolutionSize szie %f designResolutionSize %f height", designResolutionSize.width, designResolutionSize.height);
    CCLOG("log:: frame szie %f width %f height",frameSize.width,frameSize.height);

    if (frameSize.height >= resource2.size.height)
    {
        CCLOG("log:: hd1");
        searchPath.push_back(resource2.directory);
        
        float scaleValue = MIN(resource2.size.height/designResolutionSize.height, resource2.size.width/designResolutionSize.width);
        
		director->setContentScaleFactor(scaleValue);
    }
    else
    {
    	CCLOG("log:: sd");
        searchPath.push_back(resource1.directory);
		director->setContentScaleFactor(MIN(resource1.size.height / designResolutionSize.height, resource1.size.width / designResolutionSize.width));
    }
    
   // GAME_SHARED_HANDLER->schedule(schedule_selector(GAME_SHARED_HANDLER::timerForLifeCheck),1/60);
     GameState::sharedGameState();
    FileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    //******************************setting resource directories*****************************
    
    // turn on display FPS
	director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    Scene *pScene;
    pScene = PlayMenu::scene();
    // run
    
	director->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::sharedDirector()->pause();
    Director::sharedDirector()->stopAnimation();
    CCLOG("BackEnd");
    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    //    ccGLInvalidateStateCache();
    //    CCShaderCache::getInstance()->reloadDefaultShaders();
    //    ccDrawInit();
    //    CCTextureCache::reloadAllTextures();
    //    //CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
    //    Director::sharedDirector()->setGLDefaultValues();
    
    Director::sharedDirector()->resume();
    Director::sharedDirector()->startAnimation();
    
    CCLOG("ForeEnd");
    // if you use SimpleAudioEngine, it must resume here
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
