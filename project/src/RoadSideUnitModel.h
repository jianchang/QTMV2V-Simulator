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
#include "InfoExchange.h"
#include "Logger.h"

#define ROADSIDEUNITMODEL_NAME "RoadSideUnitModel"

// 5 min --- the period before the truth of a reported incident is revealed by the infrastructures 
#define INCIDENTUPDATEINTERVAL 300.0
// incidentDB update interval
#define UPDATETIME 10.0

// write reputation to log.txt
#define WRITEREPUTATIONINTERVAL 120.0 // 2min

/*typedef enum IncidentStatusEnum
{
    True = 0,
    False = 1,
    Unknown = 2,
} IncidentStatus;

/typedef struct OpinionInfoStruct
{
    float opinion;
    std::vector<in_addr_t> reportedBy;
    bool counted; // the opinion of a specific incident has been counted or not
    
} OpinionInfo;

typedef struct OpinionStatsStrust
{
    float right;
    float wrong;
}OpinionStats;*/

class RoadSideUnitModel : public InfrastructureNodeModel
{
  public:
	inline virtual QString GetModelType() const
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
	
	/*inline virtual std::map<in_addr_t, float> GetReputationDB()
	{
	    return m_reputationDB;
	}
	inline virtual std::map<unsigned int, std::map<in_addr_t, float> > GetReportDB()
	{
	    return m_reportDB;
	}
	inline virtual void SetReputationDB(std::map<in_addr_t, float> reputation)
	{
	    m_reputationDB = reputation;
	}
	inline virtual void SetReportMsgs(std::map<unsigned int, std::map<in_addr_t, float> > reports)
	{
	    m_reportDB = reports;
	}*/
	
	// model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	virtual int PreRun();
	virtual int ProcessEvent(SimEvent & event);
	virtual int Save(std::map<QString, QString> & mapParams);
	virtual int Cleanup();
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
	virtual void CreateMessage(Packet * msg);
	virtual void SendMessage(const Packet * msg);
	virtual bool RecvMessage(Packet * msg);
	
	// update m_incidentDB
	virtual void UpdateIncidentDB();
	
	// update m_reportDB & m_reputationDB
	// evaluate vehicle reputation based on the message received from vehicles 
	//static virtual std::map<in_addr_t, float> EvaluateReputation(std::map<unsigned int, std::map<in_addr_t, float> > messages);
	//void EvaluateReputation(std::map<Coords, std::map<in_addr_t, float> > messages, in_addr_t reporter);
	void EvaluateReputation(std::map<IncidentInfo, std::map<in_addr_t, float> > messages, in_addr_t reporter);
	
	/*inline virtual std::map<IncidentInfo, IncidentStatus> * GetIncidentDB() const
	{
	    return &m_incidentDB;
	}*/
	
  protected:
	// static variable shared by all RoadSideUnitModel objects
	// reputation database
	static std::map<in_addr_t, float> m_reputationDB; //map<carID, reputation>
	static std::map<in_addr_t, OpinionStats> m_opinionStatsDB;
	
	// received messages from vehicles
	//map<incident coords, <carID, OpinionInfo> >
	//static std::map<Coords, std::map<in_addr_t, OpinionInfo> > m_reportDB;
	// map<carID, map<incident coords, opinino> >
	//static std::map<in_addr_t, std::map<Coords, OpinionInfo> > m_reportDB;
	static std::map<in_addr_t, std::map<IncidentInfo, OpinionInfo> > m_reportDB;
	
	// incidentDB that stores the ground truth of every incidentDB
	//static std::map<Coords, IncidentStatus> m_incidentDB; // <incident coords, ground truth>
	//static std::map<IncidentInfo, IncidentStatus> m_incidentDB;
	
	struct timeval m_lastPrint; // last time to update incidentDB
	bool m_printRole;
	int m_cnt; // counter of writing to reputation file
};

inline Model * RoadSideUnitModelCreator(const QString & strModelName)
{
	return new RoadSideUnitModel(strModelName);
}

#endif // ROADSIDEUNITMODEL_H
