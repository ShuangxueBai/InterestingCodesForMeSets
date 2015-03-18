#include "SnapLinesManger.h"

using namespace std;

SnapLinesManger::SnapLinesManger()
{
}

SnapLinesManger::~SnapLinesManger()
{
}

bool SnapLinesManger::addNodeInfo(CoordNodeInfo& nodeInfo)
{
  //添加节点信息
  if(nodeInfo.pNode == NULL)
	return false;

  int coords[4] = { nodeInfo.min_x, nodeInfo.max_x,
                    nodeInfo.min_y, nodeInfo.max_y};
  IVxCGNode* pTmpNode = nodeInfo.pNode; 		

  //向对应set中插入节点指针。
  m_CoordAndNodes[Min_x][coord[Min_x]].insert(pTmpNode);
  m_CoordAndNodes[Max_x][coord[Max_x]].insert(pTmpNode);
  m_CoordAndNodes[Min_y][coord[Min_y]].insert(pTmpNode);
  m_CoordAndNodes[Max_y][coord[Max_y]].insert(pTmpNode);
  
  return true;
}

bool SnapLinesManger::isDisplaySnapLine(const IVxCGNode* pNode, const int axis_var, const unsigned int coordFlag)
{
	//从组织结构中找出是否有与这个坐标值相匹配的项。
	if(coordFlag > 3) //超出标识范围
		return false;

	//return m_CoordAndNodes[coordFlag].find(axis_var) != m_CoordAndNodes[coordFlag].end(); 如果要求可以包括自身原来的位置。
	
	if(m_CoordAndNodes[coordFlag].find(axis_var) != m_CoordAndNodes[coorFlag].end())
	{
	  if(m_CoordAndNodes[coorFlag][axis_var].size > 1)
		return true;
	  else if( m_CoordAndNodes[coorFlag][axis_var].size == 1)
	  {
	    //判断这个是不是原来节点指针
		return m_CoordAndNodes[coorFlag][axis_var].find(pNode) == m_CoordAndNodes[coorFlag][axis_var].end();
	  }
	}
	
   return false;   
}

bool SnapLinesManger::deleteNodeInfo(const IVxCGNode* pNode)
{
	//删除结构中包含的节点信息。
	if(pNode == NULL)
		return false;

	//遍历结构进行查找
	map< int, set<IVxCGNode*> >::iterator iter;
	set<IVxCGNode*>::iterator setItera;
	for(int index = 0; index < 4; index++)
	{
	  iter = m_CoordAndNodes[index].begin();
	  while(iter != m_CoordAndNodes[index].end())
	  {
		setItera = iter->value().find(pNode);
		if(setItera != iter->value().end())
		{
			iter->value().erase(setItera);
			if(iter->value().size() == 0)
			{  
			  //移除map中的这一项
			  m_CoordAndNodes[index].erase(itera++);
			  continue;
			}
		}
		iter++;
	  } // end while
	} // end for
	return true;
}

















