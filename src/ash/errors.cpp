/// \file
/// \brief Implementations of common exception classes.
///
/// \copyright
///   Copyright 2018 by Google Inc. All Rights Reserved.
///
/// \copyright
///   Licensed under the Apache License, Version 2.0 (the "License"); you may
///   not use this file except in compliance with the License. You may obtain a
///   copy of the License at
///
/// \copyright
///   http://www.apache.org/licenses/LICENSE-2.0
///
/// \copyright
///   Unless required by applicable law or agreed to in writing, software
///   distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
///   WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
///   License for the specific language governing permissions and limitations
///   under the License.

#include "ash/errors.h"

namespace ash {

namespace errors {

base_error::~base_error() {}

}  // namespace errors

void error_factory::throw_error(const char* error_class_name,
                                const char* what) {
  auto it = error_function_map_.find(error_class_name);
  if (it == error_function_map_.end()) {
    // If we don't know the error type, just use unknown_error.
    throw errors::unknown_error(what);
  }
  // Throw the specific error type otherwise.
  it->second(what);
}

void throw_io_error(const std::string& message, int code) {
  if (code == EINPROGRESS) {
    // This is just an ongoing non-blocking connection. Nothing to see here.
    return;
  }
  if (code == EAGAIN || code == EWOULDBLOCK) {
    throw errors::try_again("Try again");
  }
  throw errors::io_error(message + std::string(": ") + std::to_string(errno));
}

void throw_io_error(const std::string& message) {
  throw_io_error(message, errno);
}

}  // namespace ash
