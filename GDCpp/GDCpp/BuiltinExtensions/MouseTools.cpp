#include "GDCpp/BuiltinExtensions/MouseTools.h"
#include "GDCpp/RuntimeScene.h"
#include "GDCpp/RuntimeLayer.h"
#include <SFML/Graphics.hpp>

void GD_API CenterCursor( RuntimeScene & scene )
{
    sf::Mouse::setPosition(sf::Vector2i(scene.renderWindow->getSize().x/2, scene.renderWindow->getSize().y/2), *scene.renderWindow );
}

void GD_API CenterCursorHorizontally( RuntimeScene & scene )
{
    sf::Mouse::setPosition(sf::Vector2i(scene.renderWindow->getSize().x/2, sf::Mouse::getPosition(*scene.renderWindow).y ), *scene.renderWindow );
}

void GD_API CenterCursorVertically( RuntimeScene & scene )
{
    sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition(*scene.renderWindow).x, scene.renderWindow->getSize().y/2), *scene.renderWindow );
}

void GD_API SetCursorPosition( RuntimeScene & scene, float newX, float newY )
{
    sf::Mouse::setPosition(sf::Vector2i(newX, newY), *scene.renderWindow );
}

void GD_API HideCursor( RuntimeScene & scene )
{
    scene.renderWindow->setMouseCursorVisible(false);
}

void GD_API ShowCursor( RuntimeScene & scene )
{
    scene.renderWindow->setMouseCursorVisible(true);
}

double GD_API GetCursorXPosition( RuntimeScene & scene, const std::string & layer, unsigned int camera )
{
    if (scene.GetRuntimeLayer(layer).GetCameraCount() == 0) return 0;
    if (camera >= scene.GetRuntimeLayer(layer).GetCameraCount()) camera = 0;

    //Get view, and compute mouse position
    const sf::View & view = scene.GetRuntimeLayer(layer).GetCamera(camera).GetSFMLView();
    return scene.renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*scene.renderWindow), view).x;
}

double GD_API GetCursorYPosition( RuntimeScene & scene, const std::string & layer, unsigned int camera )
{
    if (scene.GetRuntimeLayer(layer).GetCameraCount() == 0) return 0;
    if (camera >= scene.GetRuntimeLayer(layer).GetCameraCount()) camera = 0;

    //Get view, and compute mouse position
    const sf::View & view = scene.GetRuntimeLayer(layer).GetCamera(camera).GetSFMLView();
    return scene.renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*scene.renderWindow), view).y;
}

bool GD_API MouseButtonPressed( RuntimeScene & scene, const std::string & key )
{
    if ( !scene.RenderWindowHasFocus() && scene.IsInputDisabledWhenFocusIsLost() )
        return false;

    if ( key == "Left" ) { return sf::Mouse::isButtonPressed( sf::Mouse::Left ); }
    if ( key == "Right" ) { return sf::Mouse::isButtonPressed( sf::Mouse::Right ); }
    if ( key == "Middle" ) { return sf::Mouse::isButtonPressed( sf::Mouse::Middle ); }
    if ( key == "XButton1" ) { return sf::Mouse::isButtonPressed( sf::Mouse::XButton1 ); }
    if ( key == "XButton2" ) { return sf::Mouse::isButtonPressed( sf::Mouse::XButton2 ); }

    return false;
}

int GD_API GetMouseWheelDelta( RuntimeScene & scene )
{
    if ( !scene.RenderWindowHasFocus() && scene.IsInputDisabledWhenFocusIsLost() )
        return false;

    const std::vector<sf::Event> & events = scene.GetRenderTargetEvents();
    for (unsigned int i = 0;i<events.size();++i)
    {
        if (events[i].type == sf::Event::MouseWheelMoved )
            return events[i].mouseWheel.delta;
    }

    return 0;
}