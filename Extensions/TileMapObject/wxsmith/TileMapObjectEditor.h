//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: TileMapObjectEditor.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef TILEMAPOBJECTEDITOR_BASE_CLASSES_H
#define TILEMAPOBJECTEDITOR_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/scrolwin.h>
#include "../TileSetPanel.h"
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/checkbox.h>
#include "../TileMapPanel.h"

class TileMapObjectEditorBase : public wxDialog
{
protected:
    TileSetPanel* m_tileSetPanel;
    wxStaticText* m_staticText19;
    wxSpinCtrl* m_tileWidthSpin;
    wxStaticText* m_staticText43;
    wxSpinCtrl* m_tileHeightSpin;
    wxStaticText* m_staticText81;
    wxSpinCtrl* m_horizontalMarginsSpin;
    wxStaticText* m_staticText85;
    wxSpinCtrl* m_verticalMarginsSpin;
    wxTextCtrl* m_imageNameTextCtrl;
    wxButton* m_updateButton;
    wxStaticText* m_staticText105;
    wxChoice* m_layerChoice;
    wxCheckBox* m_hideUpperLayerCheck;
    TileMapPanel* m_tileMapPanel;
    wxStaticText* m_staticText93;
    wxSpinCtrl* m_mapWidthSpin;
    wxStaticText* m_staticText97;
    wxSpinCtrl* m_mapHeightSpin;
    wxStaticText* m_staticText101;
    wxButton* m_mapUpdateButton;
    wxStdDialogButtonSizer* m_stdBtnSizer60;
    wxButton* m_button62;
    wxButton* m_button64;

protected:
    virtual void OnUpdateClicked(wxCommandEvent& event) { event.Skip(); }
    virtual void OnLayerChoiceChanged(wxCommandEvent& event) { event.Skip(); }
    virtual void OnHideUpperLayerChecked(wxCommandEvent& event) { event.Skip(); }
    virtual void OnMapUpdateButtonClicked(wxCommandEvent& event) { event.Skip(); }

public:
    TileMapObjectEditorBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("TileMap Object Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX);
    virtual ~TileMapObjectEditorBase();
};

#endif
