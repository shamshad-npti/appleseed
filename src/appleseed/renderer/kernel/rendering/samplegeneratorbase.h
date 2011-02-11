
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2011 Francois Beaune
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

#ifndef APPLESEED_RENDERER_KERNEL_RENDERING_SAMPLEGENERATORBASE_H
#define APPLESEED_RENDERER_KERNEL_RENDERING_SAMPLEGENERATORBASE_H

// appleseed.renderer headers.
#include "renderer/kernel/rendering/isamplegenerator.h"
#include "renderer/kernel/rendering/sample.h"

// Standard headers.
#include <cstddef>
#include <vector>

// Forward declarations.
namespace foundation    { class AbortSwitch; }
namespace renderer      { class AccumulationFramebuffer; }

namespace renderer
{

//
// A convenient base class for sample generators.
//

class SampleGeneratorBase
  : public ISampleGenerator
{
  public:
    SampleGeneratorBase(
        const size_t                generator_index,
        const size_t                generator_count);

    // Reset the sample generator to its initial state.
    virtual void reset();

    // Generate a given number of samples and store them into a progressive framebuffer.
    virtual void generate_samples(
        const size_t                sample_count,
        AccumulationFramebuffer&    framebuffer,
        foundation::AbortSwitch&    abort_switch);

  protected:
    typedef std::vector<Sample> SampleVector;

    // Generate one or multiple samples for a given sequence index and store them in @samples.
    // Return the number of samples that were stored.
    virtual size_t generate_samples(
        const size_t                sequence_index,
        SampleVector&               samples) = 0;

  private:
    const size_t                    m_generator_index;
    const size_t                    m_stride;
    size_t                          m_sequence_index;
    size_t                          m_current_batch_size;
    SampleVector                    m_samples;
};

}       // namespace renderer

#endif  // !APPLESEED_RENDERER_KERNEL_RENDERING_SAMPLEGENERATORBASE_H
