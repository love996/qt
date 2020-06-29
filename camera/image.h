#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>

enum class ImageType
{

};

struct Image
{
    std::shared_ptr<char[]> ptr;
    int height;
    int width;
    ImageType type;
};

struct CameraInfo
{
    std::string name;
    std::string description;
};

#endif // IMAGE_H
