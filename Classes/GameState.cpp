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

#include <iostream>
#include "GameState.h"
#include "GameUtils.h"
#include "GameConstants.h"
#include "SimpleAudioEngine.h"


#define KEY_LIFE_COUNT "lifeCount"
#define KTAG_GAME_PLAYED_FIRST_TIME "GameCount"
#define K_TIME_TAG "initTime"


using namespace std;
using namespace cocos2d;
bool GameState::instanceFlag = false;
GameState* GameState::single = NULL;
GameState::GameState()
{
	totalLife = 0;
	levelInfoDict = NULL;
}
GameState::~GameState()
{ 
	instanceFlag = false; 
	CC_SAFE_RELEASE_NULL(levelInfoDict); 
}
GameState* GameState::create()
{
    GameState * pRet = new GameState();
        
    if (pRet && pRet->init())
    {
        return pRet;
    }

    return NULL;
}
bool GameState::init()
{
    if (Node::init())
    {
        isNetWorkAvailAble_ = false;
        CCUserDefault::sharedUserDefault()->flush();
        
        levelInfoDict = CCDictionary::createWithContentsOfFile(LEVEL_INFO_PLIST);
        levelInfoDict->retain();
        
    
        totalLife= CCUserDefault::sharedUserDefault()->getIntegerForKey(KEY_LIFE_COUNT, 1);
        CCLOG("log:: totalLive %d",totalLife);
        timeInSeconds= CCUserDefault::sharedUserDefault()->getDoubleForKey(K_TIME_TAG,0.0);
        
        
        
        int gameCount= CCUserDefault::sharedUserDefault()->getIntegerForKey(KTAG_GAME_PLAYED_FIRST_TIME, 0);
        if (gameCount==0){
            struct timeval now;
			gettimeofday(&now, NULL);
            timeInSeconds = (now.tv_sec + (double)(now.tv_usec / 1000000.0f));
            CCUserDefault::sharedUserDefault()->setDoubleForKey(K_TIME_TAG,timeInSeconds);
            CCUserDefault::sharedUserDefault()->setIntegerForKey(KTAG_GAME_PLAYED_FIRST_TIME, 1);
            CCUserDefault::sharedUserDefault()->flush();
        }
        else
        {
            timerForLifeCheck();
        }

        
        this->schedule(schedule_selector(GameState::timerForLifeCheck),1/60);

         return true;
    }
    
    return false;
   
}

int GameState::getScoreTarget(int levelNum)
{
    CCDictionary *levelDic = dynamic_cast<CCDictionary*>(levelInfoDict->objectForKey(__String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,1)->getCString()));
    __String *targetScoreString = (__String*)levelDic->objectForKey("targetScore");
    int targetScore = GameUtils::getIntFromCCString(targetScoreString);
    return targetScore;


}

int GameState::getTotalMoves(int levelNum)
{
    CCDictionary *levelDic = dynamic_cast<CCDictionary*>(levelInfoDict->objectForKey(__String::createWithFormat("%s%d",LEVEL_KEY_PREFIX, 1)->getCString()));
    __String *moveString = (__String*)levelDic->objectForKey("moves");
    int totalMoves = GameUtils::getIntFromCCString(moveString);
    return totalMoves;    
}




void GameState::updateScoreToServer()
{
    if (isNetWorkAvailAble_ == false) {
        CCLOG("log:: isnetworkAvailAble %d",isNetWorkAvailAble_);
        return;
    }
    int totalScore = 0;
    for(int i=1 ; i<=TOTAL_LEVELS ; i++){
    
        const char *key = __String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,i)->getCString();
        int score = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
        if(score==0){
            break;
        }
        totalScore+=score;
        
    }

   CCLOG("log:: in update ScoreToServer");
//   CPP_FacebookGameController::getInstance()->FB_SendScore(totalScore);

}

int GameState::getCurrentLevelNumber(){
    return levelNo;
}
void GameState::setCurrentLevelNumber(int level){
    levelNo = level;
}
bool GameState::addLevelProgress(int score, int level){
    const char *key = __String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,level)->getCString();
    int perviousHighScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    int targetScore = GAME_SHARED_HANDLER->getScoreTarget(level);

    
    if(score>targetScore){
             
    }
    
    else{
        GAME_SHARED_HANDLER->giveLife(1, false);
    }
    
    
    if (perviousHighScore < score) {
        CCUserDefault::sharedUserDefault()->setIntegerForKey(key, score);
        CCUserDefault::sharedUserDefault()->flush();
        return true;
    }
    return false;
}


