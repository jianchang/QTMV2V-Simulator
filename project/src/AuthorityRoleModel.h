/*
 * File Name: AuthorityRoleModel.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#ifndef AUTHORITYROLEMODEL_H
#define AUTHORITYROLEMODEL_H

#include "Model.h"
#include "VehicleModel.h"

#define AUTHORITYROLEMODEL_NAME "AuthorityRoleModel"

class AuthorityRoleModel : public RoleModel
{
  public:
	inline virtual QString GetModelType() const
	{
		return AUTHORITYROLEMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(AUTHORITYROLEMODEL_NAME) == 0 || (bDescendSufficient && RoleModel::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	AuthorityRoleModel(const QString& strModelName = QString::null);
	AuthorityRoleModel(const AuthorityRoleModel& copy);
	virtual ~AuthorityRoleModel();
	
	virtual AuthorityRoleModel & operator = (const AuthorityRoleModel& copy);
	
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

inline Model * AuthorityRoleModelCreator(const QString & strModelName)
{
	return new AuthorityRoleModel(strModelName);
}

#endif // AUTHORITYROLEMODEL_H
