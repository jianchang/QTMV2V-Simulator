/*
 * File Name: IncidentListVisual.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description: Object of this class will display all the incidents in a table list
 *              and keep updating as incidents start or expire.
 */

#ifndef _INCIDENTLISTVISUAL_H
#define _INCIDENTLISTVISUAL_H

#include "TableVisualizer.h"
#include "Coords.h"
#include "Global.h"

#include <qdragobject.h>

#define INCIDENTLISTVISUAL_NAME "IncidentListVisual"

class QPopupMenu;

class IncidentListVisual : public TableVisualizer
{
public:
	inline virtual QString GetModelType() const
	{
		return INCIDENTLISTVISUAL_NAME;
	}
	inline virtual bool IsModelTypeOf(const QString & strModelType, bool bDescendSufficient = true) const
	{
		return strModelType.compare(INCIDENTLISTVISUAL_NAME) == 0 || (bDescendSufficient && TableVisualizer::IsModelTypeOf(strModelType, bDescendSufficient));
	}

	IncidentListVisual(const QString & strModelName = QString::null);
	IncidentListVisual(const IncidentListVisual & copy);
	virtual ~IncidentListVisual();

	virtual IncidentListVisual & operator = (const IncidentListVisual & copy);
	
	//--- model cycle
	virtual int Init(const std::map<QString, QString> & mapParams);
	virtual int ProcessEvent(SimEvent & event);
	virtual int PostRun();
	virtual int Save(std::map<QString, QString> & mapParams);
	virtual int Cleanup();
	//---

	virtual void tableContextMenuRequested(int row, int col, const QPoint & pos);
	static void GetParams(std::map<QString, ModelParameter> & mapParams);
	
	// update the incident table list
	virtual void UpdateIncidentTable();

	std::map<Coords, int>m_mapIncidentObjectsToRows;

protected:
	QPopupMenu * m_pRightClickMenu;

};

QDragObject * IncidentListVisualDragObjectCreator(TableVisualizer * pTableVisualizer);

inline Model * IncidentListVisualCreator(const QString & strModelName)
{
	return new IncidentListVisual(strModelName);
}

#endif
