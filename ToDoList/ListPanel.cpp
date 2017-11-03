#include "ListPanel.h"
#include "ToDoItem.h"
#include <memory>
#include <algorithm>


using namespace std;


//
// Event table for events handled by ListPanel
//
wxBEGIN_EVENT_TABLE(ListPanel, wxPanel)
	EVT_IDLE(ListPanel::OnIdle)
	EVT_LEFT_DOWN(ListPanel::OnMouseLeftDown)
	EVT_LEFT_UP(ListPanel::OnMouseLeftUp)
	EVT_LEAVE_WINDOW(ListPanel::OnMouseLeaveWindow)
wxEND_EVENT_TABLE()


ListPanel::ListPanel(wxFrame *frame, int x, int y, int w, int h) :
		wxScrolledWindow(frame, wxID_ANY, wxPoint(x, y), wxSize(w, h), wxVSCROLL )
{
	// TODO: populate from a loaded list.  (RichTextCtrl has LoadFile(), SaveFile() methods
	shared_ptr<ToDoItem> item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	item = make_shared<ToDoItem>(this);
	m_Items.push_back(item);
	item = make_shared<ToDoItem>(this);
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
		// Flags: Vertically not stretchable (0 to constructor)
		// Horizontally stretchable (Expand())
		// Left-aligned
		// with border width 5.
		topsizer->Add(	it.get(), // each ToDoItem panel
						wxSizerFlags(0).Left().Expand().Border(wxALL, 5));
	}
	// SetSizerAndFit(topsizer); // use the sizer for layout
	topsizer->SetSizeHints(this); // Should never resize smaller than the initial window... ?
	SetSizer(topsizer); // use the sizer for layout

	// Where 2nd param is the vertical size of the first ToDoItem, but doesn't include the border! (hence +10)
	SetScrollRate(0, m_Items.front().get()->GetBestSize().GetY() + 10 ); 
	// SetScrollRate(0, m_Items.front().get()->GetBestVirtualSize().GetY()); // Where 2nd param is the vertical size of the first ToDoItem
}


ListPanel::~ListPanel()
{
}


void ListPanel::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}


// Note!  This fires only when the user clicks in blank space in the ListPanel window.  If the
// User clicks on an individual TodoItem, the mouse event is trapped by that window (panel) and
// this ListPanel class never receives the event.
void ListPanel::OnMouseLeftDown(wxMouseEvent& event)
{
}

void ListPanel::OnMouseLeftUp(wxMouseEvent& WXUNUSED(event))
{
}

void ListPanel::OnMouseLeaveWindow(wxMouseEvent& event)
{
}


void ListPanel::SelectItem(ToDoItem *item)
{
	if (m_SelectedItem )
	{
		if (m_SelectedItem != item)
		{
			m_SelectedItem->Deselect();
			m_SelectedItem = item;
			item->Select();
		}
		// else do nothing; the item is already selected.
	}
	else
	{
		m_SelectedItem = item;
		item->Select();
	}
}

void ListPanel::AddItem() // TODO: Modify to take a string
{
	shared_ptr<ToDoItem> item = make_shared<ToDoItem>(this);
	if (item != nullptr)
	{
		m_Items.push_back(item);
		GetSizer()->Add(item.get(), wxSizerFlags(0).Left().Expand().Border(wxALL, 5));
	}
	//GetSizer()->RecalcSizes();
	//GetSizer()->Layout();
	Layout();
	//Refresh();
	// TODO:  HMMM, This DOES NOT WORK CORRECTLY!!!!
}


void ListPanel::DeleteItem(ToDoItem *item)
{
	// Deselect if necessary
	if (m_SelectedItem && m_SelectedItem == item )
	{
		m_SelectedItem->Deselect();
		m_SelectedItem = nullptr;
	}
	
	// Don't need to remove the item from the parent ListPanel or its sizer; those are done automatically
	// when the ToDoItem gets destroyed.
	/*
	// Find this item in the sizer list
	int index = GetIndex(item);
	if (index == -1)
		return;

	// Remove from sizer
	GetSizer()->Remove(index);

	// Remove from ListPanel
	// Already done by Destroy() in the ToDoItem!
	*/


	// No need to call Destroy() because it will get called by the window's destructor.
	// Also, can't call Destroy() from here because this method is called from ToDoItem itself, which is
	// still on the callstack. 
	// item->Destroy(); // Removes this from the current parent window, and from its sizer?

	
	// remove from m_Items; this should delete the item when this goes out of scope, as it's a shared_ptr
	// Erase-Remove idiom
	m_Items.erase(std::remove_if(m_Items.begin(), m_Items.end(),
		[item](shared_ptr<ToDoItem> const& i) { return i.get() == item; }),
		m_Items.end());



	// Relayout the Panel / Sizer...
	Layout();
}


int ListPanel::GetIndex(ToDoItem *item)
{
	int index = 0;
	const wxSizerItemList& children = GetSizer()->GetChildren();
	wxSizerItemList::const_iterator it = children.begin(), end = children.end();

	for (; it != end; ++it, index++ )
	{
		wxSizerItem* p_item = *it;
		if (p_item->GetWindow() == item )
		{
			return(index);
		}
	}
	return(-1);
}