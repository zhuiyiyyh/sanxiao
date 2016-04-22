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

#ifndef __match3__EndGameLayer__
#define __match3__EndGameLayer__


#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class EndGameLayer: public Layer
{
private:
    
    Sprite* background;
    void setupGUI();
    
public:
    
   
    Size winSize;
    virtual bool init();
	void restartGame(Ref* obj);
	void quitGame(Ref* obj);
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static Scene* scene();
    
    virtual void onEnter();
    virtual void onExit();
    
    //function
       
    
    // implement the "static node()" method manually
    CREATE_FUNC( EndGameLayer );
};

#endif /* defined(__match3__EndGameLayer__) */
