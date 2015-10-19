// @HEADER
// ************************************************************************
//
//               Digital Image Correlation Engine (DICe)
//                 Copyright 2015 Sandia Corporation.
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact: Dan Turner (dzturne@sandia.gov)
//
// ************************************************************************
// @HEADER

#include <cassert>

#include <DICe_Tiff.h>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/tiff_dynamic_io.hpp>


namespace DICe{
namespace utils{

DICE_LIB_DLL_EXPORT
void read_tiff_image_dimensions(const char * file_name,
  int_t & width,
  int_t & height){
  TIFFSetWarningHandler(NULL);
  boost::gil::point2<std::ptrdiff_t> pt = boost::gil::tiff_read_dimensions(file_name);
  width = pt.x;
  height = pt.y;
}

DICE_LIB_DLL_EXPORT
void read_tiff_image(const char * file_name,
  intensity_t * intensities,
  const bool is_layout_right){
  assert(file_name!="");
  TIFFSetWarningHandler(NULL);
  boost::gil::gray8_image_t img;
  boost::gil::tiff_read_and_convert_image(file_name,img);
  const int_t width = img.width();
  const int_t height = img.height();
  boost::gil::gray8c_view_t img_view = boost::gil::const_view(img);
  for (int_t y=0; y<height; ++y) {
    boost::gil::gray8c_view_t::x_iterator src_it = img_view.row_begin(y);
    if(is_layout_right)
      for (int_t x=0; x<width;++x){
        intensities[y*width+x] = src_it[x];
      }
    else // otherwise assume LayoutLeft
      for (int_t x=0; x<width;++x){
        intensities[x*height+y] = src_it[x];
      }
  }
}

DICE_LIB_DLL_EXPORT
void read_tiff_image(const char * file_name,
  int_t offset_x,
  int_t offset_y,
  int_t width,
  int_t height,
  intensity_t * intensities,
  const bool is_layout_right){
  assert(file_name!="");
  TIFFSetWarningHandler(NULL);
  boost::gil::gray8_image_t img;
  boost::gil::tiff_read_and_convert_image(file_name,img);
  const int_t img_width = img.width();
  const int_t img_height = img.height();
  assert(width+offset_x < img_width);
  assert(height+offset_y< img_height);

  boost::gil::gray8c_view_t img_view = boost::gil::const_view(img);
  for (int_t y=offset_y; y<offset_y+height; ++y) {
    boost::gil::gray8c_view_t::x_iterator src_it = img_view.row_begin(y);
    if(is_layout_right)
      for (int_t x=offset_x; x<offset_x+width;++x){
        intensities[(y-offset_y)*width + x-offset_x] = src_it[x];
      }
    else // otherwise assume layout left
      for (int_t x=offset_x; x<offset_x+width;++x){
        intensities[(x-offset_x)*height+y-offset_y] = src_it[x];
      }
  }
}

DICE_LIB_DLL_EXPORT
void write_tiff_image(const char * file_name,
  const int_t width,
  const int_t height,
  intensity_t * intensities,
  const bool is_layout_right){
  assert(file_name!="");

  // rip through the intensity values and determine if they need to be scaled to 8-bit range (0-255):
  // negative values are shifted to start at zero so all values will be positive
  intensity_t max_intensity = -1.0E10;
  intensity_t min_intensity = 1.0E10;
  for(size_t i=0; i<width*height; ++i){
    if(intensities[i] > max_intensity) max_intensity = intensities[i];
    if(intensities[i] < min_intensity) min_intensity = intensities[i];
  }
  intensity_t fac = 1.0;
  if((max_intensity - min_intensity) != 0.0)
    fac = 255.0 / (max_intensity - min_intensity);

  boost::gil::gray8_image_t img(width,height);
  boost::gil::gray8_view_t img_view = boost::gil::view(img);
  for (int_t y=0; y<height; ++y) {
    boost::gil::gray8_view_t::x_iterator src_it = img_view.row_begin(y);
    if(is_layout_right)
      for (int_t x=0; x<width;++x){
        src_it[x] = (boost::gil::gray8_pixel_t)(std::floor((intensities[y*width + x]-min_intensity)*fac));
      }
    else
      for (int_t x=0; x<width;++x){
        src_it[x] = (boost::gil::gray8_pixel_t)(std::floor((intensities[x*height+y]-min_intensity)*fac));
      }
  }
  boost::gil::tiff_write_view(file_name, img_view);
}

} // end namespace utils
} // end namespace DICe
