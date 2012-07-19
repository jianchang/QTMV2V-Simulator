/*
 *  File Name: IncidentModel.h
 *  Written by: Cong Liao
 *  Email: liaocong@seas.upenn.edu
 *  Description: Objects of this class provide relevant information about the incidents,
 *               such as location (longitude & latitude, address), severity, description,
 *               observable region and display corresponding incident objects on the map.
 */

#ifndef _INCIDENTMODEL_H
#define _INCIDENTMODEL_H

#include <qstring.h>

#include "Global.h"
#include "Coords.h"
#include "Model.h"
#include "MapObjects.h"
#include "MapDB.h"

#include "IncidentListVisual.h"
#include "QIncidentDialog.h"

#define INCIDENTMODEL_NAME "IncidentModel"

#define INCIDENTREGIONCOORDSMAX 8

// use default setting for incident region size (meters)
#define INCIDENTREGION_CIRCLE_RADIUS 50
#define INCIDENTREGION_SQUARE_SIDE 50
#define INCIDENTREGION_RECT_WIDTH 50
#define INCIDENTREGION_RECT_HEIGHT 100


typedef enum IncidentListColumnEnum
{
	IncidentListColumnIcon = 0,
	IncidentListColumnSeve = 1,
	IncidentListColumnDescription = 2,
	IncidentListColumnLongitude = 3,
	IncidentListColumnLatitude = 4,
	IncidentListColumnAddress = 5,
}IncidentListColumn;

typedef enum IncidentRegionTypeEnum
{
	IncidentRegionTypeCircle = 0,
	IncidentRegionTypeSquare = 1,
	IncidentRegionTypeRectangle = 3,
}IncidentRegionType;

typedef struct IncidentRegionStruct
{
	IncidentRegionType iRegionType;
	Coords vecCoords[INCIDENTREGIONCOORDSMAX + 1];
}IncidentRegion;

typedef struct IncidentStruct
{
	Coords location;
	IncidentRegion region;
	struct timeval startTime;
	struct timeval durationTime;
	QString severity;
	QString description;
}Incident;


// incident
class IncidentModel : public Model
{
public:
	inline virtual QString GetModelType() const
	{
		return INCIDENTMODEL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(INCIDENTMODEL_NAME) == 0 || (bDescendSufficient && Model::IsModelTypeOf(strModelType, bDescendSufficient));
	}

	IncidentModel(const QString & strModelName = QString::null);
	IncidentModel(const IncidentModel & copy);

	virtual ~IncidentModel();

	virtual IncidentModel & operator = (const IncidentModel & copy);

	//--- model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	virtual int PreRun();
	virtual int ProcessEvent(SimEvent & event);
	virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	virtual int Cleanup();
	//---	
	
	static void GetParams(std::map<QString, ModelParameter> & mapParams);

