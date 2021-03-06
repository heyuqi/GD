#ifndef OBJECTSEDITOR_H
#define OBJECTSEDITOR_H

//(*Headers(ObjectsEditor)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
//*)
#include <wx/toolbar.h>
#include <wx/image.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/gallery.h>
#include <wx/ribbon/toolbar.h>
#include <wx/srchctrl.h>
#include <string>
#include <vector>
#include "GDCore/PlatformDefinition/Object.h"
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Layout.h"
#include "GDCore/IDE/Dialogs/MainFrameWrapper.h"
#include "GDCore/IDE/Dialogs/LayoutEditorCanvas/LayoutEditorCanvasAssociatedEditor.h"
class LayoutEditorPropertiesPnl;

namespace gd {

/**
 * \brief Panel allowing to display and edit objects
 *
 * \todo Move this to GDCore.
 */
class ObjectsEditor: public wxPanel, public gd::LayoutEditorCanvasAssociatedEditor
{
public:

    /**
     * \brief Default constructor
     * \param parent wxWidgets parent window
     * \param project The project being edited
     * \param layout The layout being edited. Can be NULL.
     * \param mainFrameWrapper gd::MainFrameWrapper object
     */
    ObjectsEditor(wxWindow* parent, gd::Project & project, gd::Layout * layout, gd::MainFrameWrapper & mainFrameWrapper_);
    virtual ~ObjectsEditor();

    /**
     * \brief Refresh the editor.
     */
    void Refresh();

    /**
     * \brief Create the ribbon buttons for this editor
     */
    static void CreateRibbonPage(wxRibbonPage * page);

    /**
     * \brief Connect the ribbons buttons to this editor instance
     */
    void ConnectEvents();

    /**
     * \brief Enable or disable the editor.
     */
    virtual bool Enable(bool enable=true) { return wxWindow::Enable(enable); };

    /**
     * \brief Can be called by another editor ( Typically a gd::LayoutEditorCanvas, which has a list of editors
     * of type gd::LayoutEditorCanvasAssociatedEditor ) to notify that objects have been changed.
     */
    virtual void ObjectsUpdated() { Refresh(); };


    /**
     * \brief Can be used to associate a LayoutEditorPropertiesPnl, and the wxAuiManager used to display it,
     * to the editor.
     */
    void SetAssociatedPropertiesPanel(LayoutEditorPropertiesPnl * propPnl, wxAuiManager * manager);

protected:

    //(*Identifiers(ObjectsEditor)
    static const long ID_TREECTRL1;
    static const long ID_TEXTCTRL1;
    static const long idMenuModObj;
    static const long idMenuAddAuto;
    static const long idMenuProp;
    static const long idMenuAddObj;
    static const long idMenuDelObj;
    static const long idMenuModName;
    static const long ID_SETGLOBALITEM;
    static const long idMoveUp;
    static const long idMoveDown;
    static const long idMenuCopy;
    static const long idMenuCut;
    static const long idMenuPaste;
    static const long ID_MENUITEM7;
    static const long IdGroupEdit;
    static const long idModName;
    static const long ID_MENUITEM8;
    static const long idAddGroup;
    static const long idDelGroup;
    static const long ID_MENUITEM1;
    static const long ID_MENUITEM2;
    static const long ID_MENUITEM3;
    static const long ID_MENUITEM4;
    static const long ID_MENUITEM5;
    static const long ID_MENUITEM6;
    //*)
    static const long idRibbonAdd;
    static const long idRibbonDel;
    static const long idRibbonUp;
    static const long idRibbonDown;
    static const long idRibbonModProp;
    static const long idRibbonModName;
    static const long idRibbonCopy;
    static const long idRibbonCut;
    static const long idRibbonPaste;
    static const long idRibbonHelp;
    static const long idRibbonRefresh;

private:

    //(*Declarations(ObjectsEditor)
    wxMenuItem* MenuItem8;
    wxMenuItem* MenuItem7;
    wxSearchCtrl* searchCtrl;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem2;
    wxMenu groupContextMenu;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem4;
    wxTreeCtrl* objectsList;
    wxMenuItem* MenuItem11;
    wxMenuItem* copyMenuI;
    wxMenuItem* MenuItem13;
    wxMenuItem* MenuItem10;
    wxMenuItem* MenuItem12;
    wxMenuItem* moveUpMenuI;
    wxMenuItem* MenuItem3;
    wxMenu contextMenu;
    wxMenuItem* MenuItem6;
    wxMenuItem* moveDownMenuI;
    wxMenuItem* cutMenuI;
    wxMenu emptyContextMenu;
    wxMenu multipleContextMenu;
    wxMenuItem* MenuItem9;
    wxMenuItem* pasteMenuI;
    //*)

    //(*Handlers(ObjectsEditor)
    void OnobjectsListItemActivated(wxTreeEvent& event);
    void OnobjectsListItemRightClick(wxTreeEvent& event);
    void OnobjectsListItemMenu(wxTreeEvent& event);
    void OnobjectsListKeyDown(wxTreeEvent& event);
    void OnobjectsListBeginLabelEdit(wxTreeEvent& event);
    void OnobjectsListEndLabelEdit(wxTreeEvent& event);
    void OnobjectsListSelectionChanged(wxTreeEvent& event);
    void OnMenuEditObjectSelected(wxCommandEvent& event);
    void OnMenuPropertiesSelected(wxCommandEvent& event);
    void OnMenuRenameSelected(wxCommandEvent& event);
    void OnAddObjectSelected(wxCommandEvent& event);
    void OnDeleteSelected(wxCommandEvent& event);
    void OnMoveupSelected(wxCommandEvent& event);
    void OnMoveDownSelected(wxCommandEvent& event);
    void OnCopySelected(wxCommandEvent& event);
    void OnCutSelected(wxCommandEvent& event);
    void OnPasteSelected(wxCommandEvent& event);
    void OnAddGroupSelected(wxCommandEvent& event);
    void OnsearchCtrlText(wxCommandEvent& event);
    void OnSetGlobalSelected(wxCommandEvent& event);
    void OnSetFocus(wxFocusEvent& event);
    void OnobjectsListBeginDrag(wxTreeEvent& event);
    void OnMenuAddAutomatismSelected(wxCommandEvent& event);
    //*)
    void OnHelpSelected(wxCommandEvent& event);
    wxTreeItemId AddObjectsToList(gd::ClassWithObjects & objects, bool globalObject);
    wxTreeItemId AddGroupsToList(std::vector <gd::ObjectGroup> & groups, bool globalGroup);
    gd::Object * GetSelectedObject();
    gd::ObjectGroup * GetSelectedGroup();
    void UpdateAssociatedPropertiesPanel();

    //Tools functions
    bool HasGroupNamed(std::string name, std::vector<gd::ObjectGroup> & groups);
    gd::ObjectGroup & GetGroup(std::string name, std::vector<gd::ObjectGroup> & groups);
    void RemoveGroup(std::string name, std::vector<gd::ObjectGroup> & groups);

    wxImageList* objectsImagesList;

    gd::Project & project;
    gd::Layout * layout; ///< Layout edited. Can be NULL.
    gd::MainFrameWrapper & mainFrameWrapper;

    LayoutEditorPropertiesPnl * propPnl;
    wxAuiManager * propPnlManager;

    std::string renamedItemOldName;
    wxTreeItemId lastSelectedItem;
    wxTreeItemId latestObjItem;
    wxTreeItemId latestGlobalObjItem;
    wxTreeItemId latestGroupItem;
    wxTreeItemId latestGlobalGroupItem;
    wxTreeItemId substituteObjItem;
    wxTreeItemId substituteGroupItem;

    DECLARE_EVENT_TABLE()
};

}

#endif
