//----------------------------------------------------------------------------
//
// FILE: ClientEnvironmentFacility.cpp
//
//----------------------------------------------------------------------------
// Copyright (c) 1998 The Northern Trust Company.
// All Rights Reserved.
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <rw/cstring.h>
#include <rw/thr/mutex.h>

#include "IllegalArgumentException.h"
#include "FileConfigSource.h"

#include "ClientEnvironmentFacility.h"

#define MESSAGE "Unable to read environment.ini file. Exception: "

#define LOCK_GUARD() RWMutexLock::LockGuard guard(*((RWMutexLock*)(this->_mutex)))
/*
 * <hr>
 * <b>Description</b>
 * <p>
 * 	The ClientEnvironmentFacility gets information from the environment that
 *      the Client needs.
 * <p>
 *
 * @see      NamingStrategy.cpp
 * @see      NameBuilder.cpp
 * @see      EnvironmentFacility.cpp
 * @see      ClientEnvironmentFacility.cpp
 * @version  1.0  29 Sep 1998
 */

ClientEnvironmentFacility *ClientEnvironmentFacility::_ClientEnvironmentFacility = new ClientEnvironmentFacility();
int ClientEnvironmentFacility::_fileRead = 0;

ClientEnvironmentFacility::ClientEnvironmentFacility ()
: _mutex( (void *) new RWMutexLock() )
{
}

//-------------------------------------------------------------------
// public interface
//-------------------------------------------------------------------

/**
 * Method returns the single instance (singleton) of the ClientEnvironmentFacility
 * used within the given applet/application.
 *
 * @return  the ClientEnvironmentFacility singleton
 */
ClientEnvironmentFacility *ClientEnvironmentFacility::getClientEnvironmentFacility() {
	return _ClientEnvironmentFacility;
}
	
/**
 * Method calls the readFromFile() method with the name of the
 * file containing the environment properties.  If no file is
 * specified in props, will use the default file location.
 *
 */
void ClientEnvironmentFacility::initializeClientEnv (const char *fileLocation)
throw( IllegalArgumentException )
{
	if (_fileRead) return;
	//RWMutexLock::LockGuard guard(_mutex); // mutex unlocked when out of scope
	LOCK_GUARD();
	if( !_fileRead ) {
		if (fileLocation) {
			readFromFile (fileLocation);
		}
		else {
			throw IllegalArgumentException("Invalid file provided to ClientEnvironmentFacility::initializeClientEnv");
			/*
			if (getenv ("SOLARIS") != NULL) {
				readFromFile (DEFAULT_UNIX_CLIENT_ENV_FILE);
			}
			else {
				readFromFile (DEFAULT_NT_CLIENT_ENV_FILE);
			}
			*/
		}
	}
}

//-------------------------------------------------------------------
// private implementation
//-------------------------------------------------------------------

/**
 * Method creates a ConfigSource with the filename and reads in the
 * environment parameters.
 *
 */
void ClientEnvironmentFacility::readFromFile (const char *fileLocation)
{
	// create ConfigSource
	FileConfigSource *cf = new FileConfigSource (fileLocation);

	_envFacilityList = cf->buildProperties(ENV_CONFIG_SECTION);

	_fileRead = 1;
	delete cf;
}


