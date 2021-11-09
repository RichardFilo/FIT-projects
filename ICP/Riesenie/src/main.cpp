/**
 * @file main.cpp
 * @author Tomáš Lisický (xlisic01)
 * @brief Aplikácia. Spúšťa a zobrazuje hlavné okno.
 * @date 2021-05-06
 */

#include "mainwindow.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication ICPapp(argc, argv);

    MainWindow AppWindow;
    AppWindow.show();

    return ICPapp.exec();
}
