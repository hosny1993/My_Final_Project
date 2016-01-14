#ifndef VOLUMESLICERWINDOW_H
#define VOLUMESLICERWINDOW_H

#include <QWidget>
#include <Volume.h>
#include <clFFT.h>
#include <FFT.h>
#include <stdio.h>
#include <ComplexImage.h>
#include <ComplexVolume.h>

namespace Ui {
class VolumeSlicerWindow;
}

class VolumeSlicerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit VolumeSlicerWindow( QWidget *parent = 0,
                                 std::string volumePrefix = "" );

    u_int8_t* xSliceFFT(const int xSlider) const;

    ~VolumeSlicerWindow();

private slots: // Slots

    /**
     * @brief on_xSlider_valueChanged
     * @param value
     */
    void on_xSlider_valueChanged( int value );

    /**
     * @brief on_ySlider_valueChanged
     * @param value
     */
    void on_ySlider_valueChanged( int value );

    /**
     * @brief on_zSlider_valueChanged
     * @param value
     */
    void on_zSlider_valueChanged( int value );

signals: // Signals

    /**
     * @brief xSliderChanged
     * @param value
     */
    void xSliderChanged( int value );

    /**
     * @brief ySliderChanged
     * @param value
     */
    void ySliderChanged( int value );

    /**
     * @brief zSliderChanged
     * @param value
     */
    void zSliderChanged( int value );

private: // Private functions

    /**
     * @brief initialize_
     */
    void initialize_();

private: // Private member variables

    /**
     * @brief volume_
     */
    Volume8* volume_;

    /**
     * @brief volume
     */
    ComplexVolumeF* complexVolume_ ;

    /**
     * @brief volumePrefix_
     */
    std::string volumePrefix_;

    /**
     * @brief ui
     */
    Ui::VolumeSlicerWindow *ui;

    /**
     * @brief fft3
     */
    FFT::oclFFT* fft3_;

    /**
     * @brief xSize_ , ySize_, zSize_
     */
    size_t xSize_, ySize_, zSize_;

};

#endif // VOLUMESLICERWINDOW_H
