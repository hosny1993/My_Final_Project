#include "VolumeSlicerWindow.h"
#include "ui_VolumeSlicerWindow.h"

VolumeSlicerWindow::VolumeSlicerWindow( QWidget *parent,
                                        std::string volumePrefix ) :
    QWidget( parent ),
    volumePrefix_( volumePrefix ),
    ui( new Ui::VolumeSlicerWindow )
{
    ui->setupUi( this );
    initialize_();

    // SIGNALS/SLOTS
    connect( this, SIGNAL( xSliderChanged( int )),
             this, SLOT( on_xSlider_valueChanged( int )));
    connect( this, SIGNAL( ySliderChanged( int )),
             this, SLOT( on_ySlider_valueChanged( int )));
    connect( this, SIGNAL( zSliderChanged( int )),
             this, SLOT( on_zSlider_valueChanged( int )));

    // Set the initial slices at the center of the volume.
    xSliderChanged( ui->xSlider->value());
    ySliderChanged( ui->ySlider->value());
    zSliderChanged( ui->zSlider->value());
}

VolumeSlicerWindow::~VolumeSlicerWindow()
{
    delete ui;
}

void VolumeSlicerWindow::initialize_()
{
    // Creates the volume, and initializes it
    volume_ = new Volume8( volumePrefix_, false );

    // Get the projections and display them
    Image8* xProjection = volume_->getProjectionX();
    QImage xImage(  xProjection->getData(),
                    xProjection->getSizeX(), xProjection->getSizeY(),
                    QImage::Format_Grayscale8 );
    ui->xProjectionImage->setPixmap(QPixmap::fromImage( xImage ));
    ui->xProjectionImage->show();

    Image8* yProjection = volume_->getProjectionY();
    QImage yImage(  yProjection->getData(),
                    yProjection->getSizeX(), yProjection->getSizeY(),
                    QImage::Format_Grayscale8 );
    ui->yProjectionImage->setPixmap(QPixmap::fromImage( yImage ));
    ui->yProjectionImage->show();

    Image8* zProjection = volume_->getProjectionZ();
    QImage zImage( zProjection->getData(),
                   zProjection->getSizeX(), zProjection->getSizeY(),
                   QImage::Format_Grayscale8 );
    ui->zProjectionImage->setPixmap( QPixmap::fromImage( zImage ));
    ui->zProjectionImage->show();
}

void VolumeSlicerWindow::on_xSlider_valueChanged( int value )
{
    const u_int64_t x = value / 100.f * ( volume_->getSizeX() - 1 );
    Image8* slice = volume_->getSliceX( x );
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->xSliceImage->setPixmap( QPixmap::fromImage( image ));
    ui->xSliceImage->show();
}

void VolumeSlicerWindow::on_ySlider_valueChanged( int value )
{
    const u_int64_t y = value / 100.f * ( volume_->getSizeY() - 1 );
    Image8* slice = volume_->getSliceY( y );
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->ySliceImage->setPixmap(QPixmap::fromImage( image ));
    ui->ySliceImage->show();
}

void VolumeSlicerWindow::on_zSlider_valueChanged( int value )
{
    const u_int64_t z = value / 100.f * ( volume_->getSizeZ() - 1 );
    Image8* slice = volume_->getSliceZ( z );
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->zSliceImage->setPixmap(QPixmap::fromImage( image ));
    ui->zSliceImage->show();
}
