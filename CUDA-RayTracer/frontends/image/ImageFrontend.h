#ifndef RAY_TRACER_IMAGEFRONTEND_H
#define RAY_TRACER_IMAGEFRONTEND_H

#include <mutex>
#include <condition_variable>
#include "frontends/Frontend.h"

class ImageFrontend : public Frontend {
private:
    std::condition_variable condition;
    std::mutex lock;

    const std::string filename;
    std::unique_ptr<Bitmap> image = nullptr;
    bool shouldTerminate = false;

    void savePNG(Bitmap const &image);
public:
    explicit ImageFrontend(std::string const &filename);

    ~ImageFrontend() override;

    void run() override;

    void setImage(Bitmap image) override;

    bool isDaemon() override;

    void terminate() override;
};

#endif //RAY_TRACER_IMAGEFRONTEND_H
