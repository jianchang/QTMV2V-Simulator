/*
 * File Name: AttackerRoleModel.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#include "AttackerRoleModel.h"
#include "Simulator.h"
#include "StringHelp.h"

// add model parameters
#define ATTACKERROLEMODEL_LIEFREQUENCY_PARAM "LIE FREQUENCY"
#define ATTACKERROLEMODEL_LIEFREQUENCY_PARAM_DEFAULT "0.0"
#define ATTACKERROLEMODEL_LIEFREQUENCY_PARAM_DESC "LIE FREQUENCY -- The interval of sending a false message"

AttackerRoleModel::AttackerRoleModel(const QString& strModelName): RoleModel(strModelName), m_lieFrequency(timeval0)
{

}

AttackerRoleModel::AttackerRoleModel(const AttackerRoleModel& copy): RoleModel(copy), m_lieFrequency(copy.m_lieFrequency)
{

}

AttackerRoleModel::~AttackerRoleModel()
{

}

AttackerRoleModel & AttackerRoleModel::operator =(const AttackerRoleModel & copy)
{
	RoleModel::operator=(copy);
	
	m_lieFrequency = copy.m_lieFrequency;
	
	return *this;
}

int AttackerRoleModel::Init(const std::map< QString, QString >& mapParams)
{
	QString strValue;

	if (RoleModel::Init(mapParams))
		return 1;
	
	strValue = GetParam(mapParams, ATTACKERROLEMODEL_LIEFREQUENCY_PARAM, ATTACKERROLEMODEL_LIEFREQUENCY_PARAM_DEFAULT);
	m_lieFrequency = MakeTime(ValidateNumber(StringToNumber(strValue), 0, HUGE_VAL));;
	
	return 0;
}

int AttackerRoleModel::ProcessEvent(SimEvent& event)
{
    return Model::ProcessEvent(event);
}

int AttackerRoleModel::Save(map< QString, QString >& mapParams)
{
	if (RoleModel::Save(mapParams))
		return 1;
	
	mapParams[ATTACKERROLEMODEL_LIEFREQUENCY_PARAM] = QString("%1").arg(ToDouble(m_lieFrequency));
	
	return 0;
}

void AttackerRoleModel::GetParams(map< QString, ModelParameter >& mapParams)
{
	RoleModel::GetParams(mapParams);
	
	mapParams[ATTACKERROLEMODEL_LIEFREQUENCY_PARAM].strValue = ATTACKERROLEMODEL_LIEFREQUENCY_PARAM_DEFAULT;
	mapParams[ATTACKERROLEMODEL_LIEFREQUENCY_PARAM].strDesc = ATTACKERROLEMODEL_LIEFREQUENCY_PARAM_DESC;
	mapParams[ATTACKERROLEMODEL_LIEFREQUENCY_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
}

void AttackerRoleModel::falsifyMessage(Packet* msg)
{

}
