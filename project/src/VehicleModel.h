/*
 *  FIle Name: VehicleModel.h
 *  Written by: Cong Liao
 *  Email: liaocong@seas.upenn.edu
 *  Description:
 *
 */

#ifndef VEHICLEMODEL_H
#define VEHICLEMODEL_H

#include "Model.h"
#include "SimModel.h"
#include "IncidentModel.h"
#include "Message.h"

#define ROLEMODEL_NAME "RoleModel"

class RoleModel : public Model
{
  public:
	 inline virtual QString GetModelType() const
	 {
		return ROLEMODEL_NAME;
	 }
	 inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(ROLEMODEL_NAME) == 0 || (bDescendSufficient && Model::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	RoleModel(const QString& strModelName = QString::null);
	RoleModel(const RoleModel & copy);
	virtual ~RoleModel();
	
	virtual RoleModel & operator = (const RoleModel & copy);
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	//virtual int PreRun();
	//virtual int ProcessEvent(SimEvent & event);
	//virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
	inline virtual double GetDetectThreshold()
	{
		return m_detectThresh;
	}
	inline virtual double GetForwardThreshold()
	{
		return m_forwardThresh;
	}
	inline virtual double GetLieThreshold()
	{
		return m_lieThresh;
	}
	inline virtual double GetTrustLowerBound()
	{
		return m_trustLowerBound;
	}
	inline virtual double GetTrustUpperBound()
	{
		return m_trustUpperBound;
	}
	inline virtual void SetDetectThreshold(double detectThresh)
	{
		m_detectThresh = detectThresh;
	}
	inline virtual void SetForwardThreshold(double forwardThresh)
	{
		m_forwardThresh = forwardThresh;
	}
	inline virtual void SetLieThreshold(double lieThresh)
	{
		m_lieThresh = lieThresh;
	}
	inline virtual void SetTrustLowerBound(double trustLowerBound)
	{
		m_trustLowerBound = trustLowerBound;
	}
	inline virtual void SetTrustUpperBound(double trustUpperBound)
	{
		m_trustUpperBound = trustUpperBound;
	}
	
  protected:
	// threshold of detecting an incident
	float m_detectThresh;
	
	// threshold of forwarding an incident message
	float m_forwardThresh;
	
	// threshold of telling a lie
	float m_lieThresh;
	
	// threshold of not believing an incident messages
	float m_trustLowerBound;
	
	// threshold of believing an incident message
	float m_trustUpperBound;
};


#define VEHICLEMODEL_NAME "VehicleModel"

class VehicleModel : public SimModel
{
public:
        inline virtual QString GetModelType() const
        {
		return VEHICLEMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(VEHICLEMODEL_NAME) == 0 || (bDescendSufficient && SimModel::IsModelTypeOf(strModelType, bDescendSufficient));
	}
	
	VehicleModel(const QString& strModelName = QString::null);
	VehicleModel(const VehicleModel & copy);
	virtual ~VehicleModel();
	
	virtual VehicleModel & operator = (const VehicleModel & copy);
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	virtual int PreRun();
	virtual int ProcessEvent(SimEvent & event);
	virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
	// perform incident detection
	virtual void DetectIncidents();
	
	// evaluate the message received from other vehicles
	float evaluateMessage(Packet * msg);
	
  protected:
	// role of the vehicle
	RoleModel * m_pVehicleRole;
	
	// detection range
	float m_detectionRange;
	
	// detected incidents
	std::map<unsigned int, IncidentModel *> m_detectedIncidents; // <IncidentID, IncidentModel>
	//std::map<Coords, IncidentModel *> m_detectedIncidents;
	
	// received messages from other vehicles
	std::map<unsigned int, Packet> m_receivedMessageCache; // <PacketSequenceID, Packet>
	//std::list<Packet> receivedMessageCache;
	
	// vehicle reputation database
	map<in_addr_t, float> m_reputationDB; // <VehicelID, VehicleReputation>
};

inline Model * VehicleModelCreator(const QString & strModelName)
{
	return new VehicleModel(strModelName);
}

#endif // VEHICLEMODEL_H
