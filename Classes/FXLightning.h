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

//#import <Foundation/Foundation.h>
//#import "MObject.h"

#include "cocos2d.h"
//#import "Node.h"

USING_NS_CC;

#define K_NUMBER_OF_LIGHTNING_SAMPLES 60


typedef struct
{
	float x;
	float y;
	
} vec2;


typedef struct
{
	float x;
	float y;
	float z;
	
} vec3;

typedef struct
{
	float x;
	float y;
	float z;
	float w;
	
} vec4;

class FXLightning :public Node {
    
public:
    float tapper;
    float width;
    float spread;
    float speed;
    
	Vec2 start;
	Vec2 end;
    
    void render();

    bool initialize();
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
private:
    GLProgram *pShaderProgram;
    Vec2 vtx[K_NUMBER_OF_LIGHTNING_SAMPLES];
	Vec2 uvs[K_NUMBER_OF_LIGHTNING_SAMPLES];
    Texture2D * texture;

};



//@end
