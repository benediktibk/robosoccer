#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULT_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULT_H

#include "layer/control/treenode.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResult :
		public TreeNode
	{
	public:
		virtual bool decide();
		virtual void execute() = 0;

	};
}
}
}

#endif


