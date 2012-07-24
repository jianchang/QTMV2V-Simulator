/*
 * File Name: IncidentRegistry.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description: Objects of this class will keep track of the created incident models
 *              and provide methods for adding or removing them. 
 */
 
#ifndef _INCIDENTREGISTRY_H
#define _INCIDENTREGISTRY_H

#include "IncidentModel.h"

class IncidentRegistry
{
public:
	IncidentRegistry();
	~IncidentRegistry();

	inline std::map<Coords, IncidentModel *> * acquireLock(bool bWait = true)
	{
		if (bWait)
		{
			m_mutexRegistry.lock();
			return &m_mapRegistry;
		}
		else
		{
			return m_mutexRegistry.tryLock() ? &m_mapRegistry : NULL;
		}
	}
	inline std::map<Coords, IncidentModel *> * getIncidentRegistry()
	{
		return &m_mapRegistry;
	}
	inline void releaseLock()
	{
		m_mutexRegistry.unlock();
	}
	inline void addIncident(IncidentModel * pIncident)
	{
		m_mutexRegistry.lock();
		m_mapRegistry.insert(std::pair<Coords, IncidentModel *>(pIncident->GetCurrentPosition(), pIncident));
		m_mutexRegistry.unlock();
	}
	inline bool removeIncident(Coords coordsIncident)
	{
		bool bRemoved;
		m_mutexRegistry.lock();
		bRemoved = m_mapRegistry.erase(coordsIncident) > 0;
		m_mutexRegistry.unlock();
		return bRemoved;
	}

protected:
	std::map<Coords, IncidentModel *> m_mapRegistry;
	QMutex m_mutexRegistry;

private:
	inline IncidentRegistry(const IncidentRegistry & copy __attribute__ ((unused)) ) {}
	inline IncidentRegistry & operator = (const IncidentRegistry & copy __attribute__ ((unused)) ) {return *this;}

};

extern IncidentRegistry * g_pIncidentRegistry;

#endif
