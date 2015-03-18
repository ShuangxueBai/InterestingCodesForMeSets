/**
 * \author bshx
 * \date 2014-03-19
 * \detail 实现一个对图元的对齐线问题，解决方案。
 */
 
 #ifndef _SnapLinesManager_h_
 #define _SnapLinesManager_h_
 
 #include <stdlib.h>
 #include <pthread.h>
 #include <vector>
 #include <map>
 #include <set>
 
 using namespace std;
 
 
 /**
  * \struct CoordNodeInfo 传递图元（物件组）节点的坐标信息
  */
  struct CoordNodeInfo
  {
	int min_x, max_x; //!< 最大最小x坐标
	int min_y, max_y; //!< 最大最小y坐标
	IVxCGNode* pNode;
	
	/*
	  定义构造和析构
	 */
	CoordNodeInfo(): min_x(0), max_x(0),
	                 min_y(0), max_y(0),
					 pNode(NULL)
					 {}
    ~CoordNodeInfo() {}	
  }
 
 
 
 /**
  * \class SnapLineManager 来管理对对齐线的显示和计算
  * \detail 
  *	 拟定使用map和set容器来分别进行对齐线中，对图元包围盒最大，最小坐标和所归属图元（物件组）索引。
  *  根据移动图元的包围盒最值坐标来确定是否在场景中有图元与这个最值坐标
  */
   class SnapLineManager
   {
	public:
		SnapLineManager();
		~SnapLineManager();
		
		
		/**
		 * \enum 包围盒最大最小坐标标识
		 */
		enum CoordMinMax
		{
			Min_x = 0,
			Max_x,
			Min_y,
			Max_y
		};
		
		/**
		 * \param nodeInfo 图元及包围盒坐标信息
		 * \return 如果添加成功返回true， 否则返回false
		 * \detail 
		 *   对当前场景中一个图元（物件组）的信息进行添加，添加后的信息经过map容器排序
		 */
		 bool addNodeInfo(CoordNodeInfo& nodeInfo);
		 
		 /**
		  * \param  pNode 节点物件指针
		  * \param axis_var 具体坐标值
		  * \param coordFlag 只代表的是那个坐标，取值参考 \enum CoordMinMax
		  * \return 如果测试显示相应对齐线则返回true，否则返回false
		  * \detail
		  *    进行对各个轴向的对齐线测试，通过与场景中各个图元（物件组）进行比较。
		  * \sa CoordMinMax
		  */
		 bool isDisplaySnapLine(const IVxCGNode* pNode, const int axis_var, const unsigned int coordFlag);
		 
		
		/**
		 * 
		 * \param pNode 需要在结构中删除的节点指针数据
		 * \return 如果删除成功返回true，否则返回false
		 * \detail 
		 *    删除结构表里关于这一点的存储信息，并且当map中set没有记录时删除这个节点对齐数据。也相当于更新存储的结构。
		 */
		 bool deleteNodeInfo(const IVxCGNode* pNode);
		
	protected:
		
	private:
	  
		map< unsigned int, set<IVxCGNode*> > m_CoordAndNodes[4]; //!< 这里分别是min_x，max_x和min_y，max_y坐标与索引的集合。
   }
   
 
 
 #endif
 
 
 