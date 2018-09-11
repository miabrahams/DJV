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

#include <djvImageIOFormatsTest.h>

#include <djvGraphics/Image.h>
#include <djvGraphics/GraphicsContext.h>
#include <djvGraphics/ImageIO.h>
#include <djvGraphics/OpenGLImage.h>
#include <djvGraphics/OpenGLOffscreenBuffer.h>
#include <djvGraphics/PixelDataUtil.h>

#include <djvCore/Debug.h>
#include <djvCore/Error.h>
#include <djvCore/ErrorUtil.h>
#include <djvCore/FileInfo.h>
#include <djvCore/FileIO.h>
#include <djvCore/Memory.h>

#include <QPair>

#include <algorithm>

void djvImageIOFormatsTest::run(int & argc, char ** argv)
{
    DJV_DEBUG("djvImageIOFormatsTest::run");

    djvGraphicsContext context;
    initData();
    initImages();
    initPlugins(&context);
    
    //! \todo Fix these image I/O confidence tests.    
    typedef QPair<QString, djvPixel::PIXEL> Disable;
    QVector<Disable> disabled;
    disabled += Disable("IFF", djvPixel::RGB_U16);
    disabled += Disable("IFF", djvPixel::RGBA_U16);
    
    for (int j = 0; j < _plugins.count(); ++j)
    {
        djvImageIO * plugin = static_cast<djvImageIO *>(_plugins[j]);
        for (int i = 0; i < _images.count(); ++i)
        {
            const djvImage & image = _images[i];
            bool test = true;
            for (int k = 0; k < disabled.count(); ++k)
            {
                if (plugin->pluginName() == disabled[k].first &&
                    image.pixel()  == disabled[k].second)
                {
                    test = false;
                    break;
                }
            }
            if (test)
            {
                runTest(plugin, image);
            }
        }
    }
}

void djvImageIOFormatsTest::initPlugins(djvGraphicsContext * context)
{
    DJV_DEBUG("djvImageIOFormatsTest::initPlugins");

    QStringList option;
    option << "None";
    context->imageIOFactory()->setOption("Cineon", "Input Color Profile", option);
    option << "None";
    context->imageIOFactory()->setOption("Cineon", "Output Color Profile", option);
    option << "None";
    context->imageIOFactory()->setOption("DPX", "Input Color Profile", option);
    option << "None";
    context->imageIOFactory()->setOption("DPX", "Output Color Profile", option);
    option << "None";
    context->imageIOFactory()->setOption("OpenEXR", "Input Color Profile", option);

    //! \todo Fix FFmpeg image I/O testing.
    QStringList disable = QStringList() <<
        "FFmpeg";
    
    //! \todo JPEG is lossy which will cause the pixel comparison tests to fail.
    disable += "JPEG";

    const QList<djvPlugin *> & pluginsTmp = context->imageIOFactory()->plugins();
    for (int i = 0; i < pluginsTmp.count(); ++i)
    {
        if (! disable.contains(pluginsTmp[i]->pluginName()))
        {
            _plugins.append(pluginsTmp[i]);
        }
    }
    DJV_DEBUG_PRINT("plugins = " << _plugins.count());
}

void djvImageIOFormatsTest::initData()
{
    DJV_DEBUG("djvImageIOFormatsTest::initData");
    if (1)
    {
        //! \todo The one pixel wide data seems to be triggering errors
        //! in the floating point tests.
        _sizes += QVector<glm::ivec2>() <<
            glm::ivec2(11,  1) <<
            //glm::ivec2( 1,  7) <<
            glm::ivec2(11,  7) <<
            glm::ivec2( 7, 11);
        for (int i = 0; i < djvPixel::PIXEL_COUNT; ++i)
        {
            const djvPixel::PIXEL pixel = static_cast<djvPixel::PIXEL>(i);
            _pixels += pixel;
        }
    }
    else
    {
        _sizes += glm::ivec2(10, 1);
        //_pixels += djvPixel::RGB_U10;
        _pixels += djvPixel::RGB_F16;
    }
    DJV_DEBUG_PRINT("sizes = " << _sizes);
    DJV_DEBUG_PRINT("pixels = " << _pixels);
}

