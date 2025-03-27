#pragma once

#include "device/device_op.h"
#include "device/device_data.h"
#include "device/buffer_manager.h"
#include "device/op_data.h"
#include "core/event.h"
// #include "maga_transformer/cpp/disaggregate/cache_store/CacheStore.h"

namespace lytransformer {

class DeviceBase : public DeviceOps {
public:
    DeviceBase(const DeviceInitParams& params);

    virtual void init();
    // std::shared_ptr<rtp_llm::CacheStore> cacheStore();

    // Init and preRun(NormalEngine::loop()) are executed in two different threads, some environments
    // needs to be reset again in a new thread(such as cudaSetDevice,
    // otherwise it will be executed in default cudaDevice 0) so we provide a preRun() to do this.
    virtual void preRun() {}
    virtual DeviceProperties getDeviceProperties() = 0;
    virtual MemoryStatus getDeviceMemoryStatus();
    DeviceStatus getDeviceStatus();
    // virtual torch::Device getTorchDevice() {
    //     throw std::runtime_error("getTorchDevice() is not implemented");
    // }

    void traceMemoryUsage();
    void setTraceMemory(bool trace_memory);
    BufferPtr allocateBuffer(const BufferParams& params, const BufferHints& hints = {});
    BufferPtr allocateBufferLike(const Buffer& buffer,
                                 const AllocationType atype = AllocationType::DEVICE,
                                 const BufferHints& hints = {});
    virtual void syncAndCheck();
    virtual void syncCommunication(bool timeout = true);
    virtual DevicePrepOutput prepareModelRun(const DevicePrepParams& params);
    virtual DeviceEventPtr createEvent();
    // void setCacheStore(std::shared_ptr<rtp_llm::CacheStore> cache_store);
    // void writeCacheStore(const AttentionModuleParams& params);
    DeviceInitParams initParams() {
        return init_params_;
    }

public:
    // device-independence op implementations
    CloneOutput clone(const CloneParams& params) override;
    SelectOutput select(const SelectParams& params) override;
    ConcatOutput concat(const ConcatParams& params) override;
    AttentionLayerOutput attentionLayer(const AttentionLayerParams& params) override;
    FfnLayerOutput ffnLayer(const FfnLayerParams& params) override;
    LoraLinearOutput loraLinear(const LoraLinearParams& params) override;
    LossOutput loss(const LossParams& params) override;
    MaskOutput attentionMask(const MaskParams& params) override;
    BufferPtr loraLinearWithActivation(const LoraLinearWithActivationParams& params) override;
    BufferPtr mhaQKVGemm(const AttentionLayerParams& params) override;
    GroupedGemmOutput groupedGemm(const GroupedGemmParams& params) override;
    MultimodalEmbeddingOutput multimodalEmbedding(const MultimodalEmbeddingParams& params) override;

protected:
    BufferStatus queryBufferStatus();
    AllocationType getMemAllocationType(const MemoryType type);

private:
    DeviceBase(const DeviceBase&) = delete;
    DeviceBase& operator=(const DeviceBase&) = delete;
    DeviceBase(DeviceBase&&)                 = delete;
    DeviceBase& operator=(DeviceBase&&) = delete;

private:
    virtual IAllocator* getAllocator() = 0;
    virtual IAllocator* getHostAllocator() = 0;

protected:
    int device_id_;
    DeviceInitParams init_params_;
    // std::shared_ptr<rtp_llm::CacheStore> cache_store_;

private:
    std::unique_ptr<BufferManager> buffer_manager_;
};

};  // namespace lytransformer
