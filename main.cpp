#include <iostream>
#include <gtkmm.h>

#include "Gtk/DirWindow.h"

int main(int argc, char** argv)
{

    //Tworzenie obiektu aplikacji
    auto app = Gtk::Application::create(argc, argv, "wat.tom.esi");

    //Tworzenie budowniczego okien
    auto builder = Gtk::Builder::create();

    //Proba wczytania z pliku i przechwycenie wyjatkow
    try
    {
        builder->add_from_file("gui.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    DirWindow* window = nullptr;
    builder->get_widget_derived("okno1", window);
    if(window)
    {
        std::cout << "Poprawnie utworzono okno!" << std::endl;
    }
    else
    {
        std::cerr << "Nie mozna utworzyc okna!" << std::endl;
        return -1;
    }

    DirectoryManager::getEntries("D:\\");

    window->set_default_size(600,400);
    return app->run(*window);
}