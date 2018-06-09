//
// Created by Tomek on 05.06.2018.
//
#include "DirWindow.h"
#include "DirBox.h"

DirWindow::DirWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) :
    Gtk::Window(cobject),  m_box(nullptr),
    //m_detailRadioButton({nullptr, nullptr, nullptr}), m_canShowFilesCheckButton(nullptr),
    m_iconComboText(nullptr),  m_builder(builder),
    m_openDirectoryItem(nullptr), m_exitProgramItem(nullptr),
    m_showHelpItem(nullptr), m_activeDirectory(""),
    m_activeDirectoryEntry(nullptr), m_executeButton(nullptr)
{
    m_builder->get_widget("radiobutton1", m_detailRadioButton[0]);
    m_builder->get_widget("radiobutton2", m_detailRadioButton[1]);
    m_builder->get_widget("radiobutton3", m_detailRadioButton[2]);
    m_builder->get_widget("checkbutton1", m_canShowFilesCheckButton);
    m_builder->get_widget("comboboxtext1", m_iconComboText);
    m_builder->get_widget("imagemenuitem1", m_openDirectoryItem);
    m_builder->get_widget("imagemenuitem5", m_exitProgramItem);
    m_builder->get_widget("imagemenuitem10", m_showHelpItem);
    m_builder->get_widget("imagemenuitem2", m_backItem);
    m_builder->get_widget("entry1", m_activeDirectoryEntry);
    m_builder->get_widget("button1", m_executeButton);
    m_builder->get_widget("box4", m_box);

    m_detailRadioButton[0]->signal_toggled().connect(
            sigc::bind( sigc::mem_fun(*this, &DirWindow::onDetailToggled),
                        2));

    m_detailRadioButton[1]->signal_toggled().connect(
            sigc::bind( sigc::mem_fun(*this, &DirWindow::onDetailToggled),
                        1));

    m_detailRadioButton[2]->signal_toggled().connect(
            sigc::bind( sigc::mem_fun(*this, &DirWindow::onDetailToggled),
                        0));

    m_canShowFilesCheckButton->signal_toggled().connect(
            sigc::bind( sigc::mem_fun(*this, &DirWindow::onShowFilesToggled),
                        m_canShowFilesCheckButton));

    m_iconComboText->signal_changed().connect(
            sigc::bind( sigc::mem_fun(*this, &DirWindow::onIconSizeChange),
                        m_iconComboText));

    m_openDirectoryItem->signal_activate().connect(
            sigc::bind (sigc::mem_fun(*this, &DirWindow::onMenuItemActivate), 0) );

    m_exitProgramItem->signal_activate().connect(
            sigc::bind (sigc::mem_fun(*this, &DirWindow::onMenuItemActivate), 1) );

    m_showHelpItem->signal_activate().connect(
            sigc::bind (sigc::mem_fun(*this, &DirWindow::onMenuItemActivate), 2) );

    m_backItem->signal_activate().connect(
            sigc::bind (sigc::mem_fun(*this, &DirWindow::onMenuItemActivate), 3) );

    m_executeButton->signal_clicked().connect(
            sigc::mem_fun(*this, &DirWindow::onExecuteButton));

    std::cout << "Okno zostalo utworzone" << std::endl;
}

void DirWindow::update() {
    for(auto& widget : m_boxDirectories) {
        widget.update();
    }
}

void DirWindow::unload() {
    for(auto& box : m_boxDirectories) {
        m_box->remove(box);
    }
    m_boxDirectories.clear();
}

void DirWindow::loadDirectory(std::string directory, bool history) {
    char blockedCharacters [] = {'\"', '*', '<', '>', '?', '/', '|'};
    //1st check
    for(int i = 0; i < directory.length(); i++) {
        for(int j = 0; j < 9; j++) {
            if(directory[i] == blockedCharacters[j]) {
                auto dialog = Gtk::MessageDialog(*this, "W ścieżce do folderu nie może być\n znaków specjalnych: \" * < > ? / |");
                dialog.run();
                return;
            }
        }
    }

    //2nd check
    auto directories = DirectoryManager::getEntries(directory);

    if(directories.size() == 0) {
        auto dialog = Gtk::MessageDialog(*this, "Nie znaleziono podanego katalogu.");
        dialog.run();
        return;
    }

    if(history == true && m_activeDirectory.length() > 1) {
        m_history.push_back( std::string(m_activeDirectory) );
    }
    m_activeDirectory = directory;
    m_activeDirectoryEntry->set_text(directory);

    for(auto dir : directories) {
        if (dir.getName().length() == 0)
            continue;

        if (!canShowFiles())
            if (!dir.isDirectory())
                continue;

        m_boxDirectories.push_back(DirBox(this, dir));
        m_box->add(m_boxDirectories[m_boxDirectories.size() - 1]);
        m_boxDirectories[m_boxDirectories.size() - 1].showInternal();
    }
}


