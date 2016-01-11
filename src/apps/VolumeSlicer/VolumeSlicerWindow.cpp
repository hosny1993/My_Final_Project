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

/*
 * This function to test extracted central slice in frequency domain
 * then back to spatial domain by inverse 2dfft
 */
u_int8_t* VolumeSlicerWindow::xSliceFFT()
{

    /* variables definitions */
    u_int8_t* volumeData = volume_->getData();

    u_int64_t xSize = volume_->getSizeX();
    u_int64_t ySize = volume_->getSizeY();
    u_int64_t zSize = volume_->getSizeZ();

    size_t N0 = xSize;
    size_t N1 = ySize;
    size_t N2 = zSize;

    /* create buffer */
    size_t bufferSize = 2 * xSize * ySize * zSize * sizeof(float);
    float* fftData = new float[ bufferSize ];

    /* get volume data */
    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            for (int x = 0; x < xSize; x++)
            {
                unsigned int idx = 2 * (x + y * xSize + z * xSize * ySize);
                fftData[idx]  = volumeData[volume_->get1DIndex(x, y, z)];
                fftData[idx + 1] = 0.f;
            }
        }
    }

    /* perform fft on volume data */
    FFT::oclFFT* fft3 = new FFT::oclFFT();

    fftData = fft3->clFFT3D( CLFFT_SINGLE,
                             CLFFT_COMPLEX_INTERLEAVED,
                             CLFFT_FORWARD,
                             N0,N1,N2,
                             fftData );


    /* see current sizes */
    Dimensions3D dim3(N0, N1, N2);
    std::cout << "\nDim Size    : " << dim3.volumeSize() << std::endl;
    std::cout << "\nBuffer Size : " << bufferSize << std::endl;

    /* create complex volume */
    ComplexVolumeF* volume = new ComplexVolumeF(dim3, fftData);
    std::cout << "\nVolume Size : " << volume->getSizeInBytes() << std::endl;

    /* extract slice in x direction */
    ComplexImageF* img = volume->getSliceX(128); // central slice in x direction
    std::cout << "Image Size : " << img->getSizeInBytes() << std::endl;

    /* back transform slice into spatial domine */
    float* d2if = new float[ img->getSizeInBytes() ];
    d2if = volume->getInverseSlice(img);

    /* transform float data into unsigned int to display it*/
    u_int8_t* data = (u_int8_t*) malloc( sizeof(u_int8_t*) * img->getSizeInBytes());
    for (int i = 0; i < xSize * ySize ; i++)
    {
        double x = sqrt( pow(d2if[2 * i], 2) + pow(d2if[2 * i + 1], 2) );
        data[i] = x;
    }

    /* create qimage with extracted slice data */
    QImage xImage( data, xSize, ySize, QImage::Format_Grayscale8);
    ui->xProjectionImage->setPixmap(QPixmap::fromImage( xImage ));
    ui->xProjectionImage->show();

    return NULL;

}
