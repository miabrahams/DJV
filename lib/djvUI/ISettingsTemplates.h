//------------------------------------------------------------------------------
// Copyright (c) 2004-2019 Darby Johnston
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

#pragma once

#include <djvCore/ListObserver.h>
#include <djvCore/MapObserver.h>
#include <djvCore/PicoJSON.h>
#include <djvCore/ValueObserver.h>

namespace djv
{
    namespace UI
    {
        namespace Settings
        {
            //! Throws:
            //! - std::exception
            template<typename T>
            inline void read(const std::string & name, const picojson::object &, T &);
            template<typename T>
            inline void read(const std::string & name, const picojson::object &, std::shared_ptr<Core::ValueSubject<T> > &);
            template<typename T>
            inline void read(const std::string & name, const picojson::object &, std::shared_ptr<Core::ListSubject<T> > &);
            template<typename T>
            inline void read(const std::string & name, const picojson::object &, std::shared_ptr<Core::MapSubject<std::string, T> > &);

            template<typename T>
            inline void write(const std::string & name, const T &, picojson::object &);

        } // namespace Settings
    } // namespace UI
} // namespace djv

#include <djvUI/ISettingsTemplatesInline.h>