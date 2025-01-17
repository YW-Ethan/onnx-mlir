/*
 * SPDX-License-Identifier: Apache-2.0
 */

//====--------------- Diagnostic.hpp - Diagnostic Utilities ---------------===//
//
// Copyright 2022 The IBM Research Authors.
//
// =============================================================================
//
// This file contains common utilities for diagnosing incorrect ONNX operations.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "mlir/IR/Operation.h"
#include "mlir/Support/LogicalResult.h"
#include "llvm/ADT/Twine.h"

namespace onnx_mlir {

/// This convenience class groups diagnostic API used to emit error messages for
/// ONNX operators.
class Diagnostic {
public:
  Diagnostic() = delete;

  template <typename T>
  class Range {
    static_assert(std::is_arithmetic<T>::value, "Expecting an arithmetic type");
    friend class Diagnostic;
    T min;
    T max;

  public:
    Range(T min, T max) : min(min), max(max) {
      assert(min < max && "Illegal range");
    }
  };

  /// Verifies whether an attribute value is outside the supplied range.
  template <typename T>
  static mlir::LogicalResult attributeOutOfRange(mlir::Operation &op,
      const llvm::Twine &attrName, T attrVal, Range<T> validRange);
};

} // namespace onnx_mlir
