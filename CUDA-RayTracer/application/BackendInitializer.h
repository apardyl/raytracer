#ifndef RAY_TRACER_BACKENDINITIALIZER_H
#define RAY_TRACER_BACKENDINITIALIZER_H

#include <string>
#include <array>

#include "backends/solid_color_cuda/SolidColorCudaBackend.h"
#include "backends/ray_tracing/RayTracingOpenMP.h"
#include "backends/Backend.h"

class BackendInitializer {
    static const std::string SOLID_COLOR_CUDA_NAME;
    static const std::string RAY_TRACER_OPENMP;
    static const std::string RANDOM_CUDA_NAME;
    static const std::array<std::string, 3> BACKEND_LIST;

public:
    static Backend *createBackend(std::string const &name);

    static std::string generateBackendListString();

    static bool isBackendNameValid(std::string const &backendName);
};

#endif //RAY_TRACER_BACKENDINITIALIZER_H
