// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvDesktopApp/Application.h>

namespace djv
{
    namespace ViewApp
    {
        //! Viewer application.
        class Application : public Desktop::Application
        {
            DJV_NON_COPYABLE(Application);

        protected:
            void _init(std::list<std::string>&);
            Application();

        public:
            ~Application() override;

            static std::shared_ptr<Application> create(std::list<std::string>&);

            void run() override;

        protected:
            void _parseCmdLine(std::list<std::string>&) override;
            void _printUsage() override;

        private:
            void _parseCmdLineDJV(std::list<std::string>&);
            void _parseCmdLineMaya(std::list<std::string>&);
            void _printUsageDJV();
            void _printUsageMaya();

            void _readIcon(const std::string&);

            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv

