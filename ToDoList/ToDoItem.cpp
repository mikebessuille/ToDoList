#include "ToDoItem.h"


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ToDoItem, wxPanel)
	EVT_IDLE(ToDoItem::OnIdle)
wxEND_EVENT_TABLE()


ToDoItem::ToDoItem(wxFrame *frame, int x, int y, int w, int h) :
	wxPanel(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h))
{

	m_wrappingText = new wxStaticText(this, wxID_ANY,
		wxT("Hi, this is a really long line of text ")
		wxT("meant to demonstrate text wrapping. ")
		wxT("It's entirely useless.")
		wxT("\n\n")
		wxT("This is also supposed to demonstrate how ")
		wxT("to use static controls with line wrapping."),
		wxDefaultPosition,
		wxSize(240, wxDefaultCoord)
	);
}


ToDoItem::~ToDoItem()
{
}


void ToDoItem::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}