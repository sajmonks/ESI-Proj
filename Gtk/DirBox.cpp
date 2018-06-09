//
// Created by Tomek on 09.06.2018.
//
#include "DirBox.h"
#include "DirWindow.h"

DirBox::DirBox(DirWindow* windowParent, DirectoryEntry& entry) :
        Gtk::Box(),
        m_window(windowParent),
        m_entry(std::move(entry))
{

    this->signal_button_release_event().connect(
            sigc::mem_fun(*this, &DirBox::onRightReleasePressEvent)
    );

    update();
    this->set_spacing(5);
    this->add(m_image);
    this->add(m_label);
}

void DirBox::showInternal() {
    m_image.show();
    m_label.show();
    this->show();
}

void DirBox::update() {

    //Updating details of files
    auto text = std::string();

    if(m_window->getDetailLevel() == 0) {
        text += "Nazwa pliku: " + m_entry.getName();
    }
    if(m_window->getDetailLevel() == 1) {
        text += "Nazwa pliku: " + m_entry.getName();

        if(!m_entry.isDirectory())
            text += "\nRozmiar pliku: " + m_entry.getSize() + " bajtów";
    }
    if(m_window->getDetailLevel() == 2) {
        text += "Nazwa pliku: " + m_entry.getName();

        if(!m_entry.isDirectory())
            text += "\nRozmiar pliku: " + m_entry.getSize() + " bajtów";

        text += "\nData modyfikacji: " + m_entry.getModifyDate();
    }
    m_label.set_text(text);
    //-------------------------------------------
    //Updating icons of files
    std::string filesEnd [] = {"_s.png", "_m.png", "_b.png"};
    if(m_entry.isDirectory()) {
        m_image.set("directory" + filesEnd[ m_window->getIconSize() ] );
        m_image.show();
    }
    else {
        m_image.set("file" + filesEnd[ m_window->getIconSize() ] );
        m_image.show();
    }
    //-------------------------------------------
}

bool DirBox::onRightReleasePressEvent(GdkEventButton *button) {
    std::cout << "TEST 2" << std::endl;
    return true;
}
