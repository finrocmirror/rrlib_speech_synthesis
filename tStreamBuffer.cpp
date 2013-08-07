//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/speech_synthesis/tStreamBuffer.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-08-07
 *
 */
//----------------------------------------------------------------------
#include "rrlib/speech_synthesis/tStreamBuffer.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <iostream>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace speech_synthesis
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// tStreamBuffer constructors
//----------------------------------------------------------------------
tStreamBuffer::tStreamBuffer(speech_synthesis::tVoice &voice, std::size_t buffer_size) :
  voice(voice),
  buffer(buffer_size + 1)
{
  this->setp(this->buffer.data(), this->buffer.data() + buffer_size);
}

//----------------------------------------------------------------------
// tStreamBuffer destructor
//----------------------------------------------------------------------
tStreamBuffer::~tStreamBuffer()
{
  this->sync();
}

//----------------------------------------------------------------------
// tStreamBuffer ProcessBuffer
//----------------------------------------------------------------------
void tStreamBuffer::ProcessBuffer()
{
  std::ptrdiff_t n = this->pptr() - this->pbase();
  this->pbump(-n);

  this->voice.Say(std::string(this->pbase(), n));
}

//----------------------------------------------------------------------
// tStreamBuffer overflow
//----------------------------------------------------------------------
tStreamBuffer::int_type tStreamBuffer::overflow(int_type c)
{
  if (c != traits_type::eof())
  {
    assert(this->pptr() <= this->epptr());
    *this->pptr() = c;
    this->pbump(1);
    this->ProcessBuffer();
  }

  return c;
}

//----------------------------------------------------------------------
// tStreamBuffer sync
//----------------------------------------------------------------------
int tStreamBuffer::sync()
{
  this->ProcessBuffer();
  return 0;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
