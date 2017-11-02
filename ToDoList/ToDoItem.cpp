#include "ToDoItem.h"
#include "ListPanel.h"

#include <wx/richtext/richtextctrl.h>


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ToDoItem, wxPanel)
	EVT_IDLE(ToDoItem::OnIdle)
	EVT_LEFT_DOWN(ToDoItem::OnMouseLeftDown)
	EVT_LEFT_UP(ToDoItem::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(ToDoItem::OnMouseLeaveWindow)
wxEND_EVENT_TABLE()



ToDoItem::ToDoItem(wxWindow *parent) :
	wxPanel(parent, wxID_ANY)
{
	wxString myText =	wxT("Hi, this is a really long line of text ")
						wxT("meant to demonstrate text wrapping. ")
						wxT("It's entirely useless.")
						wxT("\n\n")
						wxT("This is also supposed to demonstrate how ")
						wxT("to use static controls with line wrapping.");

	/*
	m_wrappingText = new wxStaticText(	this, wxID_ANY,
		myText,
		wxDefaultPosition,
		wxDefaultSize,
		wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
	);
	// This is required to ensure the min size isn't set to the full length of the string:
	// m_wrappingText->SetMinSize(wxSize(100, -1)); // -1 here means unspecified (use default)
	*/
	
	m_wrappingText = new wxRichTextCtrl(	this, wxID_ANY,
		myText,
		wxDefaultPosition,
		wxDefaultSize,
		// wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
		wxRE_MULTILINE
	);
	m_wrappingText->SetMinSize(wxSize(150, 50)); // for RichText otherwise it doesn't display correctly?
	m_wrappingText->SetEditable(false);


	// Specify the mouse handler for left-button-down to be handled first by the ToDoItem, not the
	// text control itself.
	m_wrappingText->Bind(wxEVT_LEFT_DOWN, &ToDoItem::OnMouseLeftDown, this);

	wxButton *but = new wxButton(this, wxID_ANY, wxT("Useless Button"));

	// Add all the elements of a ToDoItem into a horizontal sizer
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add( m_wrappingText, wxSizerFlags(1).Left().Border(wxALL, 5));
	sizer->Add(	but, wxSizerFlags(0).Right().Border(wxALL, 5)); // Right-align all buttons
	SetSizerAndFit( sizer ); // use the sizer for layout

	// TODO: find a nicer style...
	SetWindowStyle(wxBORDER_SUNKEN);
	SetBackgroundColour(wxColour(*wxLIGHT_GREY));
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
	// TODO: (Only if the item was already selected?  Determine that by changing SelectItem() to receive a return value?)
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
	Refresh();
}


void ToDoItem::Deselect()
{
	SetWindowStyle(wxBORDER_SUNKEN);
	SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	// refresh the RichTextCtrl so that any mouse selections are removed.
	m_wrappingText->SelectNone();
	m_wrappingText->SetEditable(false);
	Refresh();
}