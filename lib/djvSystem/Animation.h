// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvSystem/ISystem.h>

#include <djvCore/Enum.h>
#include <djvCore/Time.h>

#include <functional>

namespace djv
{
    namespace System
    {
        //! Animation functionality.
        namespace Animation
        {
            class AnimationSystem;

            //! Animation types.
            enum class Type
            {
                Linear,
                EaseIn,
                EaseOut,
                SmoothStep,
                Sine,

                Count,
                First = Linear,
                Last = Sine
            };
            DJV_ENUM_HELPERS(Type);

            //! Animation function.
            typedef std::function<float(float)> Function;

            //! Get an animation function.
            Function getFunction(Type);

            //! Animated value.
            class Animation : public std::enable_shared_from_this<Animation>
            {
                DJV_NON_COPYABLE(Animation);
                void _init(const std::shared_ptr<Context>&);
                Animation();

            public:
                //! Create a new animation.
                static std::shared_ptr<Animation> create(const std::shared_ptr<Context>&);

                //! \name Information
                ///@{

                Type getType() const;
                
                void setType(Type);

                ///@}

                //! \name Options
                ///@{

                bool isRepeating() const;
                
                void setRepeating(bool);

                ///@}

                //! \name Active
                ///@{

                //! Get whether the animation is active.
                bool isActive() const;

                typedef std::function<void(float)> Callback;

                //! Start the animation.
                void start(
                    float                begin,
                    float                end,
                    Core::Time::Duration duration,
                    const Callback&      callback,
                    const Callback&      endCallback = nullptr);

                //! Stop the animation.
                void stop();

                ///@}

            private:
                void _tick();

                Type                  _type        = Type::Linear;
                Function              _function;
                bool                  _repeating   = false;
                bool                  _active      = false;
                float                 _begin       = 0.F;
                float                 _end         = 0.F;
                Core::Time::Duration  _duration    = Core::Time::Duration::zero();
                Callback              _callback;
                Callback              _endCallback;
                Core::Time::TimePoint _time;
                Core::Time::TimePoint _start;

                friend class AnimationSystem;
            };

            //! Animation system.
            class AnimationSystem : public ISystem
            {
                DJV_NON_COPYABLE(AnimationSystem);
                void _init(const std::shared_ptr<Context>&);
                AnimationSystem();

            public:
                ~AnimationSystem() override;

                static std::shared_ptr<AnimationSystem> create(const std::shared_ptr<Context>&);

                void tick() override;

            private:
                void _addAnimation(const std::weak_ptr<Animation>&);

                DJV_PRIVATE();

                friend class Animation;
            };

        } // namespace Animation
    } // namespace System

    DJV_ENUM_SERIALIZE_HELPERS(System::Animation::Type);
    DJV_ENUM_SERIALIZE_HELPERS(System::Animation::Type);

} // namespace djv

#include <djvSystem/AnimationInline.h>
