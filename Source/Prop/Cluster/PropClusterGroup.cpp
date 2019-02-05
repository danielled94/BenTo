/*
  ==============================================================================

    PropClusterGroup.cpp
    Created: 5 Feb 2019 11:12:42am
    Author:  jonglissimo

  ==============================================================================
*/

#include "PropClusterGroup.h"

PropClusterGroup::PropClusterGroup() :
	BaseItem("Cluster Group"),
	clusterManager("Clusters")
{
	addChildControllableContainer(&clusterManager);
	clusterManager.selectItemWhenCreated = false;
	clusterManager.editorCanBeCollapsed = false;
}

PropClusterGroup::~PropClusterGroup()
  {
  }

int PropClusterGroup::getLocalPropID(Prop * p)
{
	for (auto &c : clusterManager.items)
	{
		int id = c->getLocalPropID(p);
		if (id >= 0) return id;
	}

	return -1;
}

var PropClusterGroup::getJSONData()
{
	var data = BaseItem::getJSONData();
	data.getDynamicObject()->setProperty("clusterManager", clusterManager.getJSONData());
	return data;
}

void PropClusterGroup::loadJSONDataInternal(var data)
{
	BaseItem::loadJSONDataInternal(data);
	clusterManager.loadJSONData(data.getProperty("clusterManager", var()));
}