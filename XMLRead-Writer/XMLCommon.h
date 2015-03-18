/**
 *	这里是XML读取写入时共有的一些东西
 */
#ifndef XML_COMMON_H_
#define XML_COMMON_H_
#include "global.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#define KEYS_MAX 261

//写入字符串数据宏
#define WRITE_ELE_XML(strEle, strTxt, tmpStr, keysMax, doc, root)	do{				\
	XMLString::transcode(strEle, tmpStr, keysMax - 1);													\
	DOMElement *_tmpEle = (doc)->createElement(tmpStr);										\
	root->appendChild(_tmpEle);																					\
	XMLString::transcode(strTxt, tmpStr, keysMax - 1);												\
	DOMText *_tmpTxt = (doc)->createTextNode(tmpStr);											\
	_tmpEle->appendChild(_tmpTxt);																			\
}while(0);

//写入布尔值数据宏
#define WRITE_ELE_BOOL_XML(strEle, tmpStr, keysMax, doc, root, isBool) do{		\
	char _strTmp2[2] = {0};																						\
	if(isBool)																												\
		strncpy(_strTmp2, "1", sizeof(char) * 2);																\
	else																														\
		strncpy(_strTmp2, "0", sizeof(char) * 2);																\
	WRITE_ELE_XML(strEle, _strTmp2, tmpStr, keysMax, doc, root);							\
} while (0);


//读取字符串的数据宏
#define READ_ELE_XML(strEle, strOutput, keyMax, doc)  do{												\
	xercesc::DOMNode *tmpNode = doc->getElementsByTagName(XMLString::transcode(strEle))->item(0);			\
	if (tmpNode->getFirstChild())																									\
	{																																			\
		std::string _strTmp = XMLString::transcode(tmpNode->getFirstChild()->getNodeValue());		\
		strncpy(strOutput, _strTmp.c_str(), sizeof(char) * keyMax);										\
	}																																			\
	else																																		\
	{																																			\
		memset(strOutput, 0, sizeof(char)* keyMax);																\
	}																																			\
}while(0);

//读取布尔值的数据宏
#define READ_ELE_BOOL_XML(strEle, doc, outputBool) do{						\
	char _strTmp2[2] = {0};																							\
	READ_ELE_XML(strEle, _strTmp2, 2, doc);													\
	if( '1' == _strTmp2[0])																								\
		outputBool = true;																									\
	else																															\
		outputBool = false;																									\
}while(0);

#endif

