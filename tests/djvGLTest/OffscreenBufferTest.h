// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#include <djvTestLib/Test.h>

namespace djv
{
    namespace GLTest
    {
        class OffscreenBufferTest : public Test::ITest
        {
        public:
            OffscreenBufferTest(
                const System::File::Path& tempPath,
                const std::shared_ptr<System::Context>&);
            
            void run() override;
            
        private:
            void _enum();
        };
        
    } // namespace GLTest
} // namespace djv

