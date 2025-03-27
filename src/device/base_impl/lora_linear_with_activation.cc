#include "devices/device_base.h"
#include "devices/op_data.h"

using namespace std;

namespace lytransformer {
    BufferPtr DeviceBase::loraLinearWithActivation(const LoraLinearWithActivationParams& params) {
        BufferPtr output = loraLinear(params.lora_linear_params).output;
        // create new activation from output;
        auto act_params = params.activation_params;
        act_params.states = output;
        return activation(act_params);
    }
} // namespace lytransformer