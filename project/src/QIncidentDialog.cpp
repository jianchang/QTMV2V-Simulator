/*
 * File Name: QIncidentDialog.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 */
 
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qgroupbox.h>

#include "QIncidentDialog.h"
#include "QBoundingRegionConfDialog.h"
#include "IncidentRegistry.h"
#include "Simulator.h"
#include "StringHelp.h"

#include "app16x16.xpm"
#include <iostream>

QIncidentDialog::QIncidentDialog(QWidget * parent, const char * name, WFlags f)
: QDialog(parent, name, f), m_pfnAcceptCallback(NULL)
{
	QWidget * boxIncidentAddress = new QWidget(this);
	m_labelIncidentAddress = new QLabel("Incident Address:", boxIncidentAddress);
	m_lineIncidentAddress = new QLineEdit("", boxIncidentAddress);

	//m_groupIncidentSeve = new QButtonGroup(2, Qt::Horizontal, "Incident Type", this);
	//m_buttonEmergency = new QRadioButton("Emergency Incident", m_groupIncidentType);
	//m_buttonWarning = new QRadioButton("Warning Incident", m_groupIncidentType);
	//QGroupBox * m_groupIncidentSeverity = new QGroupBox(1, Qt::Vertical, "Incident Severity", this);
	QWidget * boxIncidentSeverity = new QWidget(this);
	m_labelIncidentSeverity = new QLabel("Incident Severity:", boxIncidentSeverity);
	m_comboIncidentSeverity = new QComboBox(false, boxIncidentSeverity);

	QWidget * boxIncidentDesc = new QWidget(this);
	m_labelIncidentDesc = new QLabel("Incident Description:", boxIncidentDesc);
	m_lineIncidentDesc = new QLineEdit("", boxIncidentDesc);

	QGroupBox * m_groupIncidentRegion = new QGroupBox(1, Qt::Vertical, "Incident Bounding Region", this);
	m_labelIncidentRegionType = new QLabel("Bouding Region Type:", m_groupIncidentRegion);
	m_comboIncidentRegionType = new QComboBox(false, m_groupIncidentRegion);
	m_buttonIncidentRegionConfig = new QPushButton("Configure...", m_groupIncidentRegion);

	QWidget * boxIncidentTime = new QWidget(this);
	m_labelIncidentStartTime = new QLabel("Start time:", boxIncidentTime);
	m_lineIncidentStartTime = new QLineEdit("", boxIncidentTime);

	//QWidget * boxIncidentDuration = new QWidget(this);
	m_labelIncidentDuration = new QLabel("Duration:", boxIncidentTime);
	m_spinIncidentDuration = new QSpinBox(0, 999999999, 1, boxIncidentTime);

	QWidget * boxButtons = new QWidget(this);
	m_buttonOK = new QPushButton("&Add", boxButtons);
	m_buttonCancel = new QPushButton("&Cancel", boxButtons);

	QVBoxLayout * pLayout = new QVBoxLayout(this, 8, 8);
	QHBoxLayout * pIncidentAddressBoxLayout = new QHBoxLayout(boxIncidentAddress, 0, 8);
	QHBoxLayout * pIncidentSeverityBoxLayout = new QHBoxLayout(boxIncidentSeverity, 0, 8);
	QHBoxLayout * pIncidentDescBoxLayout = new QHBoxLayout(boxIncidentDesc, 0, 8);
	QHBoxLayout * pIncidentTimeBoxLayout = new QHBoxLayout(boxIncidentTime, 0, 8);
	//QHBoxLayout * pIncidentDurationBoxLayout = new QHBoxLayout(boxIncidentDuration, 0, 8);
	QHBoxLayout * pButtonBoxLayout = new QHBoxLayout(boxButtons, 0, 8);

	//connect(m_groupIncidentType, SIGNAL(clicked(int)), this, SLOT(slotIncidentTypeChanged(int)));
	connect(m_comboIncidentSeverity, SIGNAL(activated(int)), this, SLOT(slotIncidentSeverityChanged(int)));
	connect(m_comboIncidentRegionType, SIGNAL(activated(int)), this, SLOT(slotIncidentRegionTypeChanged(int)));
	connect(m_buttonIncidentRegionConfig, SIGNAL(clicked()), this, SLOT(slotIncidentRegionConfig()));
	connect(m_buttonOK, SIGNAL(clicked()), this, SLOT(accept()));
	connect(m_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

	m_comboIncidentRegionType->insertItem("Circle");
	m_comboIncidentRegionType->insertItem("Square");
	slotIncidentRegionTypeChanged(0);

	//m_groupIncidentType->setButton(m_groupIncidentType->id(m_buttonEmergency));
	//slotIncidentTypeChanged(m_groupIncidentType->selectedId());
	m_comboIncidentSeverity->insertItem("Level 0");
	m_comboIncidentSeverity->insertItem("Level 1");
	m_comboIncidentSeverity->insertItem("Level 2");
	m_comboIncidentSeverity->insertItem("Level 3");
	m_comboIncidentSeverity->insertItem("Level 4");
	m_comboIncidentSeverity->insertItem("Level 5");
	slotIncidentSeverityChanged(0);
	
	m_spinIncidentDuration->setValue(3600);
	m_spinIncidentDuration->setSuffix(" s");
	
	m_buttonOK->setAutoDefault(false);
	m_buttonCancel->setAutoDefault(false);

	pLayout->addWidget(boxIncidentAddress);
	//pLayout->addWidget(m_groupIncidentType);
	pLayout->addWidget(boxIncidentSeverity);
	pLayout->addWidget(boxIncidentDesc);
	pLayout->addWidget(m_groupIncidentRegion);
	pLayout->addWidget(boxIncidentTime);
	pLayout->addWidget(boxButtons);
	
	pIncidentSeverityBoxLayout->addWidget(m_labelIncidentSeverity, 0, Qt::AlignLeft);
	pIncidentSeverityBoxLayout->addWidget(m_comboIncidentSeverity, 1);
	pIncidentAddressBoxLayout->addWidget(m_labelIncidentAddress, 0, Qt::AlignLeft);
	pIncidentAddressBoxLayout->addWidget(m_lineIncidentAddress, 1);
	pIncidentDescBoxLayout->addWidget(m_labelIncidentDesc, 0, Qt::AlignLeft);
	pIncidentDescBoxLayout->addWidget(m_lineIncidentDesc, 1);
	pIncidentTimeBoxLayout->addWidget(m_labelIncidentStartTime, 0, Qt::AlignLeft);
	pIncidentTimeBoxLayout->addWidget(m_lineIncidentStartTime, 1);
	pIncidentTimeBoxLayout->addWidget(m_labelIncidentDuration, 0, Qt::AlignLeft);
	pIncidentTimeBoxLayout->addWidget(m_spinIncidentDuration, 1);
	pButtonBoxLayout->addStretch(1);
	pButtonBoxLayout->addWidget(m_buttonOK, 0 ,Qt::AlignCenter);
	pButtonBoxLayout->addWidget(m_buttonCancel, 0, Qt::AlignCenter);

	setCaption("GrooveNet - Add Incident...");
	setIcon(app16x16_xpm);
}

QIncidentDialog::~QIncidentDialog()
{
	
}
		
void QIncidentDialog::UpdateIncidentRegion()
{
	
}
		
void QIncidentDialog::slotIncidentSeverityChanged(int index)
{
	
}

void QIncidentDialog::slotIncidentRegionTypeChanged(int index)
{
	
}

void QIncidentDialog::slotIncidentRegionConfig()
{
	
}

void QIncidentDialog::accept()
{
	if (m_pfnAcceptCallback != NULL)
		(*m_pfnAcceptCallback)(this);

	QDialog::accept();
	
	/*IncidentModel * pIncident;
	
	//g_pIncidentRegistry->acquireLock();

	if (!m_lineIncidentAddress->text().isEmpty() && StringToAddress(m_lineIncidentAddress->text(), &(pIncident->m_sPosition)))
	{	
		pIncident->m_strPosition = m_lineIncidentAddress->text();
		pIncident->m_ptPosition = pIncident->m_sPosition.ptCoordinates;
		pIncident->m_iIncident.location = pIncident->m_ptPosition; 
	}
	else
	{	
		pIncident->m_strPosition = "";
		pIncident->m_ptPosition.Set(0, 0);
		pIncident->m_iIncident.location.Set(0, 0);
	}
	/*if (m_groupIncidentType->selectedId() == m_groupIncidentType->id(m_buttonEmergency))
	{
		pIncident->m_iType = "EMERGENCY";
		pIncident->m_iIncident.type = pIncident->m_iType;
	}
	else
	{
		pIncident->m_iType = "WARNING";
		pIncident->m_iIncident.type = pIncident->m_iType;
	}
	pIncident->m_iSeve = m_comboIncidentSeverity->currentText();
	pIncident->m_iIncident.severity = pIncident->m_iSeve;
	if (!m_lineIncidentDesc->text().isEmpty())
	{
		pIncident->m_iDesc = m_lineIncidentDesc->text();
		pIncident->m_iIncident.description = pIncident->m_iDesc;
	}
	else
	{
		pIncident->m_iDesc = "";
		pIncident->m_iIncident.description = pIncident->m_iDesc;
	}
	pIncident->m_iRegion = m_comboIncidentRegionType->currentText();
	pIncident->m_iIncident.startTime = g_pSimulator->m_tCurrent;//MakeTime(StringToNumber(m_lineIncidentStartTime->text()));
	pIncident->m_iIncident.durationTime = MakeTime(m_spinIncidentDuration->value() * 1e-0f);	

	MapIncidentObject * pObject = new MapIncidentObject(pIncident);
	pIncident->m_iMapObjectID = g_pMapObjects->add(pObject);

	//g_pIncidentRegistry->releaseLock();

	g_pIncidentRegistry->addIncident(pIncident);*/

}


void AddIncident(QIncidentDialog * pDialog)
{	
	
	IncidentModel pIncident ;
	Address sPosition;
	struct timeval delay = MakeTime(StringToNumber("0.4"));
	//g_pIncidentRegistry->acquireLock();
	
	if (!pDialog->m_lineIncidentAddress->text().isEmpty() && StringToAddress(pDialog->m_lineIncidentAddress->text(), &(sPosition)))
	{	
		pIncident.SetPosition(pDialog->m_lineIncidentAddress->text());
	}
	else
	{
		QString addr = "4000 Forbes Avenue, Pittsburgh, Pennsylvania";
		pIncident.SetPosition(addr);
	}
	
	pIncident.SetSeverity(pDialog->m_comboIncidentSeverity->currentText());

	if (!pDialog->m_lineIncidentDesc->text().isEmpty())
	{
		pIncident.SetDescription(pDialog->m_lineIncidentDesc->text());
	}
	pIncident.SetRegion(pDialog->m_comboIncidentRegionType->currentText());
	pIncident.SetStartTime(g_pSimulator->m_tCurrent - g_pSimulator->m_tStart + delay);
	pIncident.SetDuration(MakeTime(pDialog->m_spinIncidentDuration->value() * 1e-0f));	

	MapIncidentObject * pObject = new MapIncidentObject(&(pIncident));
	pIncident.SetIncidentMapObjectID(g_pMapObjects->add(pObject));

	//g_pIncidentRegistry->releaseLock();

	g_pIncidentRegistry->addIncident(&(pIncident));

}

