#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class ListPanel; // forward declaration

class ToDoItem :
	public wxPanel
{
public:
	ToDoItem(wxWindow *parent);
	virtual ~ToDoItem();
	void OnIdle(wxIdleEvent &event);
	void Select();
	void Deselect();
	
private:
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);

// Member Variables:
private:
	wxStaticText  *m_wrappingText; // TEMPORARY for TEST

	wxDECLARE_EVENT_TABLE();
};

