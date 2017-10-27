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


ListPanel::ListPanel(wxFrame *frame, int x, int y, int w, int h) :
		wxScrolledWindow(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h))
{
	// TODO: populate from a loaded list
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
						wxSizerFlags(0).Left().Border(wxALL, 5));
	}
	SetSizerAndFit(topsizer); // use the sizer for layout
}


ListPanel::~ListPanel()
{
}


void ListPanel::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}