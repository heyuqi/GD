/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the MIT License.
 */

#ifndef SCENENAMEMANGLER_H
#define SCENENAMEMANGLER_H
#include <string>

namespace gd
{

/**
 * \brief Used to mangle the name of a scene
 *
 * \ingroup IDE
 */
class GD_CORE_API SceneNameMangler
{
public:

    /**
     * \brief Mangle the name of a scene, replacing all characters that are not 0-9, a-z or A-Z
     * by "_"+AsciiCodeOfTheCharacter. The first character must be a letter, otherwise it is also
     * replaced in the same manner.
     */
    static std::string GetMangledSceneName(const std::string & originalSceneName);

private:
    SceneNameMangler() {};
    virtual ~SceneNameMangler() {};
};

}

#endif // SCENENAMEMANGLER_H

