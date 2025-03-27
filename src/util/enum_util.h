#pragma once
#include <string>
#include "core/type.h"

// corresponds to cublasOperation_t
enum TransposeOperation {
    NONE,
    TRANSPOSE,
};

std::string inline enumToString(TransposeOperation type) {
    if (type == NONE) {
        return "NONE";
    } else {
        return "TRANSPOSE";
    }
};

enum class KvCacheDataType : int8_t {
    BASE = 0,
    INT8 = 1,
    FP8  = 2
};

KvCacheDataType inline loadKvCacheDataTypeFromString(const std::string &str) {
    if (str == "base" || str == "fp16") {
        return KvCacheDataType::BASE;
    } else if (str == "int8") {
        return KvCacheDataType::INT8;
    } else if (str == "fp8") {
        return KvCacheDataType::FP8;
    } else {
        return KvCacheDataType::BASE;
    }
}

KvCacheDataType inline loadKvCacheDataTypeFromDataType(lytransformer::DataType type) {
    if (type == lytransformer::DataType::TYPE_INT8) {
        return KvCacheDataType::INT8;
    } else if (type == lytransformer::DataType::TYPE_FP8_E4M3) {
        return KvCacheDataType::FP8;
    } else {
        return KvCacheDataType::BASE;
    }
}