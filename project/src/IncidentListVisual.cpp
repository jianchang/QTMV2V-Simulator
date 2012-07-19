/*
 * File Name: IncidentListVisual.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 */

#include <qpopupmenu.h>
#include <qradiobutton.h>
#include <qlistbox.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qapplication.h>

#include "IncidentModel.h"
#include "IncidentListVisual.h"
#include "IncidentRegistry.h"
#include "QTableVisualizer.h"
#include "QMapObjectTableItem.h"
#include "QIncidentDialog.h"
#include "MainWindow.h"
#include "StringHelp.h"

IncidentListVisual::IncidentListVisual(const QString & strModelName) : TableVisualizer(strModelName)
{

}

IncidentListVisual::IncidentListVisual(const IncidentListVisual & copy) : TableVisualizer(copy), m_mapIncidentObjectsToRows(copy.m_mapIncidentObjectsToRows)
{

}

IncidentListVisual::~IncidentListVisual()
{

}

IncidentListVisual & IncidentListVisual::operator = (const IncidentListVisual & copy)
{
	TableVisualizer::operator = (copy);
	m_mapIncidentObjectsToRows = copy.m_mapIncidentObjectsToRows;
	return *this;
}

// update
void IncidentListVisual::UpdateIncidentTable()
{
	std::map<Coords, IncidentModel *> * pIncidentRegistry;
	std::map<Coords, IncidentModel *>::iterator iterObject;
	std::map<int, MapObject *> * pMapObjects;
	std::map<int, MapObject *>::iterator iterMapObject;
	std::pair<std::map<Coords, int>::iterator, bool> pairIncidentObjectRow;
	std::vector<bool>vecUpdated;
	int i;
	QDraggingTable * pTable;
	
	if (m_pWidget != NULL && (pTable = ((QTableVisualizer *)m_pWidget)->m_pTable) != NULL)
	{
		vecUpdated.resize(pTable->numRows());
		for (i = 0; i< pTable->numRows(); i++)
		{
			vecUpdated[i] = false;
		}
		
		pMapObjects = g_pMapObjects->acquireLock();
		pIncidentRegistry = g_pIncidentRegistry->acquireLock();

		for (iterObject = pIncidentRegistry->begin();iterObject != pIncidentRegistry->end(); ++iterObject)
		{	
			//if (iterObject->second->HasExpired() && iterObject->second->HasStarted() || !iterObject->second->HasExpired() && !iterObject->second->HasStarted())
			//	continue;
			if (!iterObject->second->HasExpired() && iterObject->second->HasStarted())
			{
				pairIncidentObjectRow = m_mapIncidentObjectsToRows.insert(std::pair<Coords, int>(iterObject->first, pTable->numRows()));
				//pTable->setRowHeight(pairIncidentObjectRow.first->second, 30);
				if (pairIncidentObjectRow.second)
				{
					pTable->insertRows(pairIncidentObjectRow.first->second);
					pTable->setItem(pairIncidentObjectRow.first->second, 0, new QMapObjectTableItem(NULL, QTableItem::Never, iterObject->second == NULL ? -1 : iterObject->second->GetMapIncidentObjectID()));
				}
				else
				{
					vecUpdated[pairIncidentObjectRow.first->second] = true;
					((QMapObjectTableItem*)pTable->item(pairIncidentObjectRow.first->second, 0))->SetID(iterObject->second == NULL ? -1 : iterObject->second->GetMapIncidentObjectID());
					pTable->updateCell(pairIncidentObjectRow.first->second, 0);
				}
	
				// update data for this row
				for (i = 1; i < pTable->numCols(); i++)
				{
					pTable->setText(pairIncidentObjectRow.first->second, i, iterObject->second == NULL ? "" : iterObject->second->GetIncidentListColumnText((IncidentListColumn)i));
				}
			}
		}
		g_pIncidentRegistry->releaseLock();
		g_pMapObjects->releaseLock();
		
		for (i = 0; i < (signed)vecUpdated.size(); i++)
		{
			if (!vecUpdated[i])
			{
				pTable->removeRow(i);
				std::map<Coords, int>::iterator iterObjectRow = m_mapIncidentObjectsToRows.begin();
				while (iterObjectRow != m_mapIncidentObjectsToRows.end()) {
					if (iterObjectRow->second == i)
					{
						std::map<Coords, int>::iterator iterTemp = iterObjectRow;
						++iterObjectRow;
						m_mapIncidentObjectsToRows.erase(iterTemp);
						continue;
					}
	
					if (iterObjectRow->second > i)
						iterObjectRow->second--;
				}
			}
		}
	}
	
}

int IncidentListVisual::Init(const std::map<QString, QString> & mapParams)
{
	if (TableVisualizer::Init(mapParams))
		return 1;

	QDraggingTable * pTable = ((QTableVisualizer *)m_pWidget)->m_pTable;

	pTable->setNumCols(6);

	QHeader * pHHeader = pTable->horizontalHeader();
	pHHeader->setMovingEnabled(false);
	pHHeader->setLabel(0, "Incident");
	pTable->setColumnWidth(0, 60);
	pHHeader->setLabel(1, "Severity");
	pTable->setColumnWidth(1, 80);
	pHHeader->setLabel(2, "Description");
	pTable->setColumnWidth(2, 100);
	pHHeader->setLabel(3, "Longitude");
	pTable->setColumnWidth(3, 100);
	pHHeader->setLabel(4, "Latitude");
	pTable->setColumnWidth(4, 100);
	pHHeader->setLabel(5, "Address");
	pTable->setColumnWidth(5, 300);

	pTable->verticalHeader()->hide();
	pTable->setColumnMovingEnabled(false);
	pTable->setRowMovingEnabled(false);
	pTable->setFocusStyle(QTable::FollowStyle);
	pTable->setLeftMargin(0);
	pTable->setReadOnly(true);
	pTable->setSelectionMode(QTable::SingleRow);
	pTable->setShowGrid(true);
	pTable->setSorting(true);
	pTable->SetDragObjectCreator(IncidentListVisualDragObjectCreator, this);
	pTable->setDragEnabled(true);
	m_pRightClickMenu = new QPopupMenu(pTable);
	m_pRightClickMenu->insertItem("Add new incident...", 0);

	UpdateIncidentTable();

	return 0;
}

int IncidentListVisual::ProcessEvent(SimEvent & event)
{
	if (TableVisualizer::ProcessEvent(event))
		return 1;
	
	switch (event.GetEventID())
	{
		case EVENT_VISUALIZER_UPDATE:
			UpdateIncidentTable();
			break;
		default:
			break;
	}

	return 0;
}

int IncidentListVisual::PostRun()
{
	if (TableVisualizer::PostRun())
		return 1;
	
	UpdateIncidentTable();

	return 0;
}

int IncidentListVisual::Save(std::map<QString, QString> & mapParams)
{
	if (TableVisualizer::Save(mapParams))
		return 1;

	return 0;
}

int IncidentListVisual::Cleanup()
{
	QDraggingTable * pTable = m_pWidget == NULL ? NULL : ((QTableVisualizer *)m_pWidget)->m_pTable;

	if (pTable != NULL)
		pTable->setNumRows(0);

	if (TableVisualizer::Cleanup())
		return 1;

	m_mapIncidentObjectsToRows.clear();

	return 0;
}


// PopupMenu
void IncidentListVisual::tableContextMenuRequested(int row __attribute__ ((unused)) , int col __attribute__ ((unused)) , const QPoint & pos)
{
	// An incident dialog pops up for adding an incident when right-clicking any row of the incident list

	int iResult = m_pRightClickMenu->exec(pos);
	//std::map<Coords, IncidentModel *> * pIncidentRegistry;
	switch(iResult)
	{
		case 0:
			{
				QIncidentDialog * pDialog = new QIncidentDialog(g_pMainWindow, 0, Qt::WDestructiveClose);
				pDialog->m_lineIncidentStartTime->setEnabled(false);
				pDialog->m_labelIncidentStartTime->hide();
				pDialog->m_lineIncidentStartTime->hide();
				pDialog->m_pfnAcceptCallback = AddIncident;
				pDialog->show();
				UpdateIncidentTable();
				break;
			}
		default:
			break;
	}
}

void IncidentListVisual::GetParams(std::map<QString, ModelParameter> & mapParams)
{
	TableVisualizer::GetParams(mapParams);
}

QDragObject * IncidentListVisualDragObjectCreator(TableVisualizer * pTableVisualizer)
{
	IncidentListVisual * pIncidentList = (IncidentListVisual *)pTableVisualizer;
	QDragObject * pDragObject = NULL;
	std::map<Coords, int>::iterator iterRow;
	std::map<Coords, IncidentModel *> * pIncidentRegistry;
	std::map<Coords, IncidentModel *>::iterator iterIncident;
	int row = ((QTableVisualizer *)pIncidentList->GetWidget())->m_pTable->currentRow();

	for (iterRow = pIncidentList->m_mapIncidentObjectsToRows.begin(); iterRow != pIncidentList->m_mapIncidentObjectsToRows.end(); ++iterRow) //iterRow++
	{
		if (iterRow->second == row)
		{
			pIncidentRegistry = g_pIncidentRegistry->acquireLock();
			iterIncident = pIncidentRegistry->find(iterRow->first);
			if (iterIncident != pIncidentRegistry->end() && iterIncident->second != NULL)
			{
				pDragObject = new QTextDrag("OBJECT:" + iterIncident->second->GetModelName(), ((QTableVisualizer *)pIncidentList->GetWidget())->m_pTable);
			}
			g_pIncidentRegistry->releaseLock();
			break;
		}
	}

	return pDragObject;
}
