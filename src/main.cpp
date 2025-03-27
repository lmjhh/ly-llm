#include <stdio.h>

#include "core/type.h"
#include "core/buffer.h"

#include "device/weight.h"
#include "device/op_data.h"
#include "device/cpu_impl/cpu_device.h"

using namespace lytransformer;

int main() {
  DeviceBase *device = new CpuDevice(DeviceInitParams());
  printf("hello word! %s\n", getDataTypeStr(lytransformer::DataType::TYPE_FP16).c_str());
  return 0;
}