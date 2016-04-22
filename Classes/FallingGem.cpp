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

#include "FallingGem.h"
bool FallingGem::init(GemSprite *gemSp, int gemType, float gemPosition, float gemSpeed){
    gemSprite_ = gemSp;
    gemType_ = gemType;
    gemPositionY_ = gemPosition;
    gemSpeedY_ = gemSpeed;
    
    return true;
}
FallingGem * FallingGem::createWithInfo(GemSprite *gemSp, int gemType, float gemPositionY, float gemSpeedY){
    
    FallingGem *gem = new FallingGem();
    gem->init(gemSp, gemType, gemPositionY, gemSpeedY);
    gem->autorelease();
    return gem;
}


bool FallingGem::init(GemSprite *gemSp, int gemType,float gemPositionX, float gemPositionY, float gemSpeedX , float gemSpeedY){
    gemSprite_ = gemSp;
    gemType_ = gemType;
    gemPositionY_ = gemPositionY;
    gemPositionX_ = gemPositionX;
    gemSpeedY_ = gemSpeedY;
    gemSpeedX_ = gemSpeedX;
    isPowerUpGem = false;
    
    return true;
}
FallingGem * FallingGem::createWithInfo(GemSprite *gemSp, int gemType,float gemPositionX, float gemPositionY,float gemSpeedX , float gemSpeedY){
    
    FallingGem *gem = new FallingGem();
    gem->init(gemSp, gemType,gemPositionX, gemPositionY, gemSpeedX, gemSpeedY);
    gem->autorelease();


    return gem;
}