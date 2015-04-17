/*
 * FIle Name: RoadSideUnitModel.cpp
 * Written by; Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
*/

#include "RoadSideUnitModel.h"
#include "InfrastructureNodeRegistry.h"
#include "IncidentRegistry.h"
#include "Simulator.h"
#include "StringHelp.h"
#include "CarRegistry.h"
#include "VehicleModel.h"
#include <sstream>

// global variables
std::map<in_addr_t, float> RoadSideUnitModel::m_reputationDB;
std::map<in_addr_t, OpinionStats> RoadSideUnitModel::m_opinionStatsDB;
//std::map<Coords, std::map<in_addr_t, OpinionInfo> > RoadSideUnitModel::m_reportDB;
//std::map<in_addr_t, std::map<Coords, OpinionInfo> > RoadSideUnitModel::m_reportDB;
//std::map<Coords, IncidentStatus> RoadSideUnitModel::m_incidentDB; 
std::map<in_addr_t, std::map<IncidentInfo, OpinionInfo> > RoadSideUnitModel::m_reportDB;
//std::map<IncidentInfo, IncidentStatus> RoadSideUnitModel::m_incidentDB;

// add RSU model parameters

RoadSideUnitModel::RoadSideUnitModel(const QString& strModelName): InfrastructureNodeModel(strModelName), m_lastPrint(timeval0), m_printRole(false)
{

}

RoadSideUnitModel::RoadSideUnitModel(const RoadSideUnitModel& copy): InfrastructureNodeModel(copy), m_lastPrint(copy.m_lastPrint), m_printRole(copy.m_printRole) //m_reportDB(copy.m_reportDB), m_reputationDB(copy.m_reputationDB), m_incidentDB(copy.m_incidentDB),
{

}

RoadSideUnitModel::~RoadSideUnitModel()
{

}

RoadSideUnitModel& RoadSideUnitModel::operator=(const RoadSideUnitModel& copy)
{
	InfrastructureNodeModel::operator=(copy);
	
	//m_reportDB = copy.m_reportDB;
	//m_reputationDB = copy.m_reputationDB;
	//m_incidentDB = copy.m_incidentDB;
	m_lastPrint = copy.m_lastPrint;
	m_printRole = copy.m_printRole;
	m_cnt = copy.m_cnt;
	
	return *this;
}

int RoadSideUnitModel::Init(const std::map< QString, QString >& mapParams)
{
	if (InfrastructureNodeModel::Init(mapParams))
		return 1;
	
	return 0;
}

int RoadSideUnitModel::PreRun()
{
	if (InfrastructureNodeModel::PreRun())
		return 1;
	
	m_cnt = 0;
	/*
	std::map<Coords, IncidentModel *> * pIncidentRegistry;
	std::map<Coords, IncidentModel *>::iterator iterIncident;
	// initialize incidentDB
	if (m_incidentDB.size() == 0)
	{
	    pIncidentRegistry = g_pIncidentRegistry->acquireLock();
	    for (iterIncident = pIncidentRegistry->begin(); iterIncident != pIncidentRegistry->end(); ++iterIncident)
	    {
		m_incidentDB.insert(std::make_pair<Coords, IncidentStatus>(iterIncident->first, Unknown));
	    }
	}
	g_pIncidentRegistry->releaseLock();
	*/
	
	std::map<in_addr_t, CarModel *> * pCarRegistry = g_pCarRegistry->acquireLock();
	std::map<in_addr_t, CarModel *>::iterator iterCar;
	// initialize reputationDB
	if (m_reputationDB.size() == 0)
	{
	    for (iterCar = pCarRegistry->begin(); iterCar != pCarRegistry->end(); ++iterCar)
	    {
		if (iterCar->second->GetCarRole() == Authority)
		    m_reputationDB.insert(std::make_pair<in_addr_t, float>(iterCar->second->GetIPAddress(), 1.0));
		else
		    m_reputationDB.insert(std::make_pair<in_addr_t, float>(iterCar->second->GetIPAddress(), 0.5));
	    }
	}
	// initialize opinionStatsDB
	if (m_opinionStatsDB.size() == 0)
	{
	    for (iterCar = pCarRegistry->begin(); iterCar != pCarRegistry->end(); ++iterCar)
	    {
		if (iterCar->second->GetCarRole() != Authority)
		{
		    OpinionStats os;
		    os.right = 0.5;
		    os.wrong = 0.5;
		    m_opinionStatsDB.insert(std::pair<in_addr_t, OpinionStats>(iterCar->second->GetIPAddress(), os));
		}
		else
		{
		    OpinionStats os;
		    os.right = 0.0;
		    os.wrong = 0.0;
		    m_opinionStatsDB.insert(std::pair<in_addr_t, OpinionStats>(iterCar->second->GetIPAddress(), os));
		}
	    }
	}
	g_pCarRegistry->releaseLock();
	
	m_lastPrint = g_pSimulator->m_tStart;
	  
	return 0;
}

