/**
 *	命名设置中的使用的xml参数写入
 */
#ifndef SET_NAME_PARAM_XML_WRITER_H_
#define SET_NAME_PARAM_XML_WRITER_H_

/**
 *	写入xml文件
 */
class SetNameParamXMLWriter
{
public:

	/**
	*	将制定的“设置”对话框信息写入，制定的xml文件中
	* \param filePath xml文件路径
	* \return bool 如果写入成功返回true， 否则返回false
	*/
	bool writeConfigInfo(const char* filePath);

};
#endif




