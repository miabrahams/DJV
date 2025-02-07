// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2004-2020 Darby Johnston
// All rights reserved.

#pragma once

#include <djvAV/SequenceIO.h>

#include <djvMath/BBox.h>

#include <ImathBox.h>
#include <ImfChannelList.h>
#include <ImfHeader.h>
#include <ImfInputFile.h>
#include <ImfPixelType.h>

namespace djv
{
    namespace AV
    {
        //! OpenEXR image I/O.
        //!
        //! References:
        //! - http://www.openexr.com
        //!
        //! \todo Add support for writing luminance/chroma images.
        //! \todo Add better support for tiled images.
        namespace OpenEXR
        {
            static const std::string pluginName = "OpenEXR";
            static const std::set<std::string> fileExtensions = { ".exr" };

            //! OpenEXR channels grouping.
            enum class Channels
            {
                None,
                Known,
                All,

                Count,
                First = None
            };
            DJV_ENUM_HELPERS(Channels);

            //! OpenEXR image channel.
            struct Channel
            {
                Channel();
                Channel(
                    const std::string& name,
                    Image::DataType    type,
                    const glm::ivec2&  sampling = glm::ivec2(1, 1));

                std::string     name;
                Image::DataType type     = Image::DataType::None;
                glm::ivec2      sampling = glm::ivec2(1, 1);
            };

            //! OpenEXR image layer.
            struct Layer
            {
                Layer(
                    const std::vector<Channel>& channels        = std::vector<Channel>(),
                    bool                        luminanceChroma = false);

                std::string          name;
                std::vector<Channel> channels;
                bool                 luminanceChroma = false;
            };

            //! OpenEXR compression type.
            enum class Compression
            {
                None,
                RLE,
                ZIPS,
                ZIP,
                PIZ,
                PXR24,
                B44,
                B44A,
                DWAA,
                DWAB,

                Count,
                First = None
            };
            DJV_ENUM_HELPERS(Compression);

            //! Get a layer name from a list of channel names.
            std::string getLayerName(const std::vector<std::string>&);

            //! Get the channels that aren't in any layer.
            Imf::ChannelList getDefaultLayer(const Imf::ChannelList&);

            //! Find a channel by name.
            const Imf::Channel* find(const Imf::ChannelList&, std::string&);

            //! Get a list of layers from Imf channels.
            std::vector<Layer> getLayers(const Imf::ChannelList&, Channels);

            //! Read the tags from an Imf header.
            void readTags(const Imf::Header&, Image::Tags&, Math::IntRational&);

            //! Write tags to an Imf header.
            //!
            //! \todo Write all the tags that are handled by readTags().
            void writeTags(const Image::Tags&, const Math::IntRational& speed, Imf::Header&);

            //! Convert an Imath box type.
            Math::BBox2i fromImath(const Imath::Box2i&);

            //! Convert to an Imf pixel type.
            Imf::PixelType toImf(Image::DataType);

            //! Convert from an Imf pixel type.
            Image::DataType fromImf(Imf::PixelType);

            //! Convert from an Imf channel.
            Channel fromImf(const std::string& name, const Imf::Channel&);

            //! OpenEXR I/O optioms.
            struct Options
            {
                size_t      threadCount         = 4;
                Channels    channels            = Channels::Known;
                Compression compression         = Compression::None;
                float       dwaCompressionLevel = 45.F;
                    
                bool operator == (const Options&) const;
            };

            //! Memory-mapped input stream.
            class MemoryMappedIStream : public Imf::IStream
            {
                DJV_NON_COPYABLE(MemoryMappedIStream);

            public:
                MemoryMappedIStream(const char fileName[]);
                ~MemoryMappedIStream() override;

                bool isMemoryMapped() const override;
                char* readMemoryMapped(int n) override;
                bool read(char c[], int n) override;
                Imf::Int64 tellg() override;
                void seekg(Imf::Int64 pos) override;

            private:
                DJV_PRIVATE();
            };

            //! OpenEXR reader.
            class Read : public IO::ISequenceRead
            {
                DJV_NON_COPYABLE(Read);

            protected:
                Read();

            public:
                ~Read() override;

                static std::shared_ptr<Read> create(
                    const System::File::Info&,
                    const IO::ReadOptions&,
                    const Options&,
                    const std::shared_ptr<System::TextSystem>&,
                    const std::shared_ptr<System::ResourceSystem>&,
                    const std::shared_ptr<System::LogSystem>&);

            protected:
                IO::Info _readInfo(const std::string& fileName) override;
                std::shared_ptr<Image::Data> _readImage(const std::string& fileName) override;

            private:
                struct File;
                IO::Info _open(const std::string&, File&);

                DJV_PRIVATE();
            };
                
            //! OpenEXR writer.
            class Write : public IO::ISequenceWrite
            {
                DJV_NON_COPYABLE(Write);

            protected:
                Write();

            public:
                ~Write() override;

                static std::shared_ptr<Write> create(
                    const System::File::Info&,
                    const IO::Info&,
                    const IO::WriteOptions&,
                    const Options&,
                    const std::shared_ptr<System::TextSystem>&,
                    const std::shared_ptr<System::ResourceSystem>&,
                    const std::shared_ptr<System::LogSystem>&);

            protected:
                Image::Type _getImageType(Image::Type) const override;
                Image::Layout _getImageLayout() const override;
                void _write(const std::string& fileName, const std::shared_ptr<Image::Data>&) override;

            private:
                DJV_PRIVATE();
            };

            //! OpenEXR I/O plugin.
            class Plugin : public IO::ISequencePlugin
            {
                DJV_NON_COPYABLE(Plugin);

            protected:
                Plugin();

            public:
                static std::shared_ptr<Plugin> create(const std::shared_ptr<System::Context>&);

                rapidjson::Value getOptions(rapidjson::Document::AllocatorType&) const override;
                void setOptions(const rapidjson::Value&) override;

                std::shared_ptr<IO::IRead> read(const System::File::Info&, const IO::ReadOptions&) const override;
                std::shared_ptr<IO::IWrite> write(const System::File::Info&, const IO::Info&, const IO::WriteOptions&) const override;

            private:
                DJV_PRIVATE();
            };

        } // namespace OpenEXR
    } // namespace AV

    DJV_ENUM_SERIALIZE_HELPERS(AV::OpenEXR::Compression);
    DJV_ENUM_SERIALIZE_HELPERS(AV::OpenEXR::Channels);

    rapidjson::Value toJSON(const AV::OpenEXR::Options&, rapidjson::Document::AllocatorType&);

    //! Throws:
    //! - std::exception
    void fromJSON(const rapidjson::Value&, AV::OpenEXR::Options&);

} // namespace djv
