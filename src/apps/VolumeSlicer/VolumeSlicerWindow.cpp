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

//    /* in this code i try to read projection data and display it to check fft */
//    /* apply 2DFFT to data then 2DIFFT to check output of fft */

//    Image8* xProjection = volume_->getProjectionX(); // get x projection
//    u_int8_t* data = xProjection->getData();         // get reference to projection data

//    u_int64_t xSize = volume_->getSizeX();  // size in x
//    u_int64_t ySize = volume_->getSizeY();  // size in y

//    float* fftData = NULL;
//    size_t buffer_size  = 2 * xSize * ySize * sizeof(float*);
//    fftData = (float*) malloc( buffer_size);

//    for (int y = 0; y < ySize; y++)
//        for (int x = 0; x < xSize; x++)
//        {
//            unsigned int idx = 2 * (x + y * ySize );
//            fftData[idx] = 0.f;                                  // initialization
//            fftData[idx] += data[xProjection->get1DIndex(x, y)]; // read data
//            fftData[idx + 1] = 0.f; // imaginary to zero because we use interleaved complex
//        }

//    std::cout << "Data Before FFT : " << std::endl;
//    for (int idx = 0; idx < xSize * ySize; idx++) // print half of values 256 * 256
//    {
//        std::cout << idx << " : " <<fftData[idx] << std::endl;
//    }

//    FFT::oclFFT fft2;
//    fftData = fft2.clFFT2D( CLFFT_SINGLE,
//                            CLFFT_COMPLEX_INTERLEAVED,
//                            CLFFT_FORWARD,
//                            sizeof(xSize),
//                            sizeof(ySize),
//                            fftData);


//    fftData = fft2.clFFT2D( CLFFT_SINGLE,
//                            CLFFT_COMPLEX_INTERLEAVED,
//                            CLFFT_BACKWARD,
//                            sizeof(xSize),
//                            sizeof(ySize),
//                            fftData);

//    std::cout << "Data after FFT then inverseFFT : " << std::endl;
//    for (int idx = 0; idx < xSize * ySize; idx++) //print half of values 256 * 256
//    {
//        std::cout << idx << " : " <<fftData[idx] << std::endl;
//    }

    u_int8_t* volumeData = volume_->getData();

    u_int64_t xSize = volume_->getSizeX();
    u_int64_t ySize = volume_->getSizeY();
    u_int64_t zSize = volume_->getSizeZ();

    size_t N0 = sizeof(xSize);
    size_t N1 = sizeof(ySize);
    size_t N2 = sizeof(zSize);

    float* fftData = NULL;
    size_t bufferSize = 2 * xSize * ySize * zSize * sizeof(float*);
    fftData = (float*) malloc(bufferSize);

    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            for (int x = 0; x < xSize; x++)
            {
                unsigned int idx = 2 * (x + y * xSize + z * xSize * ySize);
                fftData[idx]  = 0.f;
                fftData[idx] += volumeData[volume_->get1DIndex(x, y, z)];
                fftData[idx + 1] = 0.f;
            }
        }
    }

    FFT::oclFFT* fft3 = new FFT::oclFFT();

    fftData = fft3->clFFT3D(CLFFT_SINGLE,
                            CLFFT_COMPLEX_INTERLEAVED,
                            CLFFT_FORWARD,
                            N0,N1,N2,
                            fftData
                            );


    fftData = fft3->clFFT3D(CLFFT_SINGLE,
                            CLFFT_COMPLEX_INTERLEAVED,
                            CLFFT_BACKWARD,
                            N0,N1,N2,
                            fftData
                            );
    for (int i = 0; i < xSize * ySize * zSize; i++)
    {
        //std::cout << i << " : " << fftData[i] << std::endl;
    }


    /*
    u_int64_t sliceIndex = 0;
    for (int z = 0; z < zSize; z++)
    {
        for (int y = 0; y < ySize; y++)
        {
            unsigned int idx = (128 + y * zSize + z * ySize * zSize);
            sliceData[sliceIndex] = sliceData[idx];
            sliceIndex++;
        }
    }

    fft3->clFFT2D(CLFFT_SINGLE,CLFFT_COMPLEX_INTERLEAVED,CLFFT_FORWARD, ySize, zSize,sl);

    Dimensions2D sliceDimensions( xSize, ySize );
    u_int8_t* sliceData = new u_int8_t[ xSize * ySize * zSize ];
    float maxValue = 0;

    for(u_int64_t i = 0; i < sliceDimensions.imageSize(); i++)
    {
        if( fftData[i] > maxValue ) maxValue = fftData[i];
    }

    for(u_int64_t i = 0; i < sliceDimensions.imageSize(); i++)
    {
        sliceData[i] = fftData[i] / maxValue * 255; // Now we have the data again of type u_int8_t
    }*/


    return NULL;

}
