// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUI/Widget.h>

namespace djv
{
    namespace ViewApp
    {
        //! Tool drawer widget.
        class ToolDrawer : public UI::Widget
        {
            DJV_NON_COPYABLE(ToolDrawer);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            ToolDrawer();

        public:
            ~ToolDrawer() override;

            static std::shared_ptr<ToolDrawer> create(const std::shared_ptr<System::Context>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

        private:
            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv

