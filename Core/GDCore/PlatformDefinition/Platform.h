/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the MIT License.
 */

#ifndef GDCORE_PLATFORM_H
#define GDCORE_PLATFORM_H
#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <map>
#include "GDCore/PlatformDefinition/ChangesNotifier.h"
#include "GDCore/PlatformDefinition/LayoutEditorPreviewer.h"
namespace gd { class InstructionsMetadataHolder; }
namespace gd { class Project; }
namespace gd { class Object; }
namespace gd { class Automatism; }
namespace gd { class AutomatismMetadata; }
namespace gd { class ObjectMetadata; }
namespace gd { class BaseEvent; }
namespace gd { class AutomatismsSharedData; }
namespace gd { class PlatformExtension; }
namespace gd { class LayoutEditorCanvas; }
namespace gd { class ProjectExporter; }

typedef void (*DestroyFunPtr)(gd::Object*);
typedef gd::Object * (*CreateFunPtr)(std::string name);

namespace gd
{

/**
 * \brief Base class for implementing a platform
 *
 * \ingroup PlatformDefinition
 */
class GD_CORE_API Platform
{
public:
    Platform();
    virtual ~Platform();

    /**
     * \brief Must return the platform name
     */
    virtual std::string GetName() const { return "Unnamed platform"; }

    /**
     * \brief Must return the platform full name, displayed to users.
     */
    virtual std::string GetFullName() const { return "Unnamed platform"; }

    #if defined(GD_IDE_ONLY)
    /**
     * \brief Must return a text describing the platform in a few words.
     */
    virtual std::string GetSubtitle() const { return ""; }

    /**
     * \brief Must return a text describing the platform, displayed to users.
     */
    virtual std::string GetDescription() const { return ""; }

    /**
     * \brief Must return a filename to a 32*32 image file for the platform.
     */
    virtual std::string GetIcon() const { return ""; }
    #endif


    /** \name Extensions management
     * Member functions used to manage the extensions
     */
    ///@{

    /**
     * \brief Must return the name of the function that is used to create an extension for this platform.
     *
     * For example, GD C++ Platform uses "CreateGDExtension" and GD JS Platform "CreateGDJSExtension".
     * \see gd::ExtensionsLoader
     * \see GetExtensionDestroyFunctionName
     */
    virtual std::string GetExtensionCreateFunctionName() { return ""; }

    /**
     * \brief Must return the name of the function that is used to create an extension for this platform.
     *
     * For example, GD C++ Platform uses "CreateGDExtension" and GD JS Platform "CreateGDJSExtension".
     * \see gd::ExtensionsLoader
     * \see GetExtensionDestroyFunctionName
     */
    virtual std::string GetExtensionDestroyFunctionName() { return ""; }

    /**
     * \brief Add an extension to the manager.
     * \note This method is virtual and can be redefined by platforms if they want to do special work when an extension is loaded.
     * \see gd::ExtensionsLoader
     */
    virtual bool AddExtension(boost::shared_ptr<PlatformExtension> extension);

    /**
     * \brief Return true if an extension with the specified name is loaded
     */
    bool IsExtensionLoaded(const std::string & name) const;

    /**
     * \brief Get an extension of the platform
     * @return Shared pointer to the extension
     */
    boost::shared_ptr<PlatformExtension> GetExtension(const std::string & name) const;

    /**
     * \brief Get all extensions loaded for the platform.
     * @return Vector of Shared pointer containing all extensions
     */
    const std::vector < boost::shared_ptr<gd::PlatformExtension> > & GetAllPlatformExtensions() const { return extensionsLoaded; };

    ///@}

    /** \name Factory method
     * Member functions used to create the platforms objects
     */
    ///@{

    /**
     * \brief Create an object of given type with the specified name.
     */
    boost::shared_ptr<gd::Object> CreateObject(std::string type, const std::string & name) const;

    /**
     * \brief Create an automatism
     */
    gd::Automatism* CreateAutomatism(const std::string & type) const;

    /**
     * \brief Create an automatism shared data object.
     */
    boost::shared_ptr<gd::AutomatismsSharedData> CreateAutomatismSharedDatas(const std::string & type) const;

    #if defined(GD_IDE_ONLY)
    /**
     * \brief Create an event of given type
     */
    boost::shared_ptr<gd::BaseEvent> CreateEvent(const std::string & type) const;

    ///@}


    /** \name Notification of changes
     * The platform can do extra work when a change occurs by providing a special gd::ChangesNotifier
     */
    ///@{

    /**
     * \brief Must provide a ChangesNotifier object that will be called by the IDE if needed.
     * The IDE is not supposed to store the returned object.
     *
     * The default implementation simply return a ChangesNotifier object doing nothing.
     */
    virtual ChangesNotifier & GetChangesNotifier() const { return defaultEmptyChangesNotifier; };
    ///@}

    /** \name Preview and compilation
     * The platform should provides specialized classes used for previewing layouts or
     * exporting the project.
     */
    ///@{

    #if !defined(GD_NO_WX_GUI)
    /**
     * \brief Must provide a gd::LayoutEditorPreviewer object that will be stored and used
     * by LayoutEditorCanvas to display/run a preview of the layout of a project.
     *
     * The default implementation simply return a gd::LayoutEditorPreviewer object doing nothing.
     */
    virtual boost::shared_ptr<gd::LayoutEditorPreviewer> GetLayoutPreviewer(gd::LayoutEditorCanvas & editor) const;

    /**
     * \brief Must provide a gd::ProjectExporter object that will be used
     * by the IDE to export the project so as to be used without the IDE.
     *
     * The default implementation simply return a gd::ProjectExporter object doing nothing.
     */
    virtual boost::shared_ptr<gd::ProjectExporter> GetProjectExporter() const;
    #endif
    ///@}

    /**
     * \brief Called when the IDE is about to shut down: Take this opportunity for erasing
     * for example any temporary file.
     */
    virtual void OnIDEClosed() {};

    /**
     * \brief Called when the IDE is initialized and ready to be used.
     */
    virtual void OnIDEInitialized() {};

    #endif

private:

    std::vector < boost::shared_ptr<PlatformExtension> >    extensionsLoaded; ///< Extensions of the platform
    std::map < std::string, CreateFunPtr >                  creationFunctionTable; ///< Creation functions for objects
    std::map < std::string, DestroyFunPtr >                 destroyFunctionTable; ///< Destroy functions for objects

    #if defined(GD_IDE_ONLY)
    static ChangesNotifier defaultEmptyChangesNotifier;
    #endif
};

}

#endif // GDCORE_PLATFORM_H
