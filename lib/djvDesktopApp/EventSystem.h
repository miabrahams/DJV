// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUI/EventSystem.h>

#include <glm/vec2.hpp>

struct GLFWwindow;

namespace djv
{
    namespace UI
    {
        class Widget;

    } // namespace UI

    namespace Desktop
    {
        //! Desktop application event system.
        class EventSystem : public UI::EventSystem
        {
            DJV_NON_COPYABLE(EventSystem);

        protected:
            void _init(GLFWwindow *, const std::shared_ptr<System::Context>&);
            EventSystem();

        public:
            ~EventSystem() override;

            static std::shared_ptr<EventSystem> create(GLFWwindow *, const std::shared_ptr<System::Context>&);

            std::string getClipboard() const override;
            void setClipboard(const std::string&) override;

            void tick() override;

        protected:
            void _pushClipRect(const Math::BBox2f&) override;
            void _popClipRect() override;

            void _hover(System::Event::PointerMove&, std::shared_ptr<System::IObject>&) override;

        private:
            void _focus(bool);
            void _resize(const glm::ivec2&);
            void _contentScale(const glm::vec2&);
            void _redraw();
            void _hover(const std::shared_ptr<UI::Widget>&, System::Event::PointerMove&, std::shared_ptr<System::IObject>&);

            static void _focusCallback(GLFWwindow*, int);
            static void _resizeCallback(GLFWwindow*, int, int);
            static void _contentScaleCallback(GLFWwindow*, float, float);
            static void _redrawCallback(GLFWwindow *);
            static void _pointerEnterCallback(GLFWwindow*, int);
            static void _pointerCallback(GLFWwindow *, double, double);
            static void _buttonCallback(GLFWwindow *, int button, int action, int mods);
            static void _dropCallback(GLFWwindow *, int, const char **);
            static void _keyCallback(GLFWwindow *, int key, int scancode, int action, int modifiers);
            static void _charCallback(GLFWwindow *, unsigned int character, int modifiers);
            static void _scrollCallback(GLFWwindow *, double, double);

            DJV_PRIVATE();
        };

    } // namespace Desktop
} // namespace djv