	inline virtual Coords GetIncidentLocation() const
	{
		return m_iIncident.location;
	}
	inline virtual QString GetIncidentAddress() const
	{
		return m_strPosition;
	}
	inline virtual IncidentRegion GetIncidentRegion() const
	{
		return m_iIncident.region;
	}
	inline virtual struct timeval GetIncidentStartTime() const
	{
		return m_iIncident.startTime;
	}
	inline virtual struct timeval GetIncidentDurationTime() const
	{
		return m_iIncident.durationTime;
	}
	inline virtual QString GetIncidentSeve() const
	{
		return m_iIncident.severity;
	}
	inline virtual QString GetIncidentDescription() const
	{
		return m_iIncident.description;
	}
	inline virtual struct timeval GetTimestamp() const
	{
		return m_tTimestamp;
	}
	inline virtual int GetMapIncidentObjectID() const
	{
		return m_iMapObjectID;
	}
	inline virtual Coords GetCurrentPosition() const
	{
		return m_ptPosition;
	}
	inline virtual unsigned int GetCurrentRecord() const
	{
		return m_iCurrentRecord;
	}
	inline virtual unsigned short GetCRShapePoint() const
	{
		return m_iCRShapePoint;
	}
	inline virtual float GetCRProgress() const
	{
		return m_fCRProgress;
	}
	inline virtual struct timeval GetDelay() const
	{
		return m_tDelay;
	}
	inline virtual bool HasStarted() const
	{
		return m_isStarted;
        }
	inline virtual bool HasExpired() const
	{
		return m_isExpired;
	}
	inline virtual void SetDelay(const struct timeval & tDelay)
	{
		m_tDelay = tDelay;
	}
	inline virtual QString GetSeverity()
	{
		return m_iSeve;
	}
	inline virtual QString GetDescription()
	{
		return m_iDesc;
	}
	inline virtual QString GetRegion()
	{
		return m_iRegion;
	}
	inline virtual void SetRegion(QString region)
	{
		m_iRegion = region;
	}
	inline virtual void SetSeverity(QString seve)
	{	
		m_iSeve = seve;
		m_iIncident.severity = seve;
	}
	inline virtual void SetPosition(QString position)
	{
		m_strPosition = position;
		bool sTa = StringToAddress(m_strPosition, &m_sPosition);
		if(sTa)
		{
			m_ptPosition = m_sPosition.ptCoordinates;
			m_iIncident.location = m_ptPosition;
		}
	}
	inline virtual void SetDescription(QString desc)
	{
		m_iDesc = desc;
		m_iIncident.description = desc;
	}
	inline virtual void SetStartTime(const struct timeval & startTime)
	{
		m_iIncident.startTime = startTime;
	}
	inline virtual void SetDuration(const struct timeval & duration)
	{
		m_iIncident.durationTime = duration;
	}
	inline virtual void SetIncidentMapObjectID(int id)
	{
		m_iMapObjectID = id;
	}
	inline virtual void SetExpired(bool b)
	{
		m_isExpired = b;
	}
	inline virtual void SetStart(bool b)
	{
		m_isStarted = b;
	}
	
	virtual QString GetIncidentListColumnText(IncidentListColumn eColumn) const;

protected:
	// incident information
	Incident m_iIncident;
	
	QString m_iRegion; // incident region
	QString m_iSeve; // severity
	QString m_iDesc; // description
    	Coords m_ptPosition; // longitude & latitude

	// road information where the incident occurs
	unsigned int m_iCurrentRecord;
	unsigned int m_iCRShapePoint;
	float m_fCRProgress;		
	
	struct timeval m_tDelay; // updating interval
	struct timeval m_tTimestamp; // current time
	
	int m_iMapObjectID; // ID of the incident object shown on the map
	
	// incident location
	Address m_sPosition; // address
	QString m_strPosition;

	bool m_isExpired; //incident expires
	bool m_isStarted; //incident starts

};

// incident object
class MapIncidentObject : public MapObject
{
public:
	MapIncidentObject(IncidentModel *pIncident);
	MapIncidentObject(const MapIncidentObject & copy);
	virtual ~MapIncidentObject();

	virtual MapIncidentObject & operator = (const MapIncidentObject & copy);

	inline virtual QString GetDescription() const
	{
		return m_pIncident != NULL ? m_pIncident->GetIncidentListColumnText(IncidentListColumnDescription) : MapObject::GetDescription();
	}

	virtual void DrawObject(const QRect & rBox, QPainter * pPainter, MapObjectState eState) const;
	virtual void DrawObject(MapDrawingSettings * pSettings, MapObjectState eState) const;
	virtual QRect RectVisible(MapDrawingSettings * pSettings) const;

	virtual struct timeval GetLastModifiedTime() const;
	virtual bool isActive() const;

protected:
	   IncidentModel * m_pIncident;

};


inline Model * IncidentModelCreator(const QString & strModelName)
{
	return new IncidentModel(strModelName);
}

#endif
