/***************************************************************************
 *   Copyright (C) 2005, Carnegie Mellon University.                       *
 *   Maintained by: Daniel Weller                                          *
 *                  Rahul Mangharam                                        *
 *                  and the rest of the GrooveNet Team                     *
 *                                                                         *
 *   Email: dweller@ece.cmu.edu or rahulm@ece.cmu.edu                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <qapplication.h>
#include <qfiledialog.h>
#include <qcursor.h>
#include <qsplashscreen.h>

#include "MainWindow.h"
#include "MapDB.h"
#include "Simulator.h"
#include "Network.h"
#include "Logger.h"
#include "Settings.h"
#include "MapObjects.h"
#include "CarRegistry.h"
#include "InfrastructureNodeRegistry.h"

#include <iostream>
// added by Cong
#include "IncidentRegistry.h"
#include "GenerateSimFile.h"
//#include "GenerateSimFile.cpp"
// ---

Settings * g_pSettings = NULL;
Simulator * g_pSimulator = NULL;
CarRegistry * g_pCarRegistry = NULL;
InfrastructureNodeRegistry * g_pInfrastructureNodeRegistry = NULL;
IncidentRegistry * g_pIncidentRegistry = NULL; // added by Cong
MapObjects * g_pMapObjects = NULL;
MapDB * g_pMapDB = NULL;
MainWindow * g_pMainWindow = NULL;
Logger * g_pLogger = NULL;
QMessageList * m_pMessageList = NULL;

int main( int argc, char ** argv )
{
	QApplication a( argc, argv );
	QSettings appSettings;
	QString simFile;
	QPixmap bmpSplash(QDir(a.applicationDirPath()).absFilePath("splash.jpg"));

	g_pSettings = new Settings(argc, argv, &appSettings);
	g_pSettings->ReadSettings();
	QSplashScreen * pSplash = new QSplashScreen(bmpSplash, Qt::WDestructiveClose);
	int ret = 0;
	qApp->setOverrideCursor(QCursor(Qt::WaitCursor));
	pSplash->show();
	g_pLogger = new Logger();
	g_pMapDB = new MapDB();
	g_pMapObjects = new MapObjects();
	g_pCarRegistry = new CarRegistry();
	g_pInfrastructureNodeRegistry = new InfrastructureNodeRegistry();
	g_pIncidentRegistry = new IncidentRegistry(); // added by Cong
	g_pSimulator = new Simulator();
	InitNetworking();
	g_pMainWindow = new MainWindow();
	g_pMainWindow->setCaption(PACKAGE_TITLE " v" VERSION);
	InitMapDB();
	if (g_pSettings->m_sSettings[SETTINGS_GENERAL_LOADMAPS_NUM].GetValue().bValue)
		g_pMapDB->LoadAll(GetDataPath());
	if(g_pSettings->m_sSettings[SETTINGS_HYBRIDNETWORK_MODE_NUM].GetValue().iValue == 1)
	{
		StartHybridClient();
	}
	if(g_pSettings->m_sSettings[SETTINGS_HYBRIDNETWORK_MODE_NUM].GetValue().iValue == 2)
	{
		StartHybridServer();
	}
	if (g_pSettings->m_sSettings[SETTINGS_GENERAL_NETWORK_NUM].GetValue().bValue)
		InitNetwork();

	//dbgprint("PACKET_MINIMUM_LENGTH = %d\n", PACKET_MINIMUM_LENGTH);

	g_pMainWindow->show();
	pSplash->finish(g_pMainWindow);
	qApp->restoreOverrideCursor();
	a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
	
	// modified by Cong
	//g_pMainWindow->m_pFileNew->activate();
	// parse command line arguments
	/*std::cout << argc <<std::endl;
	for (int i = 0; i < argc; i++)
	{
	    std::cout << argv[i] << std::endl;
	}*/
	
	if (argc > 2)
	{   
	    int AttackerNum = atoi(argv[1]); // Attacker Role Number
	    int AuthorityNum = atoi(argv[2]); // Authority Role Number
	    int DefaultNum = atoi(argv[3]); // Default Role Number
	    int IncidentNum = atoi(argv[4]); // Incident Number
	    int rsuNum = atoi(argv[5]); // Infrastructure Number
	    
	    // automatically create a simulation file
	    if (GenSimFile(AttackerNum, AuthorityNum, DefaultNum, IncidentNum, rsuNum))
		std::cout << "Creating simulation file...Successful\n";
	    else
		std::cout << "Creating simlation file...failed\n";
	}
	else if (argc == 2)
	{
	    //std::string fileName = argv[1];
	    if (GenSimFile(argv[1]))
		std::cout << "Creating simulation file...Successful\n";
	    else
		std::cout << "Creating simulation file...failed\n";
	}
	
	if (g_pMainWindow->isShown())
		ret = a.exec();

	g_pMainWindow = NULL;
	CloseNetwork();

	delete g_pSimulator;
	g_pSimulator = NULL;
	delete g_pInfrastructureNodeRegistry;
	g_pInfrastructureNodeRegistry = NULL;
	delete g_pCarRegistry;
	g_pCarRegistry = NULL;
	//---
	delete g_pIncidentRegistry;
	g_pIncidentRegistry = NULL;
	//--- added by Cong
	delete g_pMapObjects;
	g_pMapObjects = NULL;
	delete g_pLogger;
	g_pLogger = NULL;
	g_pSettings->WriteSettings();
	delete g_pSettings;
	g_pSettings = NULL;
	return ret;
}
