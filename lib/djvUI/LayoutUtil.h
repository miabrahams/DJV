// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvUI/Enum.h>

#include <djvMath/BBox.h>

namespace djv
{
    namespace UI
    {
        //! Widget layout.
        namespace Layout
        {
            //! \name Utility
            ///@{

            //! Get the widget geometry.
            Math::BBox2f getAlign(
                const Math::BBox2f&,
                const glm::vec2& minimumSize,
                HAlign,
                VAlign);

            //! Get the popup geometry.
            Math::BBox2f getPopupGeometry(
                UI::Popup,
                const glm::vec2& pos,
                const glm::vec2& minimumSize);

            //! Get the popup geometry.
            Math::BBox2f getPopupGeometry(
                UI::Popup,
                const Math::BBox2f& button,
                const glm::vec2& minimumSize);

            //! Get the popup direction.
            UI::Popup getPopup(
                UI::Popup,
                const Math::BBox2f& area,
                const glm::vec2& pos,
                const glm::vec2& minimumSize);

            //! Get the popup direction.
            UI::Popup getPopup(
                UI::Popup,
                const Math::BBox2f& area,
                const Math::BBox2f& button,
                const glm::vec2& minimumSize);

            ///@}

        } // namespace Layout
    } // namespace UI
} // namespace djv
