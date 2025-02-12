// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUIComponents/SettingsIWidget.h>

namespace djv
{
    namespace ViewApp
    {
        //! Window geometry settings widget.
        class WindowGeometrySettingsWidget : public UIComponents::Settings::IWidget
        {
            DJV_NON_COPYABLE(WindowGeometrySettingsWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            WindowGeometrySettingsWidget();

        public:
            ~WindowGeometrySettingsWidget() override;

            static std::shared_ptr<WindowGeometrySettingsWidget> create(const std::shared_ptr<System::Context>&);

            std::string getSettingsGroup() const override;
            std::string getSettingsSortKey() const override;

        protected:
            void _initEvent(System::Event::Init&) override;

        private:
            DJV_PRIVATE();
        };

        //! Fullscreen monitor settings widget.
        class FullscreenMonitorSettingsWidget : public UIComponents::Settings::IWidget
        {
            DJV_NON_COPYABLE(FullscreenMonitorSettingsWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            FullscreenMonitorSettingsWidget();

        public:
            ~FullscreenMonitorSettingsWidget() override;

            static std::shared_ptr<FullscreenMonitorSettingsWidget> create(const std::shared_ptr<System::Context>&);

            std::string getSettingsGroup() const override;
            std::string getSettingsSortKey() const override;

        protected:
            void _initEvent(System::Event::Init&) override;

        private:
            void _widgetUpdate();

            DJV_PRIVATE();
        };
        
        //! Background image settings widget.
        class BackgroundImageSettingsWidget : public UIComponents::Settings::IWidget
        {
            DJV_NON_COPYABLE(BackgroundImageSettingsWidget);

        protected:
            void _init(const std::shared_ptr<System::Context>&);
            BackgroundImageSettingsWidget();

        public:
            ~BackgroundImageSettingsWidget() override;

            static std::shared_ptr<BackgroundImageSettingsWidget> create(const std::shared_ptr<System::Context>&);

            std::string getSettingsName() const override;
            std::string getSettingsGroup() const override;
            std::string getSettingsSortKey() const override;

        protected:
            void _initEvent(System::Event::Init&) override;
            void _updateEvent(System::Event::Update&) override;

        private:
            void _widgetUpdate();
            void _imageUpdate();

            DJV_PRIVATE();
        };

    } // namespace ViewApp
} // namespace djv

