/*
 * File Name: AttackerModel.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#ifndef ATTACKERROLEMODEL_H
#define ATTACKERROLEMODEL_H

#include "Model.h"
#include "VehicleModel.h"

#define ATTACKERROLEMODEL_NAME "AttackerRoleModel"

class AttackerRoleModel : public RoleModel
{
  public:
	inline virtual QString GetModelType() const
	{
		return ATTACKERROLEMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(ATTACKERROLEMODEL_NAME) == 0 || (bDescendSufficient && RoleModel::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	AttackerRoleModel(const QString& strModelName = QString::null);
	AttackerRoleModel(const AttackerRoleModel& copy);
	virtual ~AttackerRoleModel();
	
	virtual AttackerRoleModel & operator = (const AttackerRoleModel& copy);
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	//virtual int PreRun();
	virtual int ProcessEvent(SimEvent & event);
	//virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
	// create falsified message periodically
	void falsifyMessage(Packet * msg);
	
	inline virtual struct timeval GetLieFrequency()
	{
		return m_lieFrequency;
	}
	inline virtual void SetLieFrequency(struct timeval frequency)
	{
		m_lieFrequency = frequency;
	}
	
  protected:
	// frequency of sending falsified message
	struct timeval m_lieFrequency;
	
};

inline Model * AttackerRoleModelCreator(const QString & strModelName)
{
	return new AttackerRoleModel(strModelName);
}

#endif // ATTACKERROLEMODEL_H
