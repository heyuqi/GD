/**

GDevelop - Particle System Extension
Copyright (c) 2010-2014 Florian Rival (Florian.Rival@gmail.com)
This project is released under the MIT License.
*/

#ifndef PARTICLESYSTEMWRAPPER_H
#define PARTICLESYSTEMWRAPPER_H

#include <boost/shared_ptr.hpp>
class OpenGLTextureWrapper;

namespace SPK
{
class System;
class Model;
class SphericEmitter;
class Sphere;
class Group;
namespace GL
{
class GLRenderer;
}
}

/**
 * Wrapper around SPARK related stuff.
 * This class gives direct access to these stuff,
 * it only manages the destruction and automatize the copy behaviour.
 */
class GD_EXTENSION_API ParticleSystemWrapper
{
    public:
        ParticleSystemWrapper();
        virtual ~ParticleSystemWrapper();
        ParticleSystemWrapper(const ParticleSystemWrapper & other) //What a bad design
        {
            particleSystem = NULL;
            particleModel = NULL;
            emitter = NULL;
            zone = NULL;
            group = NULL;
            renderer = NULL;
            Init(other);
        };
        ParticleSystemWrapper & operator=(const ParticleSystemWrapper & other)
        {
            if ( &other != this ) Init(other);

            return *this;
        }

        SPK::System * particleSystem;
        SPK::Model * particleModel;
        SPK::SphericEmitter * emitter;
        SPK::Sphere * zone;
        SPK::Group * group;
        SPK::GL::GLRenderer * renderer;
        boost::shared_ptr<OpenGLTextureWrapper> openGLTextureParticle;

    private:
        void Init(const ParticleSystemWrapper & other);

        static bool SPKinitialized;
};

#endif // PARTICLESYSTEMWRAPPER_H

