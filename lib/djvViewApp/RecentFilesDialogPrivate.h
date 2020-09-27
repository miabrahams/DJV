// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvViewApp/RecentFilesDialog.h>

namespace djv
{
    namespace ViewApp
    {
        //! This class provides the recent files dialog popup menu.
        class RecentFilesMenu : public UI::Widget
        {
            DJV_NON_COPYABLE(RecentFilesMenu);

        protected:
            void _init(
                const std::map<std::string, std::shared_ptr<UI::Action> >&,
                const std::shared_ptr<System::Context>&);
            RecentFilesMenu();

        public:
            ~RecentFilesMenu() override;

            static std::shared_ptr<RecentFilesMenu> create(
                const std::map<std::string, std::shared_ptr<UI::Action> >&,
                const std::shared_ptr<System::Context>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

            void _initEvent(System::Event::Init&) override;

        private:
            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv
