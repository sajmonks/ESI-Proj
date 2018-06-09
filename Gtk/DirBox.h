//
// Created by Tomek on 09.06.2018.
//

#include <gtkmm.h>
#include <vector>

#ifndef ESIPROJ_DIRBOX_H
#define ESIPROJ_DIRBOX_H

class DirWindow;

#include "../Utils/DirectoryEntry.h"


class DirBox : public Gtk::Box {
public:
    DirBox(DirWindow* windowParent, DirectoryEntry& entry);

    void showInternal();
    void update();

    bool onRightReleasePressEvent(GdkEventButton* button);
    //bool on_button_press_event(GdkEventButton* button) override ;
private:
    DirectoryEntry              m_entry;
    Gtk::Label                  m_label;
    Gtk::Image                  m_image;
    DirWindow*                  m_window;
};

#endif //ESIPROJ_DIRBOX_H
