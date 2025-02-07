// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#include <djvSystemTest/FileIOTest.h>

#include <djvSystem/FileIO.h>
#include <djvSystem/Path.h>

#include <limits>
#include <sstream>

using namespace djv::Core;
using namespace djv::System;

namespace djv
{
    namespace SystemTest
    {
        FileIOTest::FileIOTest(
            const File::Path& tempPath,
            const std::shared_ptr<Context>& context) :
            ITest(
                "djv::SystemTest::FileIOTest",
                File::Path(tempPath, "FileIOTest"),
                context),
            _fileName("file.txt"),
            _text("Hello"),
            _text2("world!")
        {}
        
        void FileIOTest::run()
        {
            _io();
            _error();
            _endian();
            _temp();
        }

        void FileIOTest::_io()
        {
            {
                auto io = File::IO::create();
                DJV_ASSERT(!io->isOpen());
                DJV_ASSERT(io->getFileName().empty());
                DJV_ASSERT(0 == io->getSize());
                DJV_ASSERT(0 == io->getPos());
                DJV_ASSERT(io->isEOF());
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                io->open(
                    fileName,
                    File::Mode::Write);
                DJV_ASSERT(io->isOpen());
                DJV_ASSERT(io->getFileName() == fileName);
            }

            {
                const int8_t   i8  = std::numeric_limits<int8_t>::max();
                const uint8_t  u8  = std::numeric_limits<uint8_t>::max();
                const int16_t  i16 = std::numeric_limits<int16_t>::max();
                const uint16_t u16 = std::numeric_limits<uint16_t>::max();
                const int32_t  i32 = std::numeric_limits<int32_t>::max();
                const uint32_t u32 = std::numeric_limits<uint32_t>::max();
                const float    f   = std::numeric_limits<float>::max();
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                auto io = File::IO::create();
                io->open(
                    fileName,
                    File::Mode::Write);
                io->write8(i8);
                io->writeU8(u8);
                io->write16(i16);
                io->writeU16(u16);
                io->write32(i32);
                io->writeU32(u32);
                io->writeF32(f);

                io->open(
                    fileName,
                    File::Mode::Read);
                int8_t   _i8  = 0;
                uint8_t  _u8  = 0;
                int16_t  _i16 = 0;
                uint16_t _u16 = 0;
                int32_t  _i32 = 0;
                uint32_t _u32 = 0;
                float    _f   = 0.F;
                io->read8(&_i8);
                io->readU8(&_u8);
                io->read16(&_i16);
                io->readU16(&_u16);
                io->read32(&_i32);
                io->readU32(&_u32);
                io->readF32(&_f);
                DJV_ASSERT(i8  == _i8);
                DJV_ASSERT(u8  == _u8);
                DJV_ASSERT(i16 == _i16);
                DJV_ASSERT(u16 == _u16);
                DJV_ASSERT(i32 == _i32);
                DJV_ASSERT(u32 == _u32);
                DJV_ASSERT(f   == _f);
            }

            {
                auto io = File::IO::create();
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                io->open(
                    fileName,
                    File::Mode::Write);
                io->write(_text + " ");
                io->open(
                    fileName,
                    File::Mode::Append);
                io->write(_text2);

                io->open(
                    fileName,
                    File::Mode::Read);
                std::string buf = File::readContents(io);
                _print(buf);
                DJV_ASSERT((_text + " " + _text2) == buf);
                io->setPos(0);
                DJV_ASSERT(0 == io->getPos());
            }

            {
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                File::writeLines(
                    fileName,
                    {
                        "# This is a comment",
                        _text + " " + _text2
                    });

                auto io = File::IO::create();
                io->open(
                    fileName,
                    File::Mode::ReadWrite);
                char buf[String::cStringLength];
                File::readWord(io, buf);
                _print(buf);
                DJV_ASSERT(_text == buf);
                File::readWord(io, buf);
                _print(buf);
                DJV_ASSERT(_text2 == buf);
            }

            {
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                auto io = File::IO::create();
                io->open(
                    fileName,
                    File::Mode::Write);
                io->write(_text + "\n" + _text2);

                io->open(
                    fileName,
                    File::Mode::Read);
                char buf[String::cStringLength];
                File::readLine(io, buf);
                _print(buf);
                DJV_ASSERT(_text == buf);
                File::readLine(io, buf);
                _print(buf);
                DJV_ASSERT(_text2 == buf);
            }

            {
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                File::writeLines(
                    fileName,
                    {
                        _text,
                        "# This is a comment",
                        _text2
                    });

                const auto lines = File::readLines(fileName);
                for (const auto& i : lines)
                {
                    _print(i);
                }
                DJV_ASSERT(_text == lines[0]);
                DJV_ASSERT(_text2 == lines[2]);
            }
        }
        
        void FileIOTest::_error()
        {
            try
            {
                auto io = File::IO::create();
                io->open(std::string(), File::Mode::Read);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
            
            try
            {
                auto io = File::IO::create();
                io->open(std::string(), File::Mode::Write);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
            
            try
            {
                auto io = File::IO::create();
                io->open(std::string(), File::Mode::ReadWrite);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
            
            try
            {
                auto io = File::IO::create();
                io->open(std::string(), File::Mode::Append);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }

            try
            {
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                auto io = File::IO::create();
                io->open(fileName, File::Mode::Write);
                io->open(fileName, File::Mode::Read);
                uint8_t buf[16];
                io->read(buf, 16, 1);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
            
            try
            {
                const std::string fileName = File::Path(getTempPath(), _fileName).get();
                auto io = File::IO::create();
                io->open(fileName, File::Mode::Write);
                io->open(fileName, File::Mode::ReadWrite);
                uint8_t buf[16];
                io->read(buf, 16, 1);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
            
            try
            {
                auto io = File::IO::create();
                uint8_t buf[16];
                io->write(buf, 16, 1);
                DJV_ASSERT(false);
            }
            catch (const std::exception& e)
            {
                _print(e.what());
            }
        }

        void FileIOTest::_endian()
        {
            uint32_t a = 0;
            uint32_t b = 0;
            uint8_t* aP = reinterpret_cast<uint8_t*>(&a);
            uint8_t* bP = reinterpret_cast<uint8_t*>(&b);
            aP[0] = bP[3] = 1;
            aP[1] = bP[2] = 2;
            aP[2] = bP[1] = 3;
            aP[3] = bP[0] = 4;
            
            auto io = File::IO::create();
            DJV_ASSERT(!io->hasEndianConversion());
            const std::string fileName = File::Path(getTempPath(), _fileName).get();
            io->open(
                fileName,
                File::Mode::Write);
            io->writeU32(a);
            io->setEndianConversion(true);
            DJV_ASSERT(io->hasEndianConversion());
            io->writeU32(a);

            io->open(
                fileName,
                File::Mode::Read);
            io->setEndianConversion(false);
            uint32_t _a = 0;
            uint32_t _b = 0;
            io->readU32(&_a);
            DJV_ASSERT(a == _a);
            io->setEndianConversion(true);
            io->readU32(&_b);
            DJV_ASSERT(a == _b);

            io->open(
                fileName,
                File::Mode::ReadWrite);
            io->setEndianConversion(false);
            _a = 0;
            _b = 0;
            io->readU32(&_a);
            DJV_ASSERT(a == _a);
            io->setEndianConversion(true);
            io->readU32(&_b);
            DJV_ASSERT(a == _b);
        }

        void FileIOTest::_temp()
        {
            auto io = File::IO::create();
            io->openTemp();
            for (auto i : _text)
            {
                io->writeU8(i);
            }
        }
        
    } // namespace SystemTest
} // namespace djv

