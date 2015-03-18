/**
 *	读取命名设置的xml文件
 */
#ifndef SET_NAME_PARAM_XML_READER_H_
#define SET_NAME_PARAM_XML_READER_H_


/**
 *	读取xml配置文件
 */
class SetNameParamXMLReader
{
public:
	SetNameParamXMLReader();

    /**
	 *	读取xml文件中的配置信息
	 * \param filePath 文件路径
	 * \return bool	如果读取成功返回true， 否则返回false
	 */
	bool readConfigFile(const char *filePath);

private:
	char m_version[64];
};

#endif