int RoadSideUnitModel::ProcessEvent(SimEvent& event)
{
	if (InfrastructureNodeModel::ProcessEvent(event))
		return 1;
	
	switch (event.GetEventID())
	{
	  case EVENT_CARMODEL_UPDATE:
	  {
	    // try incidentDB update every 10 seconds
	    UpdateIncidentDB();
	    
	    // use the last infrastructure in the list to write reputation to the log file
	    std::map<in_addr_t, InfrastructureNodeModel *> * pNodeRegistry = g_pInfrastructureNodeRegistry->acquireLock();
	    if (pNodeRegistry->rbegin()->second->GetIPAddress() == m_ipNode)
	    {
	       if (ToFloat(g_pSimulator->m_tCurrent - m_lastPrint) >= WRITEREPUTATIONINTERVAL)
	       {
		  if (m_reputationDB.size() != 0)
		  {
		      //g_pLogReputation->LogReputation(QString("\n[Reputation Information %1]\n").arg(QDateTime::currentDateTime(Qt::LocalTime).toString(Qt::LocalDate)));
		      //g_pLogReputation->LogReputation(QString("Car IP\t\tReputation\n"));
		      std::map<in_addr_t, CarModel *> * pCarRegistry = g_pCarRegistry->acquireLock();
		      std::map<in_addr_t, float>::iterator iter;
		      
		      int attackerCnt = 0, authorityCnt = 0, defaultCnt = 0;
		      float attackerRep = 0.0, authorityRep = 0.0, defaultRep = 0.0;
		      for (iter = m_reputationDB.begin(); iter != m_reputationDB.end(); iter++)
		      {
			CarRole cr = pCarRegistry->find(iter->first)->second->GetCarRole();
			switch (cr)
			  {
			    case Attacker:
			    {
			      attackerRep += iter->second;
			      attackerCnt++;
			      break;
			    }
			    case Authority:
			    {
			      authorityRep += iter->second;
			      authorityCnt++;
			      break;
			    }
			    case Default:
			    {
			      defaultRep += iter->second;
			      defaultCnt++;
			      break;
			    }
			    default:
			      break;
			  }
		      }
		      std::ostringstream os1, os2, os3;
		      os1.precision(2);os2.precision(2), os3.precision(2);
		      os1 << attackerRep / attackerCnt;
		      os2 << authorityRep / authorityCnt;
		      os3 << defaultRep / defaultCnt;
		      m_cnt += 2;
		      g_pLogReputation->LogMetric(QString("%1").arg(m_cnt) + "\t");
		      g_pLogReputation->LogMetric(QString(os1.str()) + "\t");
		      g_pLogReputation->LogMetric(QString(os2.str()) + "\t");
		      g_pLogReputation->LogMetric(QString(os3.str()) + "\t");
		      g_pLogReputation->LogMetric("\n");
		      /*
		      if (!m_printRole)
		      {
			for (iter = m_reputationDB.begin(); iter != m_reputationDB.end(); iter ++)
			{
			  CarRole cr = pCarRegistry->find(iter->first)->second->GetCarRole();
			  switch (cr)
			  {
			    case Attacker:
			    {
			      g_pLogReputation->LogMetric("Attacker\t");
			      break;
			    }
			    case Authority:
			    {
			      g_pLogReputation->LogMetric("Authority\t");
			      break;
			    }
			    case Default:
			    {
			      g_pLogReputation->LogMetric("Default\t");
			      break;
			    }
			    default:
			      break;
			  }
			}
			g_pLogReputation->LogMetric("\n");
			m_printRole = true;
		      }
		      for (iter = m_reputationDB.begin(); iter != m_reputationDB.end(); iter ++)
		      {
			//if (pCarRegistry->find(iter->first)->second->GetCarRole() != Authority)
			//{
			    std::ostringstream os;
			    os.precision(2);
			    os << iter->second;
			    g_pLogReputation->LogMetric(QString(os.str()) + "\t");
			//}
		      }
		      g_pLogReputation->LogMetric("\n");
		      */
		      
		      m_lastPrint = g_pSimulator->m_tCurrent;
		      g_pCarRegistry->releaseLock();
		  }
	       }
	    }
	    g_pInfrastructureNodeRegistry->releaseLock();
	    
	    break;
	  }
	  /*
	  case EVENT_CARMODEL_RXMESSAGEBEGIN:
	  {
	    //Packet * pPacket = (Packet *)event.GetEventData();
	    //if (pPacket->m_ePacketType == ptV2I)
	    //    std::cout << "Begin process V2I message by " <<  IPAddressToString(pPacket->m_ipRX) << "\n";
		
	    break;
	  }
	  */
	  case EVENT_CARMODEL_RXMESSAGEEND:
	  {
	    Packet * pPacket = (Packet *)event.GetEventData();
	    //if (pPacket->m_ePacketType == ptV2I)
	    //    std::cout << "Finish process V2V message by " <<  IPAddressToString(pPacket->m_ipRX) << "\n";
		
	    switch (pPacket->m_ePacketType)
	    {
	      case ptV2I:
	      {
		  //std::cout << "V2I message from " + IPAddressToString(pPacket->m_ipTX) + " received by " + IPAddressToString(m_ipNode) << "\n";
			  
		  V2IMessage * v2iMsg = (V2IMessage*)pPacket;
		  std::map<IncidentInfo, std::map<in_addr_t, float> > messages = v2iMsg->m_incidentReports;
		  //std::map<Coords, std::map<in_addr_t, float> > messages = v2iMsg->m_incidentReports;
		  in_addr_t reporter = v2iMsg->m_ipTX;
		  
		  //update reputationDB
		  EvaluateReputation(messages, reporter);
		  
		  // respond to the car
		  I2VMessage newMsg;
		  newMsg.m_ipRX = pPacket->m_ipTX;
		  CreateMessage(&newMsg);
		  SendMessage(&newMsg);
		 
	      }
	      default:
		break;
	    }
	    
	    DestroyPacket(pPacket);
	    break;
	  }
	  default:
	    break;
	}
	
	return 0;
}

int RoadSideUnitModel::Cleanup()
{
	if (InfrastructureNodeModel::Cleanup())
		return 1;
	
	return 0;
}

int RoadSideUnitModel::Save(map< QString, QString >& mapParams)
{
	if (InfrastructureNodeModel::Save(mapParams))
		return 1;
	
	return 0;
}

void RoadSideUnitModel::GetParams(map< QString, ModelParameter >& mapParams)
{
	InfrastructureNodeModel::GetParams(mapParams);
}

void RoadSideUnitModel::EvaluateReputation(std::map<IncidentInfo, std::map<in_addr_t, float> > messages, in_addr_t reporter)
{
    std::map<in_addr_t, std::map<IncidentInfo, OpinionInfo> >::iterator iterReportDB;
    
    std::map<IncidentInfo, std::map<in_addr_t, float> >::iterator iterMsg;
    for (iterMsg = messages.begin(); iterMsg != messages.end(); ++iterMsg)
    {
	IncidentInfo ii = iterMsg->first;
	Coords incidentLocation = ii.location;
	std::map<in_addr_t, float> carOpinion = iterMsg->second;
	
	// update incidentDB
	if (m_incidentDB.find(ii) == m_incidentDB.end())
	{
	    m_incidentDB.insert(std::pair<IncidentInfo, IncidentStatus>(ii, Unknown));
	}
	
	// update reportDB
	std::map<in_addr_t, float>::iterator iterCarOpinion;
        for (iterCarOpinion = carOpinion.begin(); iterCarOpinion != carOpinion.end(); ++iterCarOpinion)
        {
            in_addr_t vehicleID = iterCarOpinion->first;
            float opinion = iterCarOpinion->second;
	    
	    std::vector<in_addr_t> reportedBy;
	    reportedBy.push_back(reporter);
	    OpinionInfo oi;
	    oi.opinion = opinion;
	    oi.reportedBy = reportedBy;
	    oi.counted = false;
	    
	    // a new carID
	    if ((iterReportDB = m_reportDB.find(vehicleID)) == m_reportDB.end())
	    {
		std::map<IncidentInfo, OpinionInfo> incidentOpinionInfo;
		incidentOpinionInfo.insert(std::make_pair<IncidentInfo, OpinionInfo>(ii, oi));
		m_reportDB.insert(std::make_pair<in_addr_t, std::map<IncidentInfo, OpinionInfo> >(vehicleID, incidentOpinionInfo));
	    }
	    else
	    {
		std::map<IncidentInfo, OpinionInfo>::iterator iterIncidentOpinionInfo;
		// a new incident 
		if ((iterIncidentOpinionInfo = (iterReportDB->second).find(ii)) == (iterReportDB->second).end())
		{
		    iterReportDB->second.insert(std::make_pair<IncidentInfo, OpinionInfo>(ii, oi));
		}
		else
		{
		    // currently assume the car always has the same opinion for the same incident
		    // TODO:handle the case that the same car has different opinion regarding the same incident
		    // a new reporter
		    if (find(iterIncidentOpinionInfo->second.reportedBy.begin(), iterIncidentOpinionInfo->second.reportedBy.end(), reporter) == iterIncidentOpinionInfo->second.reportedBy.end())
			iterIncidentOpinionInfo->second.reportedBy.push_back(reporter);
		}
	    }
	}
    }
    
    // update opinion
    for (iterReportDB = m_reportDB.begin(); iterReportDB != m_reportDB.end(); iterReportDB++)
    {
	in_addr_t carID = iterReportDB->first;
	std::map<IncidentInfo, OpinionInfo> incidentOpinionInfo = iterReportDB->second;
	
	std::map<IncidentInfo, OpinionInfo>::iterator iterIncidentOpinionInfo;
	for (iterIncidentOpinionInfo = incidentOpinionInfo.begin(); iterIncidentOpinionInfo != incidentOpinionInfo.end(); ++iterIncidentOpinionInfo)
        {
	    if (!iterIncidentOpinionInfo->second.counted)
	    {
		IncidentInfo ii = iterIncidentOpinionInfo->first;
		float opinion = iterIncidentOpinionInfo->second.opinion;
		
		std::map<IncidentInfo, IncidentStatus>::iterator iterIncidentDB;
		
		if ((iterIncidentDB = m_incidentDB.find(ii)) != m_incidentDB.end())
		{
		    std::map<in_addr_t, OpinionStats>::iterator iterStats;
		    if (iterIncidentDB->second == True)
		    {
			if ((iterStats = m_opinionStatsDB.find(carID)) != m_opinionStatsDB.end())
			{
			    iterStats->second.right += opinion;
			}
			/*else
			{
			    OpinionStats os;
			    os.right = 0.5 + opinion;
			    os.wrong = 0.5;
			    m_opinionStatsDB.insert(std::pair<in_addr_t, OpinionStats>(carID, os));
			}*/
			iterIncidentOpinionInfo->second.counted = true;
		    }
		    else if (iterIncidentDB->second == False)
		    {
			if ((iterStats = m_opinionStatsDB.find(carID)) != m_opinionStatsDB.end())
			{
			    iterStats->second.wrong += opinion;
			}
			/*else
			{
			    OpinionStats os;
			    os.right = 0.5;
			    os.wrong = 0.5 + opinion;
			    m_opinionStatsDB.insert(std::pair<in_addr_t, OpinionStats>(carID, os));
			}*/
			iterIncidentOpinionInfo->second.counted = true;
		    }
		}
		/*else
		{
		   m_incidentDB.insert(std::pair<IncidentInfo, IncidentStatus>(ii, Unknown));
		}*/
	    }
	 }
	 
	 // update reputation
	 std::map<in_addr_t, CarModel *> * pCarRegistry = g_pCarRegistry->acquireLock();
	 std::map<in_addr_t, OpinionStats>::iterator iterStats;
	 if ((iterStats = m_opinionStatsDB.find(carID)) != m_opinionStatsDB.end())
	 {
	    if ((iterStats->second.right != 0 || iterStats->second.wrong != 0) && pCarRegistry->find(carID)->second->GetCarRole() != Authority)
	    {
		float reputation = iterStats->second.right / (iterStats->second.right + iterStats->second.wrong);
		m_reputationDB.find(carID)->second = reputation;
	    }
	 }
	 g_pCarRegistry->releaseLock();
    }
    
}

/*
void RoadSideUnitModel::EvaluateReputation(std::map<Coords, std::map<in_addr_t, float> > messages, in_addr_t reporter)
{
    // evaluation algorithm
    
    //std::map<Coords, std;;map<in_addr_t, OpinionInfo> >::iterator iter;
    //std::map<in_addr_t, std::map<Coords, float> > carIncidentOpinion; // <vehicleIP, <incident coords, opinion> >
    //std::map<in_addr_t, std::map<Coords, float> >::iterator iterCarIncidentOpinon;
    std::map<in_addr_t, std::map<Coords, OpinionInfo> >::iterator iterReportDB;
    
    std::map<Coords, std::map<in_addr_t, float> >::iterator iterMsg;
    for (iterMsg = messages.begin(); iterMsg != messages.end(); ++iterMsg)
    {
	Coords incidentLocation = iterMsg->first;
	std::map<in_addr_t, float> carOpinion = iterMsg->second;
	
	std::map<in_addr_t, float>::iterator iterCarOpinion;
        for (iterCarOpinion = carOpinion.begin(); iterCarOpinion != carOpinion.end(); ++iterCarOpinion)
        {
            in_addr_t vehicleID = iterCarOpinion->first;
            float opinion = iterCarOpinion->second;
	    
	    std::vector<in_addr_t> reportedBy;
	    reportedBy.push_back(reporter);
	    OpinionInfo oi;
	    oi.opinion = opinion;
	    oi.reportedBy = reportedBy;
	    
	    // a new carID
	    if ((iterReportDB = m_reportDB.find(vehicleID)) == m_reportDB.end())
	    {
		std::map<Coords, OpinionInfo> incidentOpinionInfo;
		incidentOpinionInfo.insert(std::make_pair<Coords, OpinionInfo>(incidentLocation, oi));
		m_reportDB.insert(std::make_pair<in_addr_t, std::map<Coords, OpinionInfo> >(vehicleID, incidentOpinionInfo));
	    }
	    else
	    {
		std::map<Coords, OpinionInfo>::iterator iterIncidentOpinionInfo;
		// a new incident 
		if ((iterIncidentOpinionInfo = (iterReportDB->second).find(incidentLocation)) == (iterReportDB->second).end())
		{
		    iterReportDB->second.insert(std::make_pair<Coords, OpinionInfo>(incidentLocation, oi));
		}
		else
		{
		    // currently assume the car always has the same opinion for the same incident
		    // TODO:handle the case that the same car has different opinion regarding the same incident
		    // a new reporter
		    if (find(iterIncidentOpinionInfo->second.reportedBy.begin(), iterIncidentOpinionInfo->second.reportedBy.end(), reporter) == iterIncidentOpinionInfo->second.reportedBy.end())
			iterIncidentOpinionInfo->second.reportedBy.push_back(reporter);
		}
	    }
	}
    }

   // compute reputation
    
    for (iterReportDB = m_reportDB.begin(); iterReportDB != m_reportDB.end(); iterReportDB++)
    {
	in_addr_t carID = iterReportDB->first;
        std::map<Coords, OpinionInfo> incidentOpinionInfo = iterReportDB->second;
        //int num = 0;
	float sumRight = 0.5;
	float sumWrong = 0.5;
	
	std::map<Coords, OpinionInfo>::iterator iterIncidentOpinionInfo;
	for (iterIncidentOpinionInfo = incidentOpinionInfo.begin(); iterIncidentOpinionInfo != incidentOpinionInfo.end(); ++iterIncidentOpinionInfo)
        {
            //unsigned int incidentID = iterIncidentOpinion->first;
	    Coords incidentLocation = iterIncidentOpinionInfo->first;
            float opinion = iterIncidentOpinionInfo->second.opinion;
	    
 	    std::map<Coords, IncidentStatus>::iterator iterIncidentDB;
	    std::map<Coords, FakeIncident>::iterator iterFakeIncident;
	    
	    if ((iterIncidentDB = m_incidentDB.find(incidentLocation)) != m_incidentDB.end())
	    {
		if (iterIncidentDB->second == True)
		{
		    sumRight += opinion;
		}
	    }
	    else
	    {
		//if ((iterFakeIncident = pFakeIncident->find(incidentLocation)) != pFakeIncident->end())
		//{
		//    if (iterFakeIncident->second.confirmed == True)
		//    {
			sumWrong += opinion;
		//    }
		//}
	    }
	 }
	 if (sumRight + sumWrong != 0.0)
	 {
	    float reputation = sumRight / (sumRight + sumWrong);
	    //float reputation = (float)num / incidentOpinionInfo.size();
	    std::map<in_addr_t, float>::iterator iterReputationDB;
	    if ((iterReputationDB = m_reputationDB.find(carID)) == m_reputationDB.end())
		m_reputationDB.insert(make_pair<in_addr_t, float>(carID, reputation));
	    else
	    {
		// update the reputation
		m_reputationDB.erase(iterReputationDB);
		m_reputationDB.insert(make_pair<in_addr_t, float>(carID, reputation));
	    }
	 }
    }
}
*/
    
void RoadSideUnitModel::SendMessage(const Packet * msg)
{
    // send I2V message to the vehicle who has sent reputation request
    std::vector<CarModel *> vecCars;
    unsigned int iBytesPerSec = GetTXRate();
    struct timeval tTransmit = iBytesPerSec > 0 ? MakeTime((double)msg->GetLength() / iBytesPerSec) : timeval0;
    unsigned int i;
    Packet * newMsg = msg->clone();

    g_pCarRegistry->acquireLock();
    g_pCarRegistry->GetLocalCars(vecCars);

    for (i = 0; i < vecCars.size(); i++)
    {
	 if (vecCars[i]->GetIPAddress() == msg->m_ipRX)
	 {
		newMsg->m_ipRX = vecCars[i]->GetIPAddress();
		newMsg->m_tRX = newMsg->m_tTX + tTransmit;
		newMsg->m_iRSSI = PACKET_RSSI_UNAVAILABLE;
		newMsg->m_iSNR = PACKET_SNR_UNAVAILABLE;
		((VehicleModel*)vecCars[i])->RecvMessage(newMsg);
		break;
	 }
    }
    g_pCarRegistry->releaseLock();
    DestroyPacket(newMsg);
}

bool RoadSideUnitModel::RecvMessage(Packet * msg)
{
  if (InfrastructureNodeModel::ReceivePacket(msg))
      return true;
  else
      return false;
  /*
  std::map< unsigned int, std::map<in_addr_t, float> > messages = ((V2IMessage*)msg)->m_incidentReports;
  //update reputationDB
  std::map<in_addr_t, float> reputation = EvaluateReputation(messages);
  SetReputationDB(reputation);
  
  V2IMessage newMsg;
  newMsg.m_ipRX = msg->m_ipTX;
  CreateMessage(&newMsg);
  SendMessage(&newMsg);
  
  return true;
  */
}

