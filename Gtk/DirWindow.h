//
// Created by Tomek on 05.06.2018.
//
#include <iostream>
#include <string>
#include <gtkmm.h>

#ifndef ESIPROJ_DIRWINDOW_H
#define ESIPROJ_DIRWINDOW_H

class DirBox;

#include "../Utils/DirectoryManager.h"

class DirWindow : public Gtk::Window {
public:
    DirWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

    inline int getIconSize() {
        return m_iconSize;
    }

    inline int getDetailLevel() {
        return m_detailLevel;
    }

    inline bool canShowFiles() {
        return m_showFiles;
    }
private:
    Glib::RefPtr<Gtk::Builder>  m_builder;
    std::vector<DirBox>         m_boxDirectories;
    std::string                 m_activeDirectory;
    std::vector<std::string>    m_history;

    Gtk::Box*                   m_box;
    Gtk::RadioButton*           m_detailRadioButton [3];
    Gtk::CheckButton*           m_canShowFilesCheckButton;
    Gtk::ComboBoxText*          m_iconComboText;
    Gtk::ImageMenuItem*         m_openDirectoryItem;
    Gtk::ImageMenuItem*         m_exitProgramItem;
    Gtk::ImageMenuItem*         m_showHelpItem;
    Gtk::ImageMenuItem*         m_backItem;
    Gtk::Entry*                 m_activeDirectoryEntry;
    Gtk::Button*                m_executeButton;

    int                         m_detailLevel = 2;
    int                         m_iconSize = 1;
    bool                        m_showFiles = true;

    void update();
    void loadDirectory(std::string directory, bool history = true);
    void unload();

    inline void onDetailToggled(int pos) {
        if(pos != m_detailLevel) {
            m_detailLevel = pos;
            update();
            std::cout << "Rodzaj detali: " << m_detailLevel << std::endl;
        }
    }

    inline void onShowFilesToggled(Gtk::CheckButton* button) {
        m_showFiles = !m_showFiles;
        update();

        unload();
        if(m_activeDirectory.length() > 1) {
            loadDirectory(m_activeDirectory, false);
        }

        std::cout << "Pokazywanie plikow: " << m_showFiles << std::endl;
    }

    inline void onIconSizeChange(Gtk::ComboBoxText* button) {
        if(m_iconSize != button->get_active_row_number()) {
            m_iconSize = button->get_active_row_number();
            update();
            std::cout << "Wielkosc ikon: " << m_iconSize << std::endl;
        }
    }

    inline void onMenuItemActivate(int item) {
        //Open directory
        if(item == 0) {
            auto dialog = Gtk::FileChooserDialog("Wybierz folder do uruchomienia komendy dir",
                    Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
            dialog.set_transient_for(*this);
            dialog.add_button("Wybierz", Gtk::RESPONSE_OK);
            dialog.add_button("_Nie wybieraj", Gtk::RESPONSE_CANCEL);

            auto result = dialog.run();
            if(result == Gtk::RESPONSE_OK) {
                std::cout << "Wybrano: " <<  dialog.get_filename() << std::endl;
                unload();
                loadDirectory(dialog.get_filename());
            }
            else if (result == Gtk::RESPONSE_CANCEL){
                std::cout << "Anulowano wybór" << std::endl;
            }
            return;
        }

        //Exit
        if(item == 1) {
            exit(0);
            return;
        }

        //About
        if(item == 2) {
            auto dialog = Gtk::MessageDialog(*this, "Program wykonany przez Tomasza Kuczewskiego grupa I7G3S4");
            dialog.set_secondary_text("Aby otworzyć katalog należy nacisnąć zakładkę Plik->Otwórz a następnie wybrać katalog.\n\n"
                                      "Można również ręcznie wprowadzić ścieżke do katalogu a następnie nacisnąć przycisk Wykonaj");
            dialog.run();
            return;
        }

        //Back
        if(item == 3) {
            if(m_history.size() > 0) {
                auto dir = m_history.back();
                m_history.pop_back();
                unload();
                loadDirectory(dir, false);
                std::cout << "Ladowanie z historii." << std::endl;
            }
            else {
                std::cout << "Nie ma historii." << std::endl;
            }
        }
    }

    inline void onExecuteButton() {
        unload();
        loadDirectory(m_activeDirectoryEntry->get_text());
    }
};


#endif //ESIPROJ_DIRWINDOW_H
