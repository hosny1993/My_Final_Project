#ifndef VOLUMEIMPORTER_H
#define VOLUMEIMPORTER_H

#include <Headers.hh>
#include <Typedefs.hh>

class VolumeImporter
{
public:

    VolumeImporter( const std::string& prefix );

public:

    /**
     * @brief getDimensions
     * @return
     */
    Dimensions getDimensions() const;

private:

    /**
     * @brief loadHeader_
     */
    void loadHeader_();

    void loadData_();

private:

    /**
     * @brief prefix_
     */
    std::string prefix_;

    /**
     * @brief dimensions_
     */
    Dimensions dimensions_;


};

#endif // VOLUMEIMPORTER_H
