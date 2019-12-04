//------------------------------------------------------------------------------
// Copyright (c) 2019 Darby Johnston
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions, and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions, and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
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

namespace djv
{
    namespace Scene
    {
        inline IPrimitive::IPrimitive()
        {}

        inline IPrimitive::~IPrimitive()
        {}

        inline const std::string& IPrimitive::getName() const
        {
            return _name;
        }

        inline void IPrimitive::setName(const std::string& value)
        {
            _name = value;
        }

        inline bool IPrimitive::isVisible() const
        {
            return _visible;
        }

        inline void IPrimitive::setVisible(bool value)
        {
            _visible = value;
        }

        inline const glm::mat4x4& IPrimitive::getXForm() const
        {
            return _xform;
        }

        inline const glm::mat4x4& IPrimitive::getXFormFinal() const
        {
            return _xformFinal;
        }

        inline void IPrimitive::setXForm(const glm::mat4x4& value)
        {
            _xform = value;
        }

        inline void IPrimitive::setXFormFinal(const glm::mat4x4& value)
        {
            _xformFinal = value;
        }

        inline const std::shared_ptr<AV::Geom::TriangleMesh>& IPrimitive::getMesh() const
        {
            return _mesh;
        }

        inline void  IPrimitive::setMesh(const std::shared_ptr<AV::Geom::TriangleMesh>& value)
        {
            _mesh = value;
        }

        inline MaterialAssignment IPrimitive::getMaterialAssignment() const
        {
            return _materialAssignment;
        }

        inline void IPrimitive::setMaterialAssignment(MaterialAssignment value)
        {
            _materialAssignment = value;
        }

        inline const std::shared_ptr<IMaterial>& IPrimitive::getMaterial() const
        {
            return _material;
        }

        inline void IPrimitive::setMaterial(const std::shared_ptr<IMaterial>& value)
        {
            _material = value;
        }

        inline const std::weak_ptr<IPrimitive>& IPrimitive::getParent() const
        {
            return _parent;
        }

        inline const std::vector<std::shared_ptr<IPrimitive> >& IPrimitive::getChildren() const
        {
            return _children;
        }

        inline const std::vector<std::shared_ptr<IPrimitive> >& IPrimitive::getPrimitives() const
        {
            return _children;
        }

        inline NullPrimitive::NullPrimitive()
        {}

        inline InstancePrimitive::InstancePrimitive()
        {}

        inline const std::vector<std::shared_ptr<IPrimitive> >& InstancePrimitive::getInstances() const
        {
            return _instances;
        }

        inline void InstancePrimitive::setInstances(const std::vector<std::shared_ptr<IPrimitive> >& value)
        {
            _instances = value;
        }

        inline void InstancePrimitive::addInstance(const std::shared_ptr<IPrimitive>& value)
        {
            _instances.push_back(value);
        }

        inline const std::vector<std::shared_ptr<IPrimitive> >& InstancePrimitive::getPrimitives() const
        {
            return _instances;
        }

        inline MeshPrimitive::MeshPrimitive()
        {}

    } // namespace Scene
} // namespace djv

