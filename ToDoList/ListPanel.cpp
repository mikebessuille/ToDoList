#include "ListPanel.h"
#include "ToDoItem.h"
#include <memory>


using namespace std;


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ListPanel, wxPanel)
	EVT_IDLE(ListPanel::OnIdle)
wxEND_EVENT_TABLE()

/*
ListPanel::ListPanel(wxFrame *frame, int x, int y, int w, int h) :
	wxPanel(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h))
*/
ListPanel::ListPanel(wxFrame *frame, int x, int y, int w, int h) :
		wxScrolledWindow(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h))
{
	// TODO: populate from a loaded list

	// TODO: want this to take 'this' rather than frame
	shared_ptr<ToDoItem> item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	for (auto &it : m_Items)
	{
		// Flags: Vertically stretchable, Horizontally not stretchable with border width 5.
		topsizer->Add(	it.get(), // each ToDoItem panel
						wxSizerFlags(0).Top().Border(wxALL, 5));
	}
	SetSizerAndFit(topsizer); // use the sizer for layout and size window
							  // accordingly and prevent it from being resized
							  // to smaller size

	/*
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	// create text ctrl with minimal size 100x60
	topsizer->Add(
		new wxTextCtrl(this, -1, "My text.", wxDefaultPosition, wxSize(100, 60), wxTE_MULTILINE),
		1,            // make vertically stretchable
		wxEXPAND |    // make horizontally stretchable
		wxALL,        //   and make border all around
		10);         // set border width to 10
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	button_sizer->Add(
		new wxButton(this, wxID_OK, "OK"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);        // set border width to 10
	button_sizer->Add(
		new wxButton(this, wxID_CANCEL, "Cancel"),
		0,           // make horizontally unstretchable
		wxALL,       // make border all around (implicit top alignment)
		10);        // set border width to 10
	topsizer->Add(
		button_sizer,
		0,                // make vertically unstretchable
		wxALIGN_CENTER); // no border and centre horizontally
	SetSizerAndFit(topsizer); // use the sizer for layout and size window
							  // accordingly and prevent it from being resized
							  // to smaller size
	*/
}


ListPanel::~ListPanel()
{
}


void ListPanel::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}


// Subclass wxPanel and use standard wxWidgets controls(wxStaticText, wxStaticBitmaps, wxGauge etc)
// to build the content of one list entry.For the actual list use a wxScrolledWindow
// and for each list entry create a new entry panel and add it to a vertical box sizer.