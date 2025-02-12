// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUI/Widget.h>

namespace djv
{
    namespace UI
    {
        namespace Text
        {
            class LabelSizeGroup;

        } // namespace Text
    } // namespace UI

    namespace ViewApp
    {
        //! \todo Should this be configurable?
        const int textElide = 20;

        //! Color space configuration widget.
        class ColorSpaceConfigWidget : public UI::Widget
        {
            DJV_NON_COPYABLE(ColorSpaceConfigWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            ColorSpaceConfigWidget();

        public:
            ~ColorSpaceConfigWidget() override;

            static std::shared_ptr<ColorSpaceConfigWidget> create(const std::shared_ptr<System::Context>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

            void _initEvent(System::Event::Init&) override;

        private:
            void _widgetUpdate();

            DJV_PRIVATE();
        };

        //! Color space display widget.
        class ColorSpaceDisplayWidget : public UI::Widget
        {
            DJV_NON_COPYABLE(ColorSpaceDisplayWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            ColorSpaceDisplayWidget();

        public:
            ~ColorSpaceDisplayWidget() override;

            static std::shared_ptr<ColorSpaceDisplayWidget> create(const std::shared_ptr<System::Context>&);

            void setSizeGroup(const std::shared_ptr<UI::Text::LabelSizeGroup>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

            void _initEvent(System::Event::Init&) override;

        private:
            void _widgetUpdate();

            DJV_PRIVATE();
        };

        //! Color space view widget.
        class ColorSpaceViewWidget : public UI::Widget
        {
            DJV_NON_COPYABLE(ColorSpaceViewWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            ColorSpaceViewWidget();

        public:
            ~ColorSpaceViewWidget() override;

            static std::shared_ptr<ColorSpaceViewWidget> create(const std::shared_ptr<System::Context>&);

            void setSizeGroup(const std::shared_ptr<UI::Text::LabelSizeGroup>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

            void _initEvent(System::Event::Init&) override;

        private:
            void _widgetUpdate();

            DJV_PRIVATE();
        };

        //! Color space images widget.
        class ColorSpaceImagesWidget : public UI::Widget
        {
            DJV_NON_COPYABLE(ColorSpaceImagesWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            ColorSpaceImagesWidget();

        public:
            ~ColorSpaceImagesWidget() override;

            static std::shared_ptr<ColorSpaceImagesWidget> create(const std::shared_ptr<System::Context>&);

            void setSizeGroup(const std::shared_ptr<UI::Text::LabelSizeGroup>&);

        protected:
            void _preLayoutEvent(System::Event::PreLayout&) override;
            void _layoutEvent(System::Event::Layout&) override;

            void _initEvent(System::Event::Init&) override;

        private:
            void _valueUpdate();
            void _widgetUpdate();

            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv

