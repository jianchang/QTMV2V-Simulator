/*
 * File Name: IncidentModel.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 */

#include <qpixmap.h>

#include "Global.h"
#include "IncidentModel.h"
#include "IncidentRegistry.h"
#include "Simulator.h"
#include "IncidentListVisual.h"

#include "StringHelp.h"

#define PICTURE "warning16x16.png"

#define INCIDENTMODEL_PARAM_DELAY "DELAY"
#define INCIDENTMODEL_PARAM_DELAY_DEFAULT "0.2"
#define INCIDENTMODEL_PARAM_DELAY_DESC "DELAY (seconds) -- The time interval between updating the incident model."

#define INCIDENTMODEL_LOC_PARAM "POSITION"
#define INCIDENTMODEL_LOC_PARAM_DEFAULT "1100 5th Ave, Pittsburgh, Pennsylvania"
#define INCIDENTMODEL_LOC_PARAM_DESC "POSITION (address) -- The sreet address or intersection specifying where the incident happens."

#define INCIDENTMODEL_START_PARAM "START"
#define INCIDENTMODEL_START_PARAM_DEFAULT "0"
#define INCIDENTMODEL_START_PARAM_DESC "START (time) -- The time when the incident happens."

#define INCIDENTMODEL_DURATION_PARAM "DURATION"
#define INCIDENTMODEL_DURATION_PARAM_DEFAULT "60"
#define INCIDENTMODEL_DURATION_PARAM_DESC "DURATION (time) -- The lifetime of the incident."

#define INCIDENTMODEL_REGION_PARAM "REGION"
#define INCIDENTMODEL_REGION_PARAM_DEFAULT "Circle"
#define INCIDENTMODEL_REGION_PARAM_DESC "REGION (circle/square/rectangle) -- specify the area where the incident can be witnessed by cars."

#define INCIDENTMODEL_SEVE_PARAM "SEVERITY"
#define INCIDENTMODEL_SEVE_PARAM_DEFAULT "Level 5"
#define INCIDENTMODEL_SEVE_PARAM_DESC "Severity (Level 0 - 5) -- specify the severity of the incident, 0 means the least severe and 5 means the most severe."

#define INCIDENTMODEL_DESC_PARAM "DESCRIPTION"
#define INCIDENTMODEL_DESC_PARAM_DEFAULT "Car Crash!"
#define INCIDENTMODEL_DESC_PARAM_DESC "DESCRIPTION -- details of the incident."

#define EVENT_INCIDENTMODEL_UPDATE 592085

IncidentModel::IncidentModel(const QString & strModelName)
: Model(strModelName), m_tDelay(timeval0), m_tTimestamp(timeval0), m_iCurrentRecord((unsigned)-1), m_iCRShapePoint((unsigned)-1), m_fCRProgress(0.f), m_iMapObjectID(-1), m_isExpired(false), m_isStarted(false)
{

}


IncidentModel::IncidentModel(const IncidentModel & copy)
: Model(copy), m_iIncident(copy.m_iIncident), m_iRegion(copy.m_iRegion), m_iSeve(copy.m_iSeve), m_iDesc(copy.m_iDesc), m_ptPosition(copy.m_ptPosition), m_iCurrentRecord(copy.m_iCurrentRecord), m_iCRShapePoint(copy.m_iCRShapePoint), m_fCRProgress(copy.m_fCRProgress), m_tDelay(copy.m_tDelay), m_tTimestamp(copy.m_tTimestamp), m_iMapObjectID(copy.m_iMapObjectID), m_sPosition(copy.m_sPosition), m_strPosition(copy.m_strPosition), m_isExpired(copy.m_isExpired), m_isStarted(copy.m_isStarted)
{
	
}

IncidentModel::~IncidentModel()
{
	
}

IncidentModel & IncidentModel::operator = (const IncidentModel & copy)
{
	Model::operator =(copy);
	
	m_iIncident = copy.m_iIncident;
	m_iRegion = copy.m_iRegion;	
	m_iSeve = copy.m_iSeve;
	m_iDesc = copy.m_iDesc;
    m_ptPosition = copy.m_ptPosition;
	m_iCurrentRecord = copy.m_iCurrentRecord;
	m_iCRShapePoint = copy.m_iCRShapePoint;
	m_fCRProgress = copy.m_fCRProgress;		
	m_tDelay = copy.m_tDelay;
	m_tTimestamp = copy.m_tTimestamp;
	m_iMapObjectID = copy.m_iMapObjectID;
	m_sPosition = copy.m_sPosition;
	m_strPosition = copy.m_strPosition;
	m_isExpired = copy.m_isExpired;
	m_isStarted = copy.m_isStarted;
	
	return *this;
}

int IncidentModel::Init(const std::map<QString, QString> & mapParams)
{
	QString strValue;
	MapIncidentObject * pObject;
	
	if (Model::Init(mapParams))
		return 1;
	
	strValue = GetParam(mapParams, INCIDENTMODEL_PARAM_DELAY, INCIDENTMODEL_PARAM_DELAY_DEFAULT);
	m_tDelay = MakeTime(ValidateNumber(StringToNumber(strValue), 0, HUGE_VAL));
	
	m_strPosition = GetParam(mapParams, INCIDENTMODEL_LOC_PARAM, INCIDENTMODEL_LOC_PARAM_DEFAULT);
	if (!StringToAddress(m_strPosition, &m_sPosition))
	{
		m_sPosition.iRecord = m_sPosition.iVertex = (unsigned)-1;
		return 2;
	}
	m_ptPosition = m_sPosition.ptCoordinates;
	m_iIncident.location = m_ptPosition;
	
	strValue = GetParam(mapParams, INCIDENTMODEL_START_PARAM, INCIDENTMODEL_START_PARAM_DEFAULT);
	m_iIncident.startTime = MakeTime(ValidateNumber(StringToNumber(strValue), 0, HUGE_VAL));
	
	strValue = GetParam(mapParams, INCIDENTMODEL_DURATION_PARAM, INCIDENTMODEL_DURATION_PARAM_DEFAULT);
	m_iIncident.durationTime = MakeTime(ValidateNumber(StringToNumber(strValue), 0, HUGE_VAL));
	
	m_iSeve = GetParam(mapParams, INCIDENTMODEL_SEVE_PARAM, INCIDENTMODEL_SEVE_PARAM_DEFAULT);
	m_iIncident.severity = m_iSeve;
	
	m_iDesc = GetParam(mapParams, INCIDENTMODEL_DESC_PARAM, INCIDENTMODEL_DESC_PARAM_DEFAULT);
	m_iIncident.description = m_iDesc;
	
	m_iRegion = GetParam(mapParams, INCIDENTMODEL_REGION_PARAM, INCIDENTMODEL_REGION_PARAM_DEFAULT);
	//m_iIncident.region = m_iRegion;
	
	m_isExpired = false;
	m_isStarted = false;

	pObject = new MapIncidentObject(this);
	m_iMapObjectID = g_pMapObjects->add(pObject);
	if (m_iMapObjectID == -1)
		delete pObject;
	
	g_pIncidentRegistry->addIncident(this);	
	
	return 0;
}

int IncidentModel::PreRun()
{
	if (Model::PreRun())
			return 1;
			
	m_tTimestamp = timeval0;
	
	if (m_sPosition.iRecord != (unsigned)-1 || m_sPosition.iVertex != (unsigned)-1)
	{
		m_ptPosition= m_sPosition.ptCoordinates;
		m_iIncident.location = m_ptPosition;
		if (!g_pMapDB->AddressToPosition(&m_sPosition,m_iCurrentRecord, m_iCRShapePoint, m_fCRProgress))
		{
			m_iCurrentRecord = (unsigned)-1;
		}
	}
	else
	{
		m_ptPosition.Set(0,0);
		m_iCurrentRecord = (unsigned)-1;
		m_iCRShapePoint = (unsigned)-1;
		m_fCRProgress = 0.f;
	}

	g_pSimulator->m_EventQueue.AddEvent(SimEvent(g_pSimulator->m_tCurrent, EVENT_PRIORITY_HIGHEST, m_strModelName, m_strModelName, EVENT_INCIDENTMODEL_UPDATE));	
	
	return 0;
}

int IncidentModel::ProcessEvent(SimEvent & event)
{
	if (Model::ProcessEvent(event))
		return 1;
			
	switch (event.GetEventID())
	{
		case EVENT_INCIDENTMODEL_UPDATE:
		{	
			m_tTimestamp = event.GetTimestamp();
			
			if (event.GetTimestamp() >= g_pSimulator->m_tStart + m_iIncident.startTime)
			{	
				m_isStarted = true;
				if (g_pSimulator->m_tStart + m_iIncident.startTime + m_iIncident.durationTime <= event.GetTimestamp())
				{
					Cleanup();
					m_isExpired = true;
				}
				else
				{
					m_isExpired = false;
					event.SetTimestamp(event.GetTimestamp() + m_tDelay);
					g_pSimulator->m_EventQueue.AddEvent(event);	
				}
			}
			else
			{	
				m_isStarted = false;
				m_isExpired = false;
				event.SetTimestamp(event.GetTimestamp() + m_tDelay);
				g_pSimulator->m_EventQueue.AddEvent(event);
			}
					
			break;
		}			
		/*case EVENT_INCIDENTMODEL_EXPIRE:
		{
			// delete the incident
			if (m_iMapObjectID > -1)
			{
				std::map<int, MapObject *> * pObjects = g_pMapObjects->acquireLock();
		
				std::map<int, MapObject *>::iterator iterObject = pObjects->find(m_iMapObjectID);
		
				if (iterObject != pObjects->end())
				{
					delete iterObject->second;
					pObjects->erase(iterObject);
				}
				m_iMapObjectID = -1;
				g_pMapObjects->releaseLock();
			}
	
			g_pIncidentRegistry->removeIncident(m_ptPosition);

			break;
		}*/
		default:
			break;
				
	}
	
	return 0;
}

int IncidentModel::Save(std::map<QString, QString> & mapParams)
{
	if (Model::Save(mapParams))
		return 1;
			
	mapParams[INCIDENTMODEL_PARAM_DELAY] = QString("%1").arg(ToDouble(m_tDelay));
	mapParams[INCIDENTMODEL_LOC_PARAM] = m_strPosition;
	mapParams[INCIDENTMODEL_START_PARAM] = QString("%1").arg(ToDouble(m_iIncident.startTime));
	mapParams[INCIDENTMODEL_DURATION_PARAM] = QString("%1").arg(ToDouble(m_iIncident.durationTime));
	mapParams[INCIDENTMODEL_REGION_PARAM] = m_iRegion;
	mapParams[INCIDENTMODEL_SEVE_PARAM] = m_iSeve;
	mapParams[INCIDENTMODEL_DESC_PARAM] = m_iDesc;
	
	return 0;
}

int IncidentModel::PostRun()
{
	if (Model::PostRun())
			return 1;
			
	return 0;
}

int IncidentModel::Cleanup()
{
	if (m_iMapObjectID > -1)
	{
		std::map<int, MapObject *> * pObjects = g_pMapObjects->acquireLock();
		
		std::map<int, MapObject *>::iterator iterObject = pObjects->find(m_iMapObjectID);
		
		if (iterObject != pObjects->end())
		{
			delete iterObject->second;
			pObjects->erase(iterObject);
		}
		m_iMapObjectID = -1;
		g_pMapObjects->releaseLock();
	}
	
	g_pIncidentRegistry->removeIncident(m_ptPosition);
	
	return 0;
}

void IncidentModel::GetParams(std::map<QString, ModelParameter> & mapParams)
{
	Model::GetParams(mapParams);
	
	mapParams[INCIDENTMODEL_PARAM_DELAY].strValue = INCIDENTMODEL_PARAM_DELAY_DEFAULT;
	mapParams[INCIDENTMODEL_PARAM_DELAY].strDesc = INCIDENTMODEL_PARAM_DELAY_DESC;
	mapParams[INCIDENTMODEL_PARAM_DELAY].eType = (ModelParameterType)(ModelParameterTypeFloat | ModelParameterFixed);
	mapParams[INCIDENTMODEL_PARAM_DELAY].strAuxData = QString("%1").arg(5e-2);
	
	mapParams[INCIDENTMODEL_LOC_PARAM].strValue = INCIDENTMODEL_LOC_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_LOC_PARAM].strDesc = INCIDENTMODEL_LOC_PARAM_DESC;
	mapParams[INCIDENTMODEL_LOC_PARAM].eType = ModelParameterTypeAddress;
	
	mapParams[INCIDENTMODEL_START_PARAM].strValue = INCIDENTMODEL_START_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_START_PARAM].strDesc = INCIDENTMODEL_START_PARAM_DESC;
	mapParams[INCIDENTMODEL_START_PARAM].eType = ModelParameterTypeFloat;
	//mapParams[INCIDENTMODEL_START_PARAM].strAuxData = QString("%1").arg(0);
	
	mapParams[INCIDENTMODEL_DURATION_PARAM].strValue = INCIDENTMODEL_DURATION_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_DURATION_PARAM].strDesc = INCIDENTMODEL_DURATION_PARAM_DESC;
	mapParams[INCIDENTMODEL_DURATION_PARAM].eType = ModelParameterTypeFloat;
	//mapParams[INCIDENTMODEL_DURATION_PARAM].strAuxData = QString("%1").arg(0);
	
	mapParams[INCIDENTMODEL_REGION_PARAM].strValue = INCIDENTMODEL_REGION_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_REGION_PARAM].strDesc = INCIDENTMODEL_REGION_PARAM_DESC;
	mapParams[INCIDENTMODEL_REGION_PARAM].eType = ModelParameterTypeRegion;
	
	mapParams[INCIDENTMODEL_SEVE_PARAM].strValue = INCIDENTMODEL_SEVE_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_SEVE_PARAM].strDesc = INCIDENTMODEL_SEVE_PARAM_DESC;
	mapParams[INCIDENTMODEL_SEVE_PARAM].eType = ModelParameterTypeSeve;
	
	mapParams[INCIDENTMODEL_DESC_PARAM].strValue = INCIDENTMODEL_DESC_PARAM_DEFAULT;
	mapParams[INCIDENTMODEL_DESC_PARAM].strDesc = INCIDENTMODEL_DESC_PARAM_DESC;
	mapParams[INCIDENTMODEL_DESC_PARAM].eType = ModelParameterTypeText;
	
}

QString IncidentModel::GetIncidentListColumnText(IncidentListColumn eColumn) const
{
	switch (eColumn)
	{
		case IncidentListColumnSeve:
				return m_isExpired == false && m_isStarted == true ? m_iSeve : "";				
		case IncidentListColumnDescription:
				return m_isExpired == false && m_isStarted == true ? m_iDesc : "";
		case IncidentListColumnLongitude:
				return m_isExpired == false && m_isStarted == true ? DegreesToString(m_ptPosition.m_iLong, 6) : "";
		case IncidentListColumnLatitude:
				return m_isExpired == false && m_isStarted == true ? DegreesToString(m_ptPosition.m_iLat, 6) : "";
		case IncidentListColumnAddress:
				return m_isExpired == false && m_isStarted == true ? m_strPosition : "";
		default:
				return "";
	}
}


#define MAPINCIDENTOBJECT_SQUARE_SIDE 10

MapIncidentObject::MapIncidentObject(IncidentModel * pIncident)
: MapObject(pIncident ? pIncident->GetModelName() : QString::null), m_pIncident(pIncident)
{
	
}

MapIncidentObject::MapIncidentObject(const MapIncidentObject & copy)
: MapObject(copy), m_pIncident(copy.m_pIncident)
{
	
}

MapIncidentObject::~MapIncidentObject()
{
	
}

MapIncidentObject & MapIncidentObject::operator = (const MapIncidentObject & copy)
{
	MapObject::operator =(copy);
	
	m_pIncident = copy.m_pIncident;
	
	return *this;
}

void MapIncidentObject::DrawObject(const QRect & rBox, QPainter * pDC, MapObjectState eState __attribute__((unused)) ) const
{
	if (m_pIncident->HasStarted())
	{
		QString fileName = PICTURE;
		QPoint ptCenter;
		QPixmap pPixmap(PICTURE);
	
		if (m_pIncident == NULL)
			return;
			
		ptCenter = rBox.center();
	
		pDC->drawPixmap(ptCenter, pPixmap);
		//pDC->drawArc();
	}
	
}

void MapIncidentObject::DrawObject(MapDrawingSettings * pSettings, MapObjectState eState __attribute__((unused)) ) const
{
	if (m_pIncident->HasStarted())
	{	
		QString fileName = PICTURE;
		Coords ptPosition;
		QPixmap pPixmap(PICTURE);
		QPoint ptAt;
	
		if (m_pIncident == NULL)
			return;
			
		m_pIncident->m_mutexUpdate.lock();
		ptPosition = m_pIncident->GetCurrentPosition();
		m_pIncident->m_mutexUpdate.unlock();
	
		ptAt = MapLongLatToScreen(pSettings, ptPosition);
	
		pSettings->pMemoryDC->drawPixmap(ptAt, pPixmap);
		//pSetting->pMemoryDC->drawArc();
	}
}

QRect MapIncidentObject::RectVisible(MapDrawingSettings * pSettings) const
{
	Coords ptPosition;
	QRect r;
	QPoint ptAt;
	
	if (m_pIncident == NULL)
		return r;
			
	m_pIncident->m_mutexUpdate.lock();
	ptPosition = m_pIncident->GetCurrentPosition();
	m_pIncident->m_mutexUpdate.unlock();
	
	ptAt = MapLongLatToScreen(pSettings, ptPosition);
	
	r.setRect(ptAt.x() - MAPINCIDENTOBJECT_SQUARE_SIDE / 2, ptAt.y() - MAPINCIDENTOBJECT_SQUARE_SIDE / 2, MAPINCIDENTOBJECT_SQUARE_SIDE, MAPINCIDENTOBJECT_SQUARE_SIDE);

	return r;
}

struct timeval MapIncidentObject::GetLastModifiedTime() const
{
	if (m_pIncident == NULL)
			return timeval0;
	else
			return m_pIncident->GetTimestamp();
}

bool MapIncidentObject::isActive() const
{
	struct timeval tNext = timeval0;
	if (m_pIncident != NULL)
	{
		tNext = m_pIncident->GetTimestamp() + m_pIncident->GetDelay();
		return g_pSimulator->m_tCurrent != timeval0 && tNext >= g_pSimulator->m_tCurrent;
	}
	else
			return false;
}
