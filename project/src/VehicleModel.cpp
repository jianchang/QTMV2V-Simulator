/*
 * File Name: VehicleModel.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#include "VehicleModel.h"
#include "CarRegistry.h"
#include "IncidentRegistry.h"
#include "Simulator.h"
#include "StringHelp.h"

// add role model parameters
#define ROLEMODEL_DETECTTHRESH_PARAM "DETECTION THRESHOLD"
#define ROLEMODEL_DETECTTHRESH_PARAM_DEFAULT "0.0"
#define ROLEMODEL_DETECTTHRESH_PARAM_DESC "DETECTION THRESHOLD -- The threshold of detecting an incident"
#define ROLEMODEL_FORWARDTHRESH_PARAM "FORWARD THRESHOLD"
#define ROLEMODEL_FORWARDTHRESH_PARAM_DEFAULT "0.0"
#define ROLEMODEL_FORWARDTHRESH_PARAM_DESC "FORWARD THRESHOLD -- The threshold of forwarding an incident message"
#define ROLEMODEL_LIETHRESH_PARAM "LIE THRESHOLD"
#define ROLEMODEL_LIETHRESH_PARAM_DEFAULT "0.0"
#define ROLEMODEL_LIETHRESH_PARAM_DESC "LIE THRESHOLD -- The threshold of telling a lie"
#define ROLEMODEL_TRUSTLOWTHRESH_PARAM "TRUST LOWER BOUND"
#define ROLEMODEL_TRUSTLOWTHRESH_PARAM_DEFAULT "0.0"
#define ROLEMODEL_TRUSTLOWTHRESH_PARAM_DESC "TRUST LOWER BOUND -- The threshold of not believing an incident messages"
#define ROLEMODEL_TRUSTUPTHRESH_PARAM "TRUST UPPER BOUND"
#define ROLEMODEL_TRUSTUPTHRESH_PARAM_DEFAULT "0.0"
#define ROLEMODEL_TRUSTUPTHRESH_PARAM_DESC "TRUST UPPER BOUND -- The threshold of believing an incident message"

RoleModel::RoleModel(const QString& strModelName): Model(strModelName), m_detectThresh(0.0), m_forwardThresh(0.0), m_lieThresh(0.0), m_trustLowerBound(0.0), m_trustUpperBound(0.0)
{

}

RoleModel::RoleModel(const RoleModel& copy): Model(copy), m_detectThresh(copy.m_detectThresh), m_forwardThresh(copy.m_forwardThresh), m_lieThresh(copy.m_lieThresh), m_trustLowerBound(copy.m_trustLowerBound), m_trustUpperBound(copy.m_trustUpperBound)
{

}

RoleModel::~RoleModel()
{

}

RoleModel& RoleModel::operator=(const RoleModel& copy)
{
	Model::operator=(copy);
	
	m_detectThresh = copy.m_detectThresh;
	m_forwardThresh = copy.m_forwardThresh;
	m_lieThresh = copy.m_lieThresh;
	m_trustLowerBound = copy.m_trustLowerBound;
	m_trustUpperBound = copy.m_trustUpperBound;
	
	return *this;
}

int RoleModel::Init(const std::map< QString, QString >& mapParams)
{
	QString strValue;
	
	if (Model::Init(mapParams))
		return 1;
	
	strValue = GetParam(mapParams, ROLEMODEL_DETECTTHRESH_PARAM, ROLEMODEL_DETECTTHRESH_PARAM_DEFAULT);
	m_detectThresh = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	strValue = GetParam(mapParams, ROLEMODEL_FORWARDTHRESH_PARAM, ROLEMODEL_FORWARDTHRESH_PARAM_DEFAULT);
	m_forwardThresh = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	strValue = GetParam(mapParams, ROLEMODEL_LIETHRESH_PARAM, ROLEMODEL_LIETHRESH_PARAM_DEFAULT);
	m_lieThresh = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	strValue = GetParam(mapParams,ROLEMODEL_TRUSTLOWTHRESH_PARAM, ROLEMODEL_TRUSTLOWTHRESH_PARAM_DEFAULT);
	m_trustLowerBound = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	strValue = GetParam(mapParams,ROLEMODEL_TRUSTUPTHRESH_PARAM, ROLEMODEL_TRUSTUPTHRESH_PARAM_DEFAULT);
	m_trustUpperBound = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	return 0;
}

int RoleModel::Save(map< QString, QString >& mapParams)
{
	if (Model::Save(mapParams))
		return 1;
	
	mapParams[ROLEMODEL_DETECTTHRESH_PARAM] = QString("%1").arg(m_detectThresh);
	mapParams[ROLEMODEL_FORWARDTHRESH_PARAM] = QString("%1").arg(m_forwardThresh);
	mapParams[ROLEMODEL_LIETHRESH_PARAM] = QString("%1").arg(m_lieThresh);
	mapParams[ROLEMODEL_TRUSTLOWTHRESH_PARAM] = QString("%1").arg(m_trustLowerBound);
	mapParams[ROLEMODEL_TRUSTUPTHRESH_PARAM] = QString("%1").arg(m_trustUpperBound);
	
	return 0;
}

void RoleModel::GetParams(map< QString, ModelParameter >& mapParams)
{
	Model::GetParams(mapParams);
	
	mapParams[ROLEMODEL_DETECTTHRESH_PARAM].strValue = ROLEMODEL_DETECTTHRESH_PARAM_DEFAULT;
	mapParams[ROLEMODEL_DETECTTHRESH_PARAM].strDesc = ROLEMODEL_DETECTTHRESH_PARAM_DESC;
	mapParams[ROLEMODEL_DETECTTHRESH_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
	
	mapParams[ROLEMODEL_FORWARDTHRESH_PARAM].strValue = ROLEMODEL_FORWARDTHRESH_PARAM_DEFAULT;
	mapParams[ROLEMODEL_FORWARDTHRESH_PARAM].strDesc = ROLEMODEL_FORWARDTHRESH_PARAM_DESC;
	mapParams[ROLEMODEL_FORWARDTHRESH_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
	
	mapParams[ROLEMODEL_LIETHRESH_PARAM].strValue = ROLEMODEL_LIETHRESH_PARAM_DEFAULT;
	mapParams[ROLEMODEL_LIETHRESH_PARAM].strDesc = ROLEMODEL_LIETHRESH_PARAM_DESC;
	mapParams[ROLEMODEL_LIETHRESH_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
	
	mapParams[ROLEMODEL_TRUSTLOWTHRESH_PARAM].strValue = ROLEMODEL_TRUSTLOWTHRESH_PARAM_DEFAULT;
	mapParams[ROLEMODEL_TRUSTLOWTHRESH_PARAM].strDesc = ROLEMODEL_TRUSTLOWTHRESH_PARAM_DESC;
	mapParams[ROLEMODEL_TRUSTLOWTHRESH_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
	
	mapParams[ROLEMODEL_TRUSTUPTHRESH_PARAM].strValue = ROLEMODEL_TRUSTUPTHRESH_PARAM_DEFAULT;
	mapParams[ROLEMODEL_TRUSTUPTHRESH_PARAM].strDesc = ROLEMODEL_TRUSTUPTHRESH_PARAM_DESC;
	mapParams[ROLEMODEL_TRUSTUPTHRESH_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
}


// add vehicle model parameters
#define VEHICLEMODEL_ROLE_PARAM "ROLE"
#define VEHICLEMODEL_ROLE_PARAM_DEFAULT "NULL"
#define VEHICLEMODEL_ROLE_PARAM_DESC "ROLE (model) -- The role of the vehicle"
#define VEHICLEMODEL_DETECTRANGE_PARAM "DETECTION RANGE"
#define VEHICLEMODEL_DETECTRANGE_PARAM_DEFAULT "50.0"
#define VEHICLEMODEL_DETECTRANGE_PARAM_DESC "DETECTION RANGE (meters) -- The capability of incident detection of the vehicle"

#define DefaultRange 50.0

VehicleModel::VehicleModel(const QString& strModelName): SimModel(strModelName), m_pVehicleRole(NULL), m_detectionRange(DefaultRange)
{

}

VehicleModel::VehicleModel(const VehicleModel& copy): SimModel(copy), m_pVehicleRole(copy.m_pVehicleRole), m_detectionRange(copy.m_detectionRange)
{

}

VehicleModel::~VehicleModel()
{

}

VehicleModel & VehicleModel::operator =(const VehicleModel & copy)
{
	SimModel::operator=(copy);
	
	m_pVehicleRole = copy.m_pVehicleRole;
	m_detectionRange = copy.m_detectionRange;
	m_detectedIncidents = copy.m_detectedIncidents;
	m_receivedMessageCache = copy.m_receivedMessageCache;
	m_reputationDB = copy.m_reputationDB;
	
	return *this;
}

int VehicleModel::Init(const std::map< QString, QString >& mapParams)
{
	QString strValue;
	Model * pModel;
	
	if (SimModel::Init(mapParams))
		return 1;
	
	strValue = GetParam(mapParams, VEHICLEMODEL_ROLE_PARAM, VEHICLEMODEL_ROLE_PARAM_DEFAULT);
	if (!g_pSimulator->m_ModelMgr.GetModel(strValue, pModel))
		return 2;
	m_pVehicleRole = (RoleModel *)pModel;
	
	strValue = GetParam(mapParams, VEHICLEMODEL_DETECTRANGE_PARAM, VEHICLEMODEL_DETECTRANGE_PARAM_DEFAULT);
	m_detectionRange = ValidateNumber(StringToNumber(strValue), 0., HUGE_VAL);
	
	return 0;
}

int VehicleModel::PreRun()
{
	if (SimModel::PreRun())
		return 1;
	
	return 0;
}

int VehicleModel::ProcessEvent(SimEvent& event)
{
	if (SimModel::ProcessEvent(event))
		return 1;
	
	// process detection event
	
	// process message evaluation event
	
	return 0;
}

int VehicleModel::PostRun()
{
	if (SimModel::PostRun())
		return 1;
	
	return 0;
}

int VehicleModel::Save(map< QString, QString >& mapParams)
{
	if (SimModel::Save(mapParams))
		return 1;
	
	mapParams[VEHICLEMODEL_ROLE_PARAM] = m_pVehicleRole == NULL ? "NULL" : m_pVehicleRole->GetModelName();
	mapParams[VEHICLEMODEL_DETECTRANGE_PARAM] = QString("%1").arg(m_detectionRange);
	
	return 0;
}

void VehicleModel::GetParams(map< QString, ModelParameter >& mapParams)
{
	SimModel::GetParams(mapParams);
	
	mapParams[VEHICLEMODEL_ROLE_PARAM].strValue = VEHICLEMODEL_ROLE_PARAM_DEFAULT;
	mapParams[VEHICLEMODEL_ROLE_PARAM].strDesc = VEHICLEMODEL_ROLE_PARAM_DESC;
	mapParams[VEHICLEMODEL_ROLE_PARAM].eType = (ModelParameterType)(ModelParameterTypeModel | ModelParameterFixed);
	mapParams[VEHICLEMODEL_ROLE_PARAM].strAuxData = ROLEMODEL_NAME;
	
	mapParams[VEHICLEMODEL_DETECTRANGE_PARAM].strValue = VEHICLEMODEL_DETECTRANGE_PARAM_DEFAULT;
	mapParams[VEHICLEMODEL_DETECTRANGE_PARAM].strDesc = VEHICLEMODEL_DETECTRANGE_PARAM_DESC;
	mapParams[VEHICLEMODEL_DETECTRANGE_PARAM].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
}

void VehicleModel::DetectIncidents()
{
	// check if any incident is within detection range
}

float VehicleModel::evaluateMessage(Packet* msg)
{
	// evaluation algorithm
}
