#include "ToDoItem.h"
#include "ListPanel.h"


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
	m_wrappingText = new wxStaticText(this, wxID_ANY,
		wxT("Hi, this is a really long line of text ")
		wxT("meant to demonstrate text wrapping. ")
		wxT("It's entirely useless.")
		wxT("\n\n")
		wxT("This is also supposed to demonstrate how ")
		wxT("to use static controls with line wrapping."),
		wxDefaultPosition,
		wxDefaultSize,
		wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
	);
	// This is required to ensure the min size isn't set to the full length of the string:
	m_wrappingText->SetMinSize(wxSize(100, -1)); // -1 here means unspecified (use default)
	// Specify the mouse handler for left-button-down to be handled first by the ToDoItem, not the
	// text control itself.
	// TODO: Eventually change this to an editable control
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


/*
myName = new wxStaticText(this,-1,device.myName,wxPoint(10,10));
myName->Bind( wxEVT_RIGHT_DOWN, &cDevicePanel::OnRightClick, this );
myPower = new wxStaticText(this,-1,
wxString::Format("Power: %f kw",myDevice.myPower),
wxPoint(20,30));
myPower->Bind( wxEVT_RIGHT_DOWN, &cDevicePanel::OnRightClick, this );

myEnergy = new wxStaticText(this,-1,
wxString::Format("Energy: %f kwh",myDevice.myEnergy),
wxPoint(20,50));
myEnergy->Bind( wxEVT_RIGHT_DOWN, &cDevicePanel::OnRightClick, this );

// right clicks on panel background
Bind(wxEVT_RIGHT_DOWN,&cDevicePanel::OnRightClick, this );
*/

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

	// TODO:
	// Pass the mouse message to the text control for processing, if the mouse was clicked on the text control itself.
	// (Only if the item was already selected?  Determine that by changing SelectItem() to receive a return value?)
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
	Refresh();
}


void ToDoItem::Deselect()
{
	SetWindowStyle(wxBORDER_SUNKEN);
	SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	Refresh();
}