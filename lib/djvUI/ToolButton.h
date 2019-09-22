// Copyright (c) 2017-2018 Darby Johnston
// All rights reserved.
//
// See LICENSE.txt for licensing information.

#pragma once

#include <djvUI/IButton.h>

namespace djv
{
    namespace UI
    {
        namespace Button
        {
            //! This class provides a button for use with toolbars.
            class Tool : public IButton
            {
                DJV_NON_COPYABLE(Tool);

            protected:
                void _init(const std::shared_ptr<Core::Context>&);
                Tool();

            public:
                virtual ~Tool();

                static std::shared_ptr<Tool> create(const std::shared_ptr<Core::Context>&);

                void setIcon(const std::string &);
                void setCheckedIcon(const std::string&);

                std::string getText() const;
                void setText(const std::string &);

                TextHAlign getTextHAlign() const;
                void setTextHAlign(TextHAlign);

                const std::string& getFont() const;
                const std::string& getFontFace() const;
                MetricsRole getFontSizeRole() const;
                void setFont(const std::string &);
                void setFontFace(const std::string &);
                void setFontSizeRole(MetricsRole);

                const Layout::Margin & getInsideMargin() const;
                void setInsideMargin(const Layout::Margin &);

                void setTextFocusEnabled(bool);

                void setChecked(bool) override;
                void setForegroundColorRole(ColorRole) override;

                void addAction(const std::shared_ptr<Action>&) override;
                void removeAction(const std::shared_ptr<Action>&) override;
                void clearActions() override;
                bool acceptFocus(TextFocusDirection) override;

            protected:
                void _preLayoutEvent(Core::Event::PreLayout &) override;
                void _layoutEvent(Core::Event::Layout &) override;
                void _paintEvent(Core::Event::Paint&) override;
                void _buttonPressEvent(Core::Event::ButtonPress&) override;
                void _keyPressEvent(Core::Event::KeyPress&) override;
                void _textFocusEvent(Core::Event::TextFocus&) override;
                void _textFocusLostEvent(Core::Event::TextFocusLost&) override;

            private:
                void _actionUpdate();
                void _iconUpdate();

                DJV_PRIVATE();
            };

        } // namespace Button

        typedef Button::Tool ToolButton;

    } // namespace UI
} // namespace djv
