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

#ifndef __match3__FallingGem__
#define __match3__FallingGem__
#include "GameConstants.h"
#include "GemSprite.h"
#include "cocos2d.h"
using namespace cocos2d;

class FallingGem : public cocos2d::Ref
{
public:
    
    static FallingGem * createWithInfo(GemSprite *gemSp, int gemType, float gemPosition, float gemSpeed);
    bool init(GemSprite *gemSp, int gemType, float gemPosition, float gemSpeed);
    
    static FallingGem * createWithInfo(GemSprite *gemSp, int gemType,float gemPositionX, float gemPositionY, float gemSpeedX,float gemSpeedY);
    bool init(GemSprite *gemSp, int gemType,float gemPositionX, float gemPositionY, float gemSpeedX , float gemSpeedY);

    
    
    GemSprite *gemSprite_;
    int gemType_;
    float gemPositionY_;
    float gemPositionX_;
    float gemSpeedY_;
    float gemSpeedX_;

    bool isPowerUpGem;

};

#endif
