/*
 * FIle Name: RoadSideUnitModel.h
 * Written by; Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
*/

#ifndef ROADSIDEUNITMODEL_H
#define ROADSIDEUNITMODEL_H

#include "InfrastructureNodeModel.h"

#define ROADSIDEUNITMODEL_NAME "RoadSideUnitModel"

class RoadSideUnitModel : public InfrastructureNodeModel
{
  public:
	inline virtual GetModelName()
	{
		return ROADSIDEUNITMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(ROADSIDEUNITMODEL_NAME) == 0 || (bDescendSufficient && InfrastructureNodeModel::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	RoadSideUnitModel(const QString& strModelName = QString::null);
	RoadSideUnitModel(const RoadSideUnitModel & copy);
	virtual ~RoadSideUnitModel();
	
	virtual RoadSideUnitModel & operator = (const RoadSideUnitModel & copy);
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	virtual int PreRun();
	virtual int ProcessEvent(SimEvent & event);
	virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
  protected:
	
};

#endif // ROADSIDEUNITMODEL_H
