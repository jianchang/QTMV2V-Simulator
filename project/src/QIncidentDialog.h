/*
 * File Name: QIncidentDialog.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description: 
 */
 
#ifndef _QINCIDENTDIALOG_H
#define _QINCIDENTDIALOG_H

#include <qdialog.h>
#include <qspinbox.h>

#include "IncidentModel.h"

class QRadioButton;
class QButtonGroup;
class QPushButton;
class QComboBox;
class QSpinBox;
class QLabel;
class QLineEdit;

class QIncidentDialog;

typedef void (* QIncidentDialogAcceptCallback)(QIncidentDialog *);

class QIncidentDialog : public QDialog
{
Q_OBJECT
public:
		QIncidentDialog(QWidget * parent = NULL, const char * name = 0, WFlags f = 0);
		virtual ~QIncidentDialog();
		
		void UpdateIncidentRegion();
		
		QIncidentDialogAcceptCallback m_pfnAcceptCallback;
		//IncidentRegion m_incidentRegion;
		
		//QButtonGroup * m_groupIncidentType; 
		//QGroupBox * m_groupIncidentRegion;
		//QRadioButton * m_buttonEmergency, * m_buttonWarning;
		//QGroupBox * m_groupIncidentSeverity;
		QLabel * m_labelIncidentSeverity;
		QComboBox * m_comboIncidentSeverity;
		QComboBox * m_comboIncidentRegionType;
		QSpinBox * m_spinIncidentDuration;
		QPushButton * m_buttonIncidentRegionConfig, * m_buttonOK, * m_buttonCancel;
		QLabel * m_labelIncidentAddress, * m_labelIncidentDesc, * m_labelIncidentRegionType, * m_labelIncidentStartTime, * m_labelIncidentDuration;
		QLineEdit * m_lineIncidentAddress, * m_lineIncidentDesc, * m_lineIncidentStartTime;
		
		
protected slots:
		//virtual void slotIncidentTypeChanged(int id);
		virtual void slotIncidentSeverityChanged(int index);
		virtual void slotIncidentRegionTypeChanged(int index);
		virtual void slotIncidentRegionConfig();
		virtual void accept();
			
};

void AddIncident(QIncidentDialog * pDialog);

#endif
