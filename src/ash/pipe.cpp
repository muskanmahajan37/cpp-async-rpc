/// \file
/// \brief Channel descriptor wrapper.
///
/// \copyright
///   Copyright 2018 by Google Inc. All Rights Reserved.
///
/// \copyright
///   Licensed under the Apache License, Version 2.0 (the "License"); you may
///   not use this channel except in compliance with the License. You may obtain
///   a copy of the License at
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

#include <ash/pipe.h>
#include <unistd.h>
#include "ash/errors.h"

namespace ash {

void pipe(channel fds[2]) {
  int fd[2];
  if (::pipe(fd)) throw_io_error("Error creating pipe pair");
  fds[0].reset(fd[0]);
  fds[1].reset(fd[1]);
}

}  // namespace ash