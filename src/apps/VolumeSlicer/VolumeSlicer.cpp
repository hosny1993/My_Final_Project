#include <VolumeSlicerWindow.h>
#include <QApplication>
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication application( argc, argv);
    std::string volumePrefix = "/projects/volume-datasets/skull/skull";
    VolumeSlicerWindow window( NULL,  volumePrefix );
    window.show();
    return application.exec();
}
