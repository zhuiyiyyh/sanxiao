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

#ifndef EggJump_GameState_h
#define EggJump_GameState_h
#include "cocos2d.h"
using namespace cocos2d;
class GameState:public cocos2d::Node
{
	GameState();
	virtual ~GameState();
private:
    static bool instanceFlag;
    static GameState *single;
    
    int totalLife;
    int levelNo;
    double timeInSeconds;
	
    
    virtual bool init();
    static GameState * create(void);

    
public:

    CC_SYNTHESIZE(bool, isNetWorkAvailAble_, isNetWorkAvailAble);
    static GameState* sharedGameState();
    int levelCompleted; // TODO: delete

    int score;
	CCDictionary* levelInfoDict;
    


    int getLives();
    int getCurrentLevelNumber();
    void setCurrentLevelNumber(int level);
    void giveLife(int,bool);
    int getScoreTarget(int levelNum);
    int getTotalMoves(int levelNum);
    int getLevelHighScore(int levelNum);
    void updateLevelHighScore(int score, const char *key);
    int getLevelHighScore(const char* key);
    bool addLevelProgress(int score, int level);
    bool isLevelCompleted(int level);
    int getLevelStars(int level);
    int getLevelStarsWithScore(int level,int score);
    void updateScoreToServer();
	void timerForLifeCheck(float dt = 0);
    int getRemainingTimeForLife();
    int getCompletedLevelCount();
  
};
#endif
