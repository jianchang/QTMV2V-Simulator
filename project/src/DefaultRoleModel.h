/*
 * File Name: DefaultRoleModel.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#ifndef DEFAULTROLEMODEL_H
#define DEFAULTROLEMODEL_H

#include "Model.h"
#include "VehicleModel.h"

#define DEFAULTROLEMODEL_NAME "DefaultRoleModel"

class DefaultRoleModel : public RoleModel
{
  public:
	inline virtual QString GetModelType() const
	{
		return DEFAULTROLEMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(DEFAULTROLEMODEL_NAME) == 0 || (bDescendSufficient && RoleModel::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	DefaultRoleModel(const QString& strModelName = QString::null);
	DefaultRoleModel(const DefaultRoleModel& copy);
	virtual ~DefaultRoleModel();
	
	virtual DefaultRoleModel & operator = (const DefaultRoleModel& copy);
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	//virtual int PreRun();
	//virtual int ProcessEvent(SimEvent & event);
	//virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
  protected:
	//
};

inline Model * DefaultRoleModelCreator(const QString & strModelName)
{
	return new DefaultRoleModel(strModelName);
}

#endif // DEFAULTROLEMODEL_H
