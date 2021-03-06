/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the MIT License.
 */

#if defined(GD_IDE_ONLY)
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <map>
#include <sstream>
#include "GDCore/Tools/Log.h"
#include "GDCore/Tools/Localization.h"
#include "GDCore/CommonTools.h"
#include "GDCore/Events/InstructionMetadata.h"
#include "GDCore/IDE/CommonBitmapManager.h"
#include "GDCore/IDE/InstructionSentenceFormatter.h"
#if !defined(GD_NO_WX_GUI)
#include <wx/config.h>
#include <wx/bitmap.h>
#endif

using namespace std;

namespace gd
{

InstructionSentenceFormatter *InstructionSentenceFormatter::_singleton = NULL;

string InstructionSentenceFormatter::Translate(const gd::Instruction & instr, const gd::InstructionMetadata & metadata)
{
    std::string out = metadata.GetSentence();
    if ( out.empty() ) out = "   "; //Prevent empty sentences that could trigger graphical glitches.

    //Replace _PARAMx_ placeholders by their values
    for (unsigned int i =0;i<metadata.parameters.size();++i)
    {
        std::string placeholder = "_PARAM"+ToString(i)+"_";
        while ( out.find( placeholder ) != std::string::npos )
        {
            std::string parameter = instr.GetParameter(i).GetPlainString();
            out.replace(out.find(placeholder), placeholder.length(), parameter);
        }
    }

    std::replace( out.begin(), out.end(), '\n', ' ');

    return out;
}

std::vector< std::pair<std::string, gd::TextFormatting> > InstructionSentenceFormatter::GetAsFormattedText(
    const Instruction & instr, const gd::InstructionMetadata & metadata)
{
    std::vector< std::pair<std::string, gd::TextFormatting> > formattedStr;

    std::string sentence = metadata.GetSentence();
    std::replace( sentence.begin(), sentence.end(), '\n', ' ');
    bool parse = true;

    while ( parse )
    {
        //Search first parameter
        parse = false;
        size_t firstParamPosition = std::string::npos;
        size_t firstParamIndex = std::string::npos;
        for (unsigned int i =0;i<metadata.parameters.size();++i)
        {
            size_t paramPosition = sentence.find( "_PARAM"+ToString(i)+"_" );
            if ( paramPosition < firstParamPosition )
            {
                firstParamPosition = paramPosition;
                firstParamIndex = i;
                parse = true;
            }
        }

        //When a parameter is found, complete formatted std::string.
        if ( parse )
        {
            if ( firstParamPosition != 0 ) //Add constant text before the parameter if any
            {
                TextFormatting format;
                formattedStr.push_back(std::make_pair(sentence.substr(0, firstParamPosition), format));
            }

            //Add the parameter
            TextFormatting format = GetFormattingFromType(metadata.parameters[firstParamIndex].type);
            format.userData = firstParamIndex;

            std::string text = instr.GetParameter( firstParamIndex ).GetPlainString();
            std::replace( text.begin(), text.end(), '\n', ' ');

            formattedStr.push_back(std::make_pair(text, format));

            sentence = sentence.substr(firstParamPosition+ToString("_PARAM"+ToString(firstParamIndex)+"_").length());
        }
        else if ( !sentence.empty() )//No more parameter found: Add the end of the sentence
        {
            TextFormatting format;
            formattedStr.push_back(std::make_pair(sentence, format));
        }
    }

    return formattedStr;
}

TextFormatting InstructionSentenceFormatter::GetFormattingFromType(const std::string & type)
{
    if (gd::ParameterMetadata::IsObject(type))
        return typesFormatting["object"];

    return typesFormatting[type];
}

std::string InstructionSentenceFormatter::LabelFromType(const std::string & type)
{
    if ( type.empty() ) return "";
    else if ( type == "expression" ) return _("Expression");
    else if ( gd::ParameterMetadata::IsObject(type) ) return _("Object");
    else if ( type == "automatism" ) return _("Automatism");
    else if ( type == "operator" ) return _("Operator");
    else if ( type == "relationalOperator" ) return _( "Relational operator" );
    else if ( type == "file" ) return _("File");
    else if ( type == "key" ) return _( "Key" );
    else if ( type == "mouse" ) return _( "Mouse button" );
    else if ( type == "yesorno" ) return _("Yes or no");
    else if ( type == "police" ) return _("Font");
    else if ( type == "color" ) return _("Color");
    else if ( type == "trueorfalse" ) return _( "True or False" );
    else if ( type == "string" ) return _("String");
    else if ( type == "musicfile" ) return _("Music");
    else if ( type == "soundfile" ) return _("Sound");
    else if ( type == "password" ) return _("Password");
    else if ( type == "layer" ) return _("Layer");
    else if ( type == "joyaxis" ) return _("Joystick axis");
    else if ( type == "objectvar" ) return _("Variable of the object");
    else if ( type == "scenevar" ) return _("Scene variable");
    else if ( type == "globalvar" ) return _("Global variable");

    return _("Unknown");
}

void InstructionSentenceFormatter::LoadTypesFormattingFromConfig()
{
    //Load default configuration
    typesFormatting.clear();
    typesFormatting["expression"].SetColor(99, 0, 0).SetBold();
    typesFormatting["object"].SetColor(19, 81, 0).SetBold();
    typesFormatting["automatism"].SetColor(19, 81, 0).SetBold();
    typesFormatting["operator"].SetColor(64, 81, 79).SetBold();
    typesFormatting["objectvar"].SetColor(44, 69, 99).SetBold();
    typesFormatting["scenevar"].SetColor(44, 69, 99).SetBold();
    typesFormatting["globalvar"].SetColor(44, 69, 99).SetBold();

    //Load any existing custom configuration
    #if !defined(GD_NO_WX_GUI)
    wxConfigBase * config = wxConfigBase::Get();

    for(std::map<std::string, gd::TextFormatting>::iterator it = typesFormatting.begin(); it != typesFormatting.end();++it)
    {
        it->second.SetColor(config->ReadObject("EventsEditor/"+it->first+"Color", it->second.GetWxColor()));
        it->second.bold = config->ReadBool("EventsEditor/"+it->first+"Bold", it->second.IsBold());
        it->second.italic = config->ReadBool("EventsEditor/"+it->first+"Italic", it->second.IsItalic());
    }
    #endif
}

#if !defined(GD_NO_WX_GUI)
void InstructionSentenceFormatter::SaveTypesFormattingToConfig()
{
    wxConfigBase * config = wxConfigBase::Get();

    for (std::map<std::string, TextFormatting>::iterator it = typesFormatting.begin();it!=typesFormatting.end();++it)
    {
        config->Write("EventsEditor/"+it->first+"Color", it->second.GetWxColor());
        config->Write("EventsEditor/"+it->first+"Bold", it->second.bold);
        config->Write("EventsEditor/"+it->first+"Italic", it->second.italic);
    }
}

wxBitmap InstructionSentenceFormatter::BitmapFromType(const std::string & type)
{
    gd::CommonBitmapManager * CommonBitmapManager = gd::CommonBitmapManager::Get();

    if ( type == "" ) return CommonBitmapManager->unknownBt;
    else if ( type == "expression" ) return CommonBitmapManager->expressionBt;
    else if ( gd::ParameterMetadata::IsObject(type) ) return CommonBitmapManager->objectBt;
    else if ( type == "automatism" ) return CommonBitmapManager->automatismBt;
    else if ( type == "operator" ) return CommonBitmapManager->signeBt;
    else if ( type == "relationalOperator" ) return CommonBitmapManager->signeBt;
    else if ( type == "file" ) return CommonBitmapManager->fileBt;
    else if ( type == "key" ) return CommonBitmapManager->keyBt;
    else if ( type == "mouse" ) return CommonBitmapManager->mouseBt;
    else if ( type == "yesorno" ) return CommonBitmapManager->yesnoBt;
    else if ( type == "police" ) return CommonBitmapManager->policeBt;
    else if ( type == "color" ) return CommonBitmapManager->colorBt;
    else if ( type == "trueorfalse" ) return CommonBitmapManager->trueOrFalseBt;
    else if ( type == "string" ) return CommonBitmapManager->texteBt;
    else if ( type == "musicfile" ) return CommonBitmapManager->musicBt;
    else if ( type == "soundfile" ) return CommonBitmapManager->soundBt;
    else if ( type == "password" ) return CommonBitmapManager->passwordBt;
    else if ( type == "layer" ) return CommonBitmapManager->layerBt;
    else if ( type == "joyaxis" ) return CommonBitmapManager->joyaxisBt;
    else if ( type == "objectvar" ) return CommonBitmapManager->varBt;
    else if ( type == "scenevar" ) return CommonBitmapManager->varBt;
    else if ( type == "globalvar" ) return CommonBitmapManager->varBt;

    return CommonBitmapManager->unknownBt;
}
#endif

}

#endif
