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

#ifndef __match3__GameLayer__
#define __match3__GameLayer__

#include <iostream>
#include "GameConstants.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameLayer : public Layer
{
	GameLayer();
	~GameLayer();
private:
    int gameLevel_;
    int scoreTarget_;
    int movesAllowed_;
    
    
    float kOffsetX;
    float kOffsetY;
    Size windowSize;
    
    bool finalGameOverScreen;
    int localScore;
    Size winSize;
    Sprite* bgLayerSprite;
    LabelBMFont* movesLabel;
    Sprite* splashSprite_;
public:
    
    bool startTouchEnable;
    
    void fallingGem();
    void StartTouch();
    void GameStart();
	void GameOverScreen(float dt);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool init();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    
    static Scene* scene();
    CREATE_FUNC(GameLayer);
    
    void setupBoard();
    void removeMarkedGems();
//    bool removeConnectedGems(int x, int y);
	void removeConnectedGems(Ref * obj);
    
    void onRemoveFromParent(Node * value);
	void pasueButtonPressed(Ref *obj);
    int findMove();
    void displayHint();
	void removSplash(Node *sender);
    void createRandomMove();
    void createGameOver();
    void updateGameOver();
    double nowInSeconds();
    bool isValidPosition(Vec2 point);
    void swapCandiesWithAnimation(Vec2 p1, Vec2 p2, bool callback);
    void checkGridForCombinations(Node *sender);
    bool isValidMove(Vec2 p1,Vec2 p2);
    bool checkGridPositionForValidMove(Vec2 point);
    bool checkGridPositionForValidMoveOnBoard(Vec2 point,int board[][kBoardHeight]);
    Vec2 getHintPoint();
    bool isValidEmojiCombinationAt (Vec2 p1,Vec2 p2,Vec2 p3, int type, int board[][kBoardHeight]);
    int getGemType(int x, int y);
    void setGemType(int x, int y, int newType);
    
    __Array * findConnectedGems(int x, int y);
    void findConnectedGems_(int x, int y, __Array * arr, int gemType);
    virtual void update(float fDelta);
    
    bool areAdjacent(Vec2 p1,Vec2 p2);
    
    
    __Array *currentEmojiFramesList_;
    Sprite *gBoardSprites[kBoardWidth][kBoardHeight];
    int gBoard[kBoardWidth][kBoardHeight];
    int gNumGemsInColumn[kBoardWidth];
    int gTimeSinceAddInColumn[kBoardWidth];
    __Array *gFallingGems[kBoardWidth];
    __Array *gGameOverGems;
    
    bool gBoardChangedSinceEvaluation;
    int gPossibleMove;
    bool gIsGameOver;
    double gStartTime;
    long gLastMoveTime;
    bool gIsDisplayingHint;
    int gNumConsecutiveGems;
    bool gEndTimerStarted;
    void addSplashParticleEffect(int x, int y);
    int gScore;
    int gLastScore;
    LabelTTF *gScoreLabel;
    ParticleSystemQuad *gPowerPlayParticles;
    LayerColor *gPowerPlayLayer;
    //sprtHeader
    ProgressTimer*saveMeTimer;
    LabelBMFont *coinLabel_;
    ProgressTimer *gTimer;
    Node * gHintLayer;
    Sprite *selectionSprite_;
    bool isSelected_;
    Vec2 movePoint1;
    Vec2 movePoint2;
    bool isMakingMove_;
    Vec2 touchBegan_;
    
	void shakeSpritesRandomly(float dt);
	void enablelightningPowerUp(float dt);
    bool lightningPowerAdded;
    int powerUpMatchedWithType;
    __Array * lightningArray;
    __Array * flashesArray;
	void removeLightningEffect(float dt);
    
};
#endif /* defined(__match3__GameLayer__) */
