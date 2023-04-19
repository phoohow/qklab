#include "LQt.h"
#include <iostream>
#include <string>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.resize(600, 600);
    window.setWindowTitle("Hello, Qt!");
    window.setWindowIcon(QIcon("path/icon.png"));

    QPushButton button("Hello, Qt!", &window);
    window.show();

    return app.exec();
}