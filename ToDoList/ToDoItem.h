#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class ToDoItem :
	public wxPanel
{
public:
	ToDoItem(wxFrame *frame, int x, int y, int w, int h);
	virtual ~ToDoItem();
	void OnIdle(wxIdleEvent &event);

	
// Member Variables:
private:
	wxStaticText  *m_wrappingText; // TEMPORARY for TEST

	wxDECLARE_EVENT_TABLE();
};

