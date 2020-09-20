// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2019-2020 Darby Johnston
// All rights reserved.

#include <djvScene/InstancePrimitive.h>

using namespace djv::Core;

namespace djv
{
    namespace Scene
    {
        InstancePrimitive::InstancePrimitive()
        {}

        std::shared_ptr<InstancePrimitive> InstancePrimitive::create()
        {
            return std::shared_ptr<InstancePrimitive>(new InstancePrimitive);
        }

    } // namespace Scene
} // namespace djv

