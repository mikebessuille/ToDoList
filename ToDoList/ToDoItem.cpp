#include "ToDoItem.h"
#include "ListPanel.h"
#include "ControlIDs.h"
#include <wx/richtext/richtextctrl.h>


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ToDoItem, wxPanel)
	EVT_IDLE(ToDoItem::OnIdle)
	EVT_LEFT_DOWN(ToDoItem::OnMouseLeftDown)
	EVT_LEFT_UP(ToDoItem::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(ToDoItem::OnMouseLeaveWindow)
	EVT_BUTTON(ID_DELETE_BUTTON, ToDoItem::OnDeleteButton)
wxEND_EVENT_TABLE()



ToDoItem::ToDoItem(wxWindow *parent, wxString itemStr = wxT("Default String") ) :
	wxPanel(parent, wxID_ANY)
{
	m_wrappingText = new wxRichTextCtrl(	this, wxID_ANY,
		itemStr,
		wxDefaultPosition,
		wxDefaultSize,
		wxRE_MULTILINE
	);
	m_wrappingText->SetMinSize(wxSize(250, 50)); // for RichText otherwise it doesn't display correctly?
	// m_wrappingText->SetEditable(false);


	// Specify the mouse handler for left-button-down to be handled first by the ToDoItem, not the
	// text control itself.
	m_wrappingText->Bind(wxEVT_LEFT_DOWN, &ToDoItem::OnMouseLeftDown, this);

	m_DelButton = new wxButton(this, ID_DELETE_BUTTON, wxT("Delete"));

	// Add all the elements of a ToDoItem into a horizontal sizer
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add( m_wrappingText, wxSizerFlags(1).Left().Border(wxALL, 5));
	sizer->Add(m_DelButton, wxSizerFlags(0).Right().Border(wxALL, 5)); // Right-align all buttons
	SetSizerAndFit( sizer ); // use the sizer for layout

	// TODO: find a nicer style...
	// SetWindowStyle(wxBORDER_SUNKEN);
	// SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	Deselect();

}


ToDoItem::~ToDoItem()
{
}


void ToDoItem::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}


// These mouse events only fire when the user clicks on the border area of the TodoItem.  Otherwise
// the mouse event gets trapped by the text control or button (or whatever) that is in the window.
// Use Bind like this:  https://stackoverflow.com/questions/36629506/propagate-wxwindows-mouse-events-upwards

void ToDoItem::OnMouseLeftDown(wxMouseEvent& event)
{
	/*
	// initial press of mouse button sets the beginning of the selection
	m_selStart = DeviceCoordsToGraphicalChars(event.GetPosition());
	// set the cursor to the same position
	m_cursor = m_selStart;
	// draw/erase selection
	MyRefresh();
	*/

	ListPanel *parent = dynamic_cast<ListPanel*>(GetParent());
	if (parent)
	{
		parent->SelectItem(this);
	}

	// Pass the mouse message to the text control for processing, if the mouse was clicked on the text control itself.
	// TODO: Consider: (Only if the item was already selected?  Determine that by changing SelectItem() to receive a return value?)
	event.Skip(); // Causes the control's event handler to handle this event as well!
}

void ToDoItem::OnMouseLeftUp(wxMouseEvent& WXUNUSED(event))
{
	/*
	// this test is necessary
	if (HasCapture()) {
	// uncapture mouse
	ReleaseMouse();
	}
	*/
}

void ToDoItem::OnMouseLeaveWindow(wxMouseEvent& event)
{
	/*
	// if user is dragging
	if (event.Dragging() && event.LeftIsDown()) {
	// set the new cursor position
	m_cursor = DeviceCoordsToGraphicalChars(event.GetPosition());
	// draw/erase selection
	MyRefresh();
	// capture mouse to activate auto-scrolling
	if (!HasCapture()) {
	CaptureMouse();
	}
	}
	*/
}


void ToDoItem::Select()
{
	SetWindowStyle(wxBORDER_RAISED);
	SetBackgroundColour(wxColour(*wxWHITE));
	m_wrappingText->SetEditable(true);
	m_wrappingText->EnableVerticalScrollbar(true);
	m_wrappingText->SetBackgroundColour(wxColour(*wxWHITE));
	m_DelButton->Show();
	Layout();
	Refresh();
}


void ToDoItem::Deselect()
{
	SetWindowStyle(wxBORDER_SUNKEN);
	SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	// refresh the RichTextCtrl so that any mouse selections are removed.
	m_wrappingText->SelectNone();
	m_wrappingText->SetEditable(false);
	m_wrappingText->ShowPosition(0);
	m_wrappingText->EnableVerticalScrollbar(false);
	m_wrappingText->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	m_DelButton->Hide();
	Layout();
	Refresh();
}

void ToDoItem::OnDeleteButton(wxCommandEvent& event)
{
	ListPanel *parent = dynamic_cast<ListPanel*>(GetParent());
	if (parent)
	{
		parent->DeleteItem(this); // called to remove it from its m_Items list.
	}
}
