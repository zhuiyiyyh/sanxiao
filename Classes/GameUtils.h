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

#ifndef GameUtils_h
#define GameUtils_h

#include "cocos2d.h" 

using namespace cocos2d;

class GameUtils : public Ref
{
public:
    static Size getDesignResolution();
    static int getIntFromCCString(__String *str);
    static __String *getCCStringFromInt(int num);
    static __String *getCCString(const char* arr);
    static bool isValid(const char* value);
    static bool isStringEqual(const char *pStr1, const char *pStr2);
    static std::string getStdStringFromInt(int value);
    static std::string getStdStringFromLongInt(int64_t value);
  static __String* getCCStringFromDouble(double value);
  //static Ref* convertDocumentToCObject(const char* data);






};


#endif
