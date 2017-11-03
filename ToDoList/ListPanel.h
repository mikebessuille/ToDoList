#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>
#include <vector>
#include "ToDoItem.h"

using namespace std;

// class ListPanel :  public wxPanel
class ListPanel : public wxScrolledWindow
{
public:
	ListPanel(wxFrame *frame, int x = -1, int y = -1, int w = -1, int h = -1);
	virtual ~ListPanel();

	void OnIdle(wxIdleEvent &event);
	void SelectItem(ToDoItem *item);
	void AddItem(); // TODO: Modify to take a string
	void DeleteItem(ToDoItem *item);
	int GetIndex(ToDoItem *item);


private:
	void OnMouseLeftDown(wxMouseEvent& event);
	void OnMouseLeftUp(wxMouseEvent& event);
	void OnMouseLeaveWindow(wxMouseEvent& event);

// Controls
private:
	vector<shared_ptr<ToDoItem>> m_Items;
	ToDoItem* m_SelectedItem = nullptr;

	wxDECLARE_EVENT_TABLE();

};

