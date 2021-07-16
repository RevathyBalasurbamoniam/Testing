#ifndef _ClientEnvironmentFacility_h
#define _ClientEnvironmentFacility_h

#include <stdio.h>
#include <rw/cstring.h>
#include "EnvironmentFacility.h"
#include "LinkedList.h"
#include "EnvironmentFacilityException.h"
#include "FileConfigSource.h"
#include "Export.h" 
#include "Mutex.h"

#define DEFAULT_UNIX_CLIENT_ENV_FILE "/usr/appl/arch/unit/environment.ini"
#define DEFAULT_NT_CLIENT_ENV_FILE "e:\\Data\\TNTApps\\environment.ini"

class ClientEnvironmentFacility : public EnvironmentFacility
{
private:		
	Mutex mutex;

	static ClientEnvironmentFacility *_ClientEnvironmentFacility;
	static int _fileRead;

public:
	// constructor
	ClientEnvironmentFacility();
	static EXPORT ClientEnvironmentFacility *getClientEnvironmentFacility();
	void initializeClientEnv (RWCString fileLocation);
	void initializeClientEnv ();
	void readFromFile (RWCString fileLocation);

};

#endif
















