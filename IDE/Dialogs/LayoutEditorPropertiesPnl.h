/*
 * GDevelop IDE
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the GNU General Public License.
 */
#ifndef LAYOUTEDITORPROPERTIESPNL_H
#define LAYOUTEDITORPROPERTIESPNL_H

//(*Headers(LayoutEditorPropertiesPnl)
#include <wx/sizer.h>
#include <wx/propgrid/propgrid.h>
#include <wx/panel.h>
//*)
#include "GDCore/IDE/Dialogs/LayoutEditorCanvas/LayoutEditorCanvasAssociatedEditor.h"
#include "GDCore/IDE/Dialogs/InitialInstancesPropgridHelper.h"
#include "GDCore/IDE/Dialogs/ObjectsPropgridHelper.h"
namespace gd { class LayoutEditorCanvas; }
namespace gd { class InitialInstance; }
namespace gd { class Project; }
namespace gd { class Layout; }
namespace gd { class Object; }

/**
 * \brief Editor displaying a property grid for an initial instance or an object
 */
class LayoutEditorPropertiesPnl: public wxPanel, public gd::LayoutEditorCanvasAssociatedEditor
{
public:

    LayoutEditorPropertiesPnl(wxWindow* parent, gd::Project & project, gd::Layout & layout,
                              gd::LayoutEditorCanvas * layoutEditorCanvas, gd::MainFrameWrapper & mainFrameWrapper);
    virtual ~LayoutEditorPropertiesPnl();

    /**
     * Refresh the editor.
     */
    virtual void Refresh();

    /** \name Initial instances properties
     * Members functions related to displaying the properties of the instances selected in the layout editor canvas.
     * Most of these members functions are inherited from gd::LayoutEditorCanvasAssociatedEditor.
     */
    ///@{
    virtual void SelectedInitialInstance(const gd::InitialInstance & );
    virtual void DeselectedInitialInstance(const gd::InitialInstance & );
    virtual void DeselectedAllInitialInstance();
    virtual void InitialInstancesUpdated();
    virtual bool Enable(bool enable=true) { return wxWindow::Enable(enable); };
    ///@}

    /** \name Object properties
     * Members functions related to displaying the properties of an object selected in a objects editor
     */
    ///@{
    virtual void SelectedObject(gd::Object * object);
    virtual void ObjectsUpdated() {};
    ///@}

    //(*Declarations(LayoutEditorPropertiesPnl)
    wxPropertyGrid* grid;
    //*)

protected:

    //(*Identifiers(LayoutEditorPropertiesPnl)
    static const long ID_PROPGRID;
    //*)

private:

    //(*Handlers(LayoutEditorPropertiesPnl)
    void OnResize(wxSizeEvent& event);
    //*)
    void OnPropertySelected(wxPropertyGridEvent& event);
    void OnPropertyChanged(wxPropertyGridEvent& event);
    void OnMustRefresh(wxCommandEvent&);

    gd::Project & project;
    gd::Layout & layout;
    gd::LayoutEditorCanvas * layoutEditorCanvas; ///< Optional pointer to the LayoutEditorCanvas which is using this editor to display instances properties
    gd::Object * object; ///< The object being selected, if any, in the objects list editor using the property grid.

    gd::InitialInstancesPropgridHelper instancesHelper; ///< The class managing the property grid when a gd::InitialInstance is selected.
    gd::ObjectsPropgridHelper objectsHelper; ///< The class managing the property grid when a gd::Object is selected.

    bool displayInstancesProperties; ///< True if displaying the properties of a gd::InitialInstance, false for the properties of a gd::Object.

    static const wxEventType refreshEventType; ///< The internal wxWidgets event used to ask the grid to be refreshed.

    DECLARE_EVENT_TABLE()
};

#endif
