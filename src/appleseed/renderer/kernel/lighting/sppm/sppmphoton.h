
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_RENDERER_KERNEL_LIGHTING_SPPM_SPPMPHOTON_H
#define APPLESEED_RENDERER_KERNEL_LIGHTING_SPPM_SPPMPHOTON_H

// appleseed.renderer headers.
#include "renderer/global/globaltypes.h"

// appleseed.foundation headers.
#include "foundation/math/vector.h"

// Standard headers.
#include <cstddef>
#include <vector>

namespace renderer
{

//
// A photon in the SPPM photon map.
//

class SPPMPhotonData
{
  public:
    foundation::Vector3f    m_incoming;             // incoming direction, world space, unit length
    foundation::Vector3f    m_geometric_normal;     // geometric normal at the photon location, world space, unit length
    Spectrum                m_flux;                 // flux carried by this photon (in W)
};

class SPPMPhoton
{
  public:
    foundation::Vector3f    m_position;
    SPPMPhotonData          m_data;
};


//
// A vector of photons.
//

class SPPMPhotonVector
{
  public:
    std::vector<foundation::Vector3f>   m_positions;
    std::vector<SPPMPhotonData>         m_data;

    bool empty() const;
    size_t size() const;

    // Return the size (in bytes) of this object in memory.
    size_t get_memory_size() const;

    void swap(SPPMPhotonVector& rhs);
    void reserve(const size_t capacity);
    void push_back(const SPPMPhoton& photon);
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_LIGHTING_SPPM_SPPMPHOTON_H