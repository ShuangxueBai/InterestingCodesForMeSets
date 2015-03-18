#include "stdafx.h"
#include <QtCore/QFile>
#include "setNameParamXMLWriter.h"
#include "XMLCommon.h"

XERCES_CPP_NAMESPACE_USE

bool SetNameParamXMLWriter::writeConfigInfo(const char* filePath)
{
	bool res = false;
	//首先进行XML DOM建立，然后将其转为字符串输出结果
	try
	{
		//初始化xml工具
		XMLPlatformUtils::Initialize();
	}
	catch (xercesc::XMLException & excp)
	{
		char* msg = XMLString::transcode(excp.getMessage());
		XMLString::release(&msg);
		return res;
	}

	XMLCh tmpStr[KEYS_MAX] = { 0 }; //定义xml标签关键字

	XMLString::transcode("Core", tmpStr, KEYS_MAX - 1);
	DOMImplementation* imple = DOMImplementationRegistry::getDOMImplementation(tmpStr);

	XMLString::transcode("transSetConfig", tmpStr, KEYS_MAX - 1);
	xercesc::DOMDocument  *doc = imple->createDocument(0, tmpStr, 0);
	DOMElement      *root = doc->getDocumentElement();
	root->setAttribute(XMLString::transcode("version"), XMLString::transcode("1.0"));

	char strTmp[MAX_PATH] = {0};
	//--formatName
	strncpy(strTmp, g_nameSetParam.strName, sizeof(char) * MAX_PATH);
	WRITE_ELE_XML("formatName", strTmp, tmpStr, KEYS_MAX, doc, root);

	//--prefix
	WRITE_ELE_BOOL_XML("prefix", tmpStr, KEYS_MAX, doc, root, g_nameSetParam.isHasPrefix);

	//--prefixName
	memset(strTmp, 0, sizeof(char) * MAX_PATH);
	strncpy(strTmp, g_nameSetParam.strPrefixName, sizeof(char) * MAX_PATH);
	WRITE_ELE_XML("prefixName", strTmp, tmpStr, KEYS_MAX, doc, root);

	//--suffix
	WRITE_ELE_BOOL_XML("suffix", tmpStr, KEYS_MAX, doc, root, g_nameSetParam.isHasSuffix);

	//--suffixName
	memset(strTmp, 0, sizeof(char) * MAX_PATH);
	strncpy(strTmp, g_nameSetParam.strSuffixName, sizeof(char) * MAX_PATH);
	WRITE_ELE_XML("suffixName", strTmp, tmpStr, KEYS_MAX, doc, root);

	//转为文件
	//将DOM转换成字符串 
	DOMLSOutput* p_DOMLSoutput = imple->createLSOutput();
	DOMLSSerializer *theSerializer = imple->createLSSerializer();
	XMLCh* encoding = XMLString::transcode("UTF-8");
	p_DOMLSoutput->setEncoding(encoding); //设置字符编码
	p_DOMLSoutput->setByteStream(new MemBufFormatTarget());
	theSerializer->write(doc, p_DOMLSoutput);
	XMLFormatTarget* p_XMLFormatTarget = p_DOMLSoutput->getByteStream();
	//将字符串返还
	char *pXML = (char*)((MemBufFormatTarget*)p_XMLFormatTarget)->getRawBuffer();
	XMLString::release(&encoding);

	QString strPath = QString(filePath);
	QFile dstFile(strPath);
	if (dstFile.open(QFile::WriteOnly | QFile::Text))
	{
		//写入文件
		dstFile.write(pXML);
		dstFile.close();
		res = true;
	}
	//释放资源
	p_DOMLSoutput->release();
	theSerializer->release();
	doc->release();
	// 销毁xerces-c工具
	XMLPlatformUtils::Terminate();
	return res;
}




