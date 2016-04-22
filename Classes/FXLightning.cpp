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

#include "FXLightning.h"
//#include "CCConfiguration.h"
//#include "Vec2Extension.h"
#include "perlin.h"
USING_NS_CC;



void FXLightning::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
//    Sprite::draw();
    this->render();

}

bool  FXLightning::initialize(){
	pShaderProgram = CCShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    texture = CCTextureCache::getInstance()->addImage("lightning.png");

    for (int i = 0; i < K_NUMBER_OF_LIGHTNING_SAMPLES; i+=2){
        
        uvs[ i+0 ].x = 0.0;
        uvs[ i+0 ].y = i / (float)K_NUMBER_OF_LIGHTNING_SAMPLES;
        
        uvs[ i+1 ].x = 1.0;
        uvs[ i+1 ].y = i / (float)K_NUMBER_OF_LIGHTNING_SAMPLES;
    }
    
    width = .20;
    spread = 5;
    tapper = 0;
    speed =0.005;
    return true;
}

void FXLightning::render(){

	float angle = atan2f(end.y - start.y , end.x - start.x);
	float x = cosf(angle - M_PI/2.0) * width;
	float y = sinf(angle - M_PI/2.0) * width;
	float rx = cosf(angle - M_PI/2.0) * spread;
	float ry = sinf(angle - M_PI/2.0) * spread;
    static int counter = 0;
	
	int n_samples = ccpDistance(start, end)/480 * K_NUMBER_OF_LIGHTNING_SAMPLES;
	if (n_samples > K_NUMBER_OF_LIGHTNING_SAMPLES) {
		n_samples = K_NUMBER_OF_LIGHTNING_SAMPLES;
	}
   
	for (int i=0; i < n_samples; i+=2) {
        Vec2 p = ccpLerp(start, end, i/(float)(n_samples-1));
		float r = ((rand()%100) / 100.0 - 0.5) * 7;
//        float r = 20* noise1(counter*speed);
        float w = 0;
        if (i < n_samples*0.5) {
            w = i/(float)n_samples * 3;
        }
        else{
            w = (n_samples-i-2)/(float)n_samples * 3;
        }
        w = clampf(w, 0, 1);
        if (tapper == 0) {
            vtx[ i+0 ].x = p.x + x + rx*r*w;
            vtx[ i+0 ].y = p.y + y + ry*r*w;
            
            vtx[ i+1 ].x = p.x - x + rx*r*w;
            vtx[ i+1 ].y = p.y - y + ry*r*w;
        }
        else{
            vtx[ i+0 ].x = p.x + x*tapper*(1-i/(float)n_samples) + rx*r;
            vtx[ i+0 ].y = p.y + y*tapper*(1-i/(float)n_samples) + ry*r;
            
            vtx[ i+1 ].x = p.x - x*tapper*(1-i/(float)n_samples) + rx*r;
            vtx[ i+1 ].y = p.y - y*tapper*(1-i/(float)n_samples) + ry*r;
        }
        counter+=5;
	}
    
    
    
    pShaderProgram->use();
    pShaderProgram->setUniformsForBuiltins();
    
	GL::bindTexture2D(texture->getName());
    
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vtx);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uvs);
    glDrawArrays(GL_TRIANGLE_STRIP, 0,n_samples);
    
    //DEBUG
//    glDrawArrays(GL_LINE_STRIP, 0, n_samples);
    
    CC_INCREMENT_GL_DRAWS(1);
}

