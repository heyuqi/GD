/**

GDevelop - Tiled Sprite Extension
Copyright (c) 2012 Victor Levasseur (victorlevasseur01@orange.fr)
Copyright (c) 2014 Florian Rival (Florian.Rival@gmail.com)
This project is released under the MIT License.
*/
#if defined(GD_IDE_ONLY)
#include "GDCore/PlatformDefinition/PlatformExtension.h"
#include "GDCore/Tools/Localization.h"
#include "GDCore/Tools/Version.h"
#include "TiledSpriteObject.h"
#include <boost/version.hpp>
#include <iostream>

void DeclareTiledSpriteObjectExtension(gd::PlatformExtension & extension);

/**
 * \brief This class declares information about the JS extension.
 */
class TiledSpriteObjectJsExtension : public gd::PlatformExtension
{
public:

    /**
     * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
     */
    TiledSpriteObjectJsExtension()
    {
        SetExtensionInformation("TiledSpriteObject",
                              _("Tiled Sprite Object"),
                              _("Extension allowing to use tiled sprite objects."),
                              "Victor Levasseur and Florian Rival",
                              "Open source (MIT License)");

        DeclareTiledSpriteObjectExtension(*this);

        GetObjectMetadata("TiledSpriteObject::TiledSprite").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");

        GetAllActionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Width"].codeExtraInformation
            .SetFunctionName("setWidth").SetAssociatedGetter("getWidth").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllConditionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Width"].codeExtraInformation
            .SetFunctionName("getWidth").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllActionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Height"].codeExtraInformation
            .SetFunctionName("setHeight").SetAssociatedGetter("getHeight").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllConditionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Height"].codeExtraInformation
            .SetFunctionName("getHeight").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllActionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Angle"].codeExtraInformation
            .SetFunctionName("setAngle").SetAssociatedGetter("getAngle").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllConditionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::Angle"].codeExtraInformation
            .SetFunctionName("getAngle").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllActionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::XOffset"].codeExtraInformation
            .SetFunctionName("setXOffset").SetAssociatedGetter("getXOffset").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllConditionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::XOffset"].codeExtraInformation
            .SetFunctionName("getXOffset").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllActionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::YOffset"].codeExtraInformation
            .SetFunctionName("setYOffset").SetAssociatedGetter("getYOffset").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");
        GetAllConditionsForObject("TiledSpriteObject::TiledSprite")["TiledSpriteObject::YOffset"].codeExtraInformation
            .SetFunctionName("getYOffset").SetIncludeFile("TiledSpriteObject/tiledspriteruntimeobject.js");

        GD_COMPLETE_EXTENSION_COMPILATION_INFORMATION();
    };
    virtual ~TiledSpriteObjectJsExtension() {};
};

#if defined(EMSCRIPTEN)
extern "C" gd::PlatformExtension * CreateGDJSTiledSpriteObjectExtension() {
    return new TiledSpriteObjectJsExtension;
}
#else
/**
 * Used by GDevelop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" gd::PlatformExtension * GD_EXTENSION_API CreateGDJSExtension() {
    return new TiledSpriteObjectJsExtension;
}

/**
 * Used by GDevelop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void GD_EXTENSION_API DestroyGDJSExtension(gd::PlatformExtension * p) {
    delete p;
}
#endif
#endif
