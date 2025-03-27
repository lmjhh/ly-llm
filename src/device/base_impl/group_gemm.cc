#include "device/device_base.h"

namespace lytransformer {

GroupedGemmOutput DeviceBase::groupedGemm(const GroupedGemmParams& params) {
    // FT_LOG_DEBUG("use default group gemm");
    params.check();
    size_t num = params.A.size();
    std::vector<BufferPtr> output(num);
    for (int i = 0; i < num; i++) {
        BufferPtr c = nullptr;
        if (params.C != std::nullopt) {
            output[i] = gemm({*params.A[i],
                              *params.B[i],
                              std::nullopt,
                              params.C.value()[i],
                              DataType::TYPE_INVALID,
                              TransposeOperation::NONE,
                              TransposeOperation::NONE,
                              ActivationType::Identity,
                              1.0f,
                              1.0f});
        } else {
            output[i] = gemm({*params.A[i], *params.B[i]});
        }

    }
    return GroupedGemmOutput({std::move(output)});
}


} // namespace lytransformer

