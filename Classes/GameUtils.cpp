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

#include "GameUtils.h"
#include "GameConstants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
//#include "rapidjson.h"
//#include "document.h"
//#include "ParseUtil.h"
using namespace std;
//using namespace rapidjson;

Size GameUtils::getDesignResolution() {

  return TARGET_DESIGN_RESOLUTION_SIZE;
}

int GameUtils::getIntFromCCString(__String *str)
{
    
    return atoi(str->getCString());
    
}

__String* GameUtils::getCCStringFromInt(int num)
{
    char key[100];
    sprintf(key,"%d",num);
    __String *str = new __String(key);
    str->autorelease();
    return str;
}

__String * GameUtils::getCCString(const char* arr)
{
	__String *str = new __String(arr);
	str->autorelease();
	return str;
}

bool GameUtils::isStringEqual(const char *pStr1, const char *pStr2)
{
    return strcmp(pStr1, pStr2) == 0;
}

bool GameUtils::isValid(const char* value)
{
	if(!value || isStringEqual(value, ""))
	{
		return false;
	}
	return true;
}
std::string GameUtils::getStdStringFromInt(int value)
{
    char key[100];
    sprintf(key,"%d",value);
    return std::string(key);
}

std::string GameUtils::getStdStringFromLongInt(int64_t value)
{
	 CCLOG("log:: vaulue %d",value);
    char key[100];
    sprintf(key,"%I64u",value);
    return std::string(key);
}

__String* GameUtils::getCCStringFromDouble(double value)
{

	char key[100];
	sprintf(key, "%f", value);
	__String *str = new __String(key);
	str->autorelease();
	return str;
}

//Ref* GameUtils::convertDocumentToCObject(const char* data)
//{
//	if(!data)
//	{
//		CCLOG("Zuluu:: Data is NULLLL");
//	}
//	Document document;
//	if(data != NULL && !document.Parse<0>(data).HasParseError())
//	{
//		CCDictionary *makerInfoDict = (CCDictionary* ) ParseUtils::parse(document);
//		makerInfoDict->retain();
//		makerInfoDict->autorelease();
//		return makerInfoDict;
//	}
//	else
//	{
//		CCLOG("Zuluu:: Document PArse ERROR %s ::%s",document.GetParseError(),data);
//	}
//	return NULL;
//}