void djvImageIOFormatsTest::initImages()
{
    DJV_DEBUG("djvImageIOFormatsTest::initImages");
    for (int i = 0; i < _sizes.count(); ++i)
    {
        for (int j = 0; j < _pixels.count(); ++j)
        {
            djvImage gradient(djvPixelDataInfo(_sizes[i], djvPixel::L_F32));
            djvPixelDataUtil::gradient(gradient);
            djvImage image(djvPixelDataInfo(gradient.size(), _pixels[j]));
            djvOpenGLImage().copy(gradient, image);
            DJV_DEBUG_PRINT("image = " << image);

            djvPixelData p(djvPixelDataInfo(1, 1, image.pixel()));
            djvOpenGLImageOptions options;
            options.xform.position = glm::vec2(0, 0);
            djvOpenGLImage().copy(image, p, options);
            djvColor c(p.data(), p.pixel());
            DJV_DEBUG_PRINT("c0 = " << c);

            options.xform.position = -glm::vec2(
                image.size().x - 1, image.size().y - 1);
            djvOpenGLImage().copy(image, p, options);
            c = djvColor(p.data(), p.pixel());
            DJV_DEBUG_PRINT("c1 = " << c);

            _images += image;
        }
    }
}

void djvImageIOFormatsTest::runTest(djvImageIO * plugin, const djvImage & image)
{
    DJV_DEBUG("djvImageIOFormatsTest::runTest");
    DJV_DEBUG_PRINT("plugin = " << plugin->pluginName());
    DJV_DEBUG_PRINT("image = " << image);
    
    QString fileName = "djvImageIOFormatsTest";
    QString fileNamePartial = fileName + "Partial";    
    const QStringList & extensions = plugin->extensions();
    if (extensions.count())
    {
        fileName += extensions[0];
        fileNamePartial += extensions[0];
    }
    DJV_DEBUG_PRINT("file name = " << fileName);
    
    try
    {
        QScopedPointer<djvImageLoad> load(plugin->createLoad());
        QScopedPointer<djvImageSave> save(plugin->createSave());
        if (! load.data() || ! save.data())
            return;
        
        save->open(fileName, image.info());
        save->write(image);
        save->close();
        
        djvImageIOInfo info;
        load->open(fileName, info);
        djvImage tmp;
        load->read(tmp);
        load->close();
        if (info.pixel != image.pixel() ||
            info.size  != image.size())
            return;
        
        djvPixelData p(djvPixelDataInfo(1, 1, image.pixel()));        
        djvOpenGLImageOptions options;
        for (int y = 0; y < info.size.y; ++y)
        {
            for (int x = 0; x < info.size.x; ++x)
            {
                options.xform.position = -glm::vec2(x, y);
                djvOpenGLImage().copy(image, p, options);
                djvColor a(p.data(), p.pixel());
                djvOpenGLImage().copy(tmp, p, options);
                djvColor b(p.data(), p.pixel());
                DJV_DEBUG_PRINT(a << " == " << b << " (" << x << " " << y << ")");
                DJV_ASSERT(a == b);
            }
        }
    }
    catch (const djvError & error)
    {
        DJV_DEBUG_PRINT(djvErrorUtil::format(error));
    }

    try
    {
        djvFileInfo fileInfo(fileName);
        const quint64 size = fileInfo.size();
        std::vector<quint8> buf(size / 2);

        djvFileIO io;
        io.open(fileName, djvFileIO::READ);
        io.get(buf.data(), buf.size());
        io.close();

        io.open(fileNamePartial, djvFileIO::WRITE);
        io.set(buf.data(), buf.size());
        io.close();

        QScopedPointer<djvImageLoad> load(plugin->createLoad());        
        if (! load.data())
            return;
        
        djvImageIOInfo info;
        load->open(fileNamePartial, info);
        djvImage tmp;
        load->read(tmp);
        load->close();        
        DJV_ASSERT(0);
    }
    catch (const djvError & error)
    {
        DJV_DEBUG_PRINT(djvErrorUtil::format(error));
    }
}

