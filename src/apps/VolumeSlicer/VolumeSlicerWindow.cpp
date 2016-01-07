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

    xSliceFFT();
}

VolumeSlicerWindow::~VolumeSlicerWindow()
{
    delete ui;
}

void VolumeSlicerWindow::initialize_()
{
    volume_ = new Volume8( volumePrefix_, false );

    Image8* xProjection = volume_->getProjectionX();

    QImage xImage( xProjection->getData(),
                    xProjection->getSizeX(), xProjection->getSizeY(),
                    QImage::Format_Grayscale8);
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
    /* to slice-theorm */
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->xSliceImage->setPixmap( QPixmap::fromImage( image ));
    ui->xSliceImage->show();
}

void VolumeSlicerWindow::on_ySlider_valueChanged( int value )
{
    const u_int64_t y = value / 100.f * ( volume_->getSizeY() - 1 );
    Image8* slice = volume_->getSliceY( y );
    /* to slice-theorm */
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->ySliceImage->setPixmap(QPixmap::fromImage( image ));
    ui->ySliceImage->show();
}

void VolumeSlicerWindow::on_zSlider_valueChanged( int value )
{
    const u_int64_t z = value / 100.f * ( volume_->getSizeZ() - 1 );
    Image8* slice = volume_->getSliceZ( z );
    /* to slice-theorm */
    QImage image( slice->getData(), slice->getSizeX(), slice->getSizeY(),
                  QImage::Format_Grayscale8 );
    ui->zSliceImage->setPixmap(QPixmap::fromImage( image ));
    ui->zSliceImage->show();
}

u_int8_t* VolumeSlicerWindow::xSliceFFT()
{

//    u_int8_t* volumeData = volume_->getData();

//    u_int64_t xSize = volume_->getSizeX();
//    u_int64_t ySize = volume_->getSizeY();
//    u_int64_t zSize = volume_->getSizeZ();

//    size_t N0 = xSize;
//    size_t N1 = ySize;
//    size_t N2 = zSize;

//    float* fftData = NULL;
//    size_t bufferSize = 2 * xSize * ySize * zSize * sizeof(float*);
//    fftData = (float*) malloc(bufferSize);

//    for (int z = 0; z < zSize; z++)
//    {
//        for (int y = 0; y < ySize; y++)
//        {
//            for (int x = 0; x < xSize; x++)
//            {
//                unsigned int idx = 2 * (x + y * xSize + z * xSize * ySize);
//                fftData[idx]  = volumeData[volume_->get1DIndex(x, y, z)];
//                fftData[idx + 1] = 0.f;
//            }
//        }
//    }

//    FFT::oclFFT* fft3 = new FFT::oclFFT();

//    fftData = fft3->clFFT3D(CLFFT_SINGLE,
//                            CLFFT_COMPLEX_INTERLEAVED,
//                            CLFFT_FORWARD,
//                            N0,N1,N2,
//                            fftData
//                            );


//    fftData = fft3->clFFT3D(CLFFT_SINGLE,
//                            CLFFT_COMPLEX_INTERLEAVED,
//                            CLFFT_BACKWARD,
//                            N0,N1,N2,
//                            fftData
//                            );


//    u_int8_t* data = (u_int8_t*) malloc( sizeof(u_int8_t*) * N0 * N1 * N2);
//    for (int i = 0; i < xSize * ySize * zSize; i++)
//    {
//        double x = sqrt( pow(fftData[2 * i], 2) + pow(fftData[2 * i + 1], 2) );
//        data[i] = x;

//        //data[i] = fftData[2 * i];
//    }

//    QImage xImage( data, xSize, ySize, QImage::Format_Grayscale8);
//    ui->xProjectionImage->setPixmap(QPixmap::fromImage( xImage ));
//    ui->xProjectionImage->show();

//    return NULL;

}
