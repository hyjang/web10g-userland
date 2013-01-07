#include "mainwindow.hpp"
#include "EstatsView.hpp"
#include <QPixmap>
#include <QIcon>

int main(int argc, char *argv[])
{
    EApplication app(argc, argv);
    app.setApplicationName("estats-view");

    QPixmap pix = QPixmap("./E.png");
    QIcon icon = QIcon(pix);

    app.setWindowIcon(icon);

    MainWindow window;
    window.setMinimumSize(700,300);
    window.show();
    return app.exec();
}
