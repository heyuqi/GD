/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the MIT License.
 */

#if defined(GD_IDE_ONLY)
#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H
#include <vector>
#include <boost/shared_ptr.hpp>
#include "GDCore/PlatformDefinition/Platform.h"

namespace gd
{

/**
 * \brief Singleton class managing all the platforms available.
 *
 * Platforms can be added thanks to gd::PlatformManager::AddPlatform. <br>
 * See gd::PlatformLoader::LoadPlatformInManager to load a platform from a file.
 *
 *
 * \see gd::PlatformLoader
 */
class GD_CORE_API PlatformManager
{
public:

    /**
     * \brief Add a new platform to be used by the IDE
     */
    bool AddPlatform(boost::shared_ptr<gd::Platform> newPlatform);

    /**
     * \brief Get a pointer to the platform called \a platformName.
     * \note The PlatformManager is the owner of the platform, so the pointer should not be freed or deleted.
     */
    gd::Platform* GetPlatform(const std::string & platformName) const;

    /**
     * \brief Get a list of all platforms available.
     */
    const std::vector< boost::shared_ptr<gd::Platform> > & GetAllPlatforms() const { return platformsLoaded; };

    /**
     * \brief Notify each platform that the IDE is ready, by calling their OnIDEInitialized member function.
     */
    void NotifyPlatformIDEInitialized() const;

    static PlatformManager *Get()
    {
        if ( NULL == _singleton )
        {
            _singleton = new PlatformManager;
        }

        return ( static_cast<PlatformManager*>( _singleton ) );
    }

    /**
     * \brief Destroy the global platform manager.
     *
     * This is called by the IDE before shutting down.
     * ( Otherwise, platforms won't get notified that the IDE closed. )
     */
    static void DestroySingleton()
    {
        if ( NULL != _singleton )
        {
            for (unsigned int i = 0;i<_singleton->platformsLoaded.size();++i)
            {
                if ( _singleton->platformsLoaded[i] != boost::shared_ptr<gd::Platform>() )
                    _singleton->platformsLoaded[i]->OnIDEClosed();
            }

            delete _singleton;
            _singleton = NULL;
        }
    }

private:
    std::vector< boost::shared_ptr<gd::Platform> > platformsLoaded;

    PlatformManager();
    virtual ~PlatformManager();
    static PlatformManager *_singleton;
};

}
#endif // PLATFORMMANAGER_H
#endif