int GameState::getCompletedLevelCount(){

    for (int i=0; i<TOTAL_LEVELS ; i++){
        if(!GAME_SHARED_HANDLER->isLevelCompleted(i+1)){
            return i;
        }
    }
    return TOTAL_LEVELS;
}


bool GameState::isLevelCompleted(int level){
    const char *key = __String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,level)->getCString();
    int highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    int targetScore = GAME_SHARED_HANDLER->getScoreTarget(level);

    if(highscore>targetScore){
        return true;
    }
    return false;
}
int GameState::getLevelStars(int level){
    
    const char *key = __String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,level)->getCString();
    int highscore = CCUserDefault::sharedUserDefault()->getIntegerForKey(key);
    int targetScore = GAME_SHARED_HANDLER->getScoreTarget(level);
    int stars = 0;
    
    float percentage =(highscore/targetScore)*75;
    
    if (percentage<75)
        stars=0;
    else if (percentage>74 && percentage<83)
        stars=1;
    else if (percentage>82 && percentage<93)
        stars=2;
    else
        stars=3;
    
    
    return stars;
}

int GameState::getLevelStarsWithScore(int level,int score){
    

    int highscore = score;
    int targetScore = GAME_SHARED_HANDLER->getScoreTarget(level);
    int stars = 0;
    
    float percentage =(highscore/targetScore)*75;
    
    if (percentage<75)
        stars=0;
    else if (percentage>74 && percentage<83)
        stars=1;
    else if (percentage>82 && percentage<93)
        stars=2;
    else
        stars=3;
    
    
    return stars;
}

int GameState::getLevelHighScore(int levelNum){
    __String *key = __String::createWithFormat("%s%d",LEVEL_KEY_PREFIX,levelNum);
    int levelHighScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(key->getCString());
    return levelHighScore;
}

void GameState::timerForLifeCheck(float dt)
{
	struct  timeval now;
	gettimeofday(&now, NULL);
    double retVal = (now.tv_sec + (double)(now.tv_usec / 1000000.0f));
    float diffInSec=retVal-timeInSeconds;
    int totalVal = diffInSec/Total_Life_Refresh_Time_In_sec;
    if (totalVal>0)
    {
        giveLife(totalVal, true);
        //// Again Refresh Counter of Timer
		struct timeval now;
		gettimeofday(&now, NULL);
        timeInSeconds = (now.tv_sec + (double)(now.tv_usec / 1000000.0f));
        CCUserDefault::sharedUserDefault()->setFloatForKey(K_TIME_TAG,timeInSeconds);
        CCUserDefault::sharedUserDefault()->flush();
    }

}

int GameState::getRemainingTimeForLife(){
    
	struct timeval now;
	gettimeofday(&now, NULL);
    double retVal = (now.tv_sec + (double)(now.tv_usec / 1000000.0f));
    float diffInSec=retVal-timeInSeconds;
    
    
    if(diffInSec>Total_Life_Refresh_Time_In_sec){
        return 0;
    }
    else{
        return Total_Life_Refresh_Time_In_sec-diffInSec;
    }
}




int GameState::getLives(){
    return totalLife;
}

void GameState::giveLife(int quantity, bool add)
{
    
	CCLOG("log:: quantity %d",quantity);
    if (add){
        totalLife+=quantity;
    	CCLOG("log:: totallife1 %d",totalLife);

    }
    else
    {
        totalLife=totalLife-quantity;
    	CCLOG("log:: totallife2 %d",totalLife);
    }
    if(totalLife>MAX_LIVES_COUNT){
        totalLife = MAX_LIVES_COUNT;
    }
	CCLOG("log:: totallife3 %d",totalLife);

    CCNotificationCenter::sharedNotificationCenter()->postNotification(N_LIFE_COUNT_UPDATED);
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey(KEY_LIFE_COUNT, totalLife);
    CCUserDefault::sharedUserDefault()->flush();

}

GameState* GameState::sharedGameState()
{
    if(! instanceFlag)
    {
        single = GameState::create();//new GameState();
        instanceFlag = true;

        return single;
    }
    else
    {
        return single;
    }
}
