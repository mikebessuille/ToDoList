#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/richtext/richtextctrl.h>


class ListPanel; // forward declaration

class ToDoItem :
	public wxPanel
{
public:
	ToDoItem(wxWindow *parent, wxString itemStr );
	virtual ~ToDoItem();
	void OnIdle(wxIdleEvent &event);
	void Select();
	void Deselect();
	
private:
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);
	void OnDeleteButton(wxCommandEvent& event);

// Member Variables:
private:
	// wxStaticText  *m_wrappingText; // TEMPORARY for TEST
	wxRichTextCtrl  *m_wrappingText;
	wxButton		*m_DelButton;

	wxDECLARE_EVENT_TABLE();
};