void RoadSideUnitModel::CreateMessage(Packet* msg)
{
  // create I2V message
  ((I2VMessage*)msg)->m_ID.srcID.iSeqNumber = GetNextSequenceNumber();
  ((I2VMessage*)msg)->m_ID.srcID.ipCar = m_ipNode;
  ((I2VMessage*)msg)->m_ID.iRXSeqNumber = (unsigned int)-1;
  ((I2VMessage*)msg)->m_ptTXPosition = m_ptPosition;
  ((I2VMessage*)msg)->m_ipTX = m_ipNode;
  //((I2VMessage*)msg)->m_ipRX = 0;
  ((I2VMessage*)msg)->m_tTX = GetCurrentTime() + MakeTime(RandDouble(0., ToDouble(m_tDelay)));
  ((I2VMessage*)msg)->m_tRX = msg->m_tTX;
  ((I2VMessage*)msg)->m_iRSSI = PACKET_RSSI_UNAVAILABLE;
  ((I2VMessage*)msg)->m_iSNR = PACKET_SNR_UNAVAILABLE;
  ((I2VMessage*)msg)->m_carReputation = m_reputationDB;
}

void RoadSideUnitModel::UpdateIncidentDB()
{
  //m_incidentDB.clear();
  
  //std::map<Coords, IncidentModel *> * pIncidentRegistry;
  //std::map<Coords, IncidentModel *>::iterator iterIncident;
  std::map<IncidentInfo, IncidentStatus>::iterator iter;
  
  //pIncidentRegistry = g_pIncidentRegistry->acquireLock();
  std::map<Coords, struct timeval> * incidentHistory = g_pIncidentRegistry->GetIncidentHistory();
  for (iter = m_incidentDB.begin(); iter != m_incidentDB.end(); iter++)
  {
      if (iter->second == Unknown)
      {
	  if (ToFloat(g_pSimulator->m_tCurrent - iter->first.reportTime) >= INCIDENTUPDATEINTERVAL)
	  {
	      //if ((iterIncident = pIncidentRegistry->find(iter->first.location)) != pIncidentRegistry->end())
	      if (incidentHistory->find(iter->first.location) != incidentHistory->end())
	      {
		  iter->second = True;
	      }
	      else
	      {
		  iter->second = False;
	      }
	  }
      }
  }
 
  //g_pIncidentRegistry->releaseLock();
  
  /*
  std::map<Coords, IncidentModel *> * pIncidentRegistry;
  std::map<Coords, IncidentModel *>::iterator iterIncident;
  
  pIncidentRegistry = g_pIncidentRegistry->acquireLock();
  if (pIncidentRegistry->size() != 0)
  {
      for (iterIncident = pIncidentRegistry->begin(); iterIncident != pIncidentRegistry->end(); ++iterIncident)
      {
	  if (ToFloat(g_pSimulator->m_tCurrent - g_pSimulator->m_tStart - iterIncident->second->GetIncidentStartTime()) >= INCIDENTUPDATEINTERVAL)
	  {
	      if (g_pSimulator->m_tStart + iterIncident->second->GetIncidentStartTime() + iterIncident->second->GetIncidentDurationTime() > g_pSimulator->m_tCurrent)
	      {
		  std::map<Coords, IncidentStatus>::iterator it = m_incidentDB.find(iterIncident->first);
		  m_incidentDB.erase(it);
		  m_incidentDB.insert(std::make_pair<Coords, IncidentStatus>(iterIncident->first, True));
	      }
	  }
      }
  }
  g_pIncidentRegistry->releaseLock();
  */
  
  /*std::map<Coords, FakeIncident> * pFakeIncident = g_pIncidentRegistry->GetFakeIncidents();
  std::map<Coords, FakeIncident>::iterator iterFakeIncident;
  for (iterFakeIncident = pFakeIncident->begin(); iterFakeIncident != pFakeIncident->end(); iterFakeIncident++)
  {
      if (ToFloat(g_pSimulator->m_tCurrent - iterFakeIncident->second.time) >= INCIDENTUPDATEINTERVAL/2)
      {
	  Coords loc = iterFakeIncident->first;
	  FakeIncident fi;
	  fi.time = iterFakeIncident->second.time;
	  fi.confirmed = true;
	  pFakeIncident->erase(iterFakeIncident);
	  pFakeIncident->insert(std::make_pair<Coords, FakeIncident>(loc,fi));
      }
  }*/
}
