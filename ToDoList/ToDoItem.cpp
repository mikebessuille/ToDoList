#include "ToDoItem.h"


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ToDoItem, wxPanel)
	EVT_IDLE(ToDoItem::OnIdle)
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
		wxT("to use static controls with line wrapping.") //,
		// wxDefaultPosition,
		// wxSize(240, wxDefaultCoord)  // this causes the line to wrap.
	);

	/*
	m_wrappingText = new wxStaticText(this, wxID_ANY,
	wxT("Hi, this is a really long line of text ")
	wxT("meant to demonstrate text wrapping. ")
	wxT("It's entirely useless.")
	wxT("\n\n")
	wxT("This is also supposed to demonstrate how ")
	wxT("to use static controls with line wrapping."),
	wxDefaultPosition,
	wxSize(240, wxDefaultCoord)  // this causes the line to wrap.
	);
	*/

	wxButton *but = new wxButton(this, wxID_ANY, wxT("Useless Button"));

	// TODO: I don't have the stretch / proportion / ... values set correctly for this sizer
	// or the topsizer that's in ListPanel.  It's not correctly stretching the controls
	// depending on the size of the frame.


	// Add all the elements of a ToDoItem into a horizontal sizer
	wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add( m_wrappingText, wxSizerFlags(1).Left().Border(wxALL, 5));
	sizer->Add(	but, wxSizerFlags(0).Left().Border(wxALL, 5));
	SetSizerAndFit( sizer ); // use the sizer for layout
}


ToDoItem::~ToDoItem()
{
}


void ToDoItem::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}