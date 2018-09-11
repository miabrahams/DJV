//------------------------------------------------------------------------------
// Copyright (c) 2004-2015 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
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

#include <djvUI/AbstractPrefsWidget.h>

#include <djvCore/Plugin.h>
#include <djvCore/System.h>

#include <QWidget>

class djvUIContext;

class djvImageIO;

//! \addtogroup djvUIWidget
//@{

//------------------------------------------------------------------------------
//! \class djvImageIOWidget
//!
//! This class provides the base functionality for image I/O widgets.
//------------------------------------------------------------------------------

class djvImageIOWidget : public djvAbstractPrefsWidget
{
    Q_OBJECT
    
public:
    explicit djvImageIOWidget(
        djvImageIO *    plugin,
        djvUIContext * context,
        QWidget *       parent  = nullptr);

    virtual ~djvImageIOWidget() = 0;

    //! Get the plugin.
    djvImageIO * plugin() const;

    //! Get the context.
    djvUIContext * context() const;
    
private:
    djvImageIO *    _plugin  = nullptr;
    djvUIContext * _context = nullptr;
};

//------------------------------------------------------------------------------
//! \class djvImageIOWidgetPlugin
//!
//! This class provides an image I/O widget plugin.
//------------------------------------------------------------------------------

class djvImageIOWidgetPlugin : public djvPlugin
{
public:
    djvImageIOWidgetPlugin(djvCoreContext *);

    virtual ~djvImageIOWidgetPlugin() = 0;

    //! Create a widget.    
    virtual djvImageIOWidget * createWidget(djvImageIO * plugin) const = 0;
    
    //! Get the context.
    djvUIContext * uiContext() const;

    virtual djvPlugin * copyPlugin() const;
};

//------------------------------------------------------------------------------
//! \class djvImageIOWidgetFactory
//!
//! This class provides a factory for image I/O widget plugins.
//------------------------------------------------------------------------------

class djvImageIOWidgetFactory : public djvPluginFactory
{
    Q_OBJECT
    
public:
    explicit djvImageIOWidgetFactory(
        djvUIContext *     context,
        const QStringList & searchPath = djvSystem::searchPath(),
        QObject *           parent     = nullptr);

    virtual ~djvImageIOWidgetFactory();

    //! Create a widget.    
    djvImageIOWidget * createWidget(djvImageIO *) const;
    
private:
    DJV_PRIVATE_COPY(djvImageIOWidgetFactory);
    
    djvUIContext * _context = nullptr;
};

//@} // djvUIWidget
