//------------------------------------------------------------------------------
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the names of the copyright holders nor the names of any
//   contributors may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#include <djvAVTest/EnumTest.h>

#include <djvAV/Enum.h>

using namespace djv::Core;
using namespace djv::AV;

namespace djv
{
    namespace AVTest
    {
        EnumTest::EnumTest(const std::shared_ptr<Core::Context>& context) :
            ITest("djv::AVTest::EnumTest", context)
        {}
        
        void EnumTest::run()
        {
            for (auto i : getSideEnums())
            {
                std::stringstream ss;
                ss << i;
                std::stringstream ss2;
                ss2 << "side string: " << _getText(ss.str());
                _print(ss2.str());
            }

            for (auto i : getTimeUnitsEnums())
            {
                std::stringstream ss;
                ss << i;
                std::stringstream ss2;
                ss2 << "time units string: " << _getText(ss.str());
                _print(ss2.str());
            }

            for (auto i : getAlphaBlendEnums())
            {
                std::stringstream ss;
                ss << i;
                std::stringstream ss2;
                ss2 << "alpha blend string: " << _getText(ss.str());
                _print(ss2.str());
            }
            
            {
                const AlphaBlend value = AlphaBlend::First;
                auto json = toJSON(value);
                AlphaBlend value2 = AlphaBlend::Count;
                fromJSON(json, value2);
                DJV_ASSERT(value == value2);
            }

            try
            {
                auto json = picojson::value(picojson::object_type, true);
                AlphaBlend value;
                fromJSON(json, value);
                DJV_ASSERT(false);
            }
            catch (const std::exception&)
            {}
        }

    } // namespace AVTest
} // namespace djv

