/*
Open Asset Import Library (ASSIMP)
----------------------------------------------------------------------

Copyright (c) 2006-2008, ASSIMP Development Team
All rights reserved.

Redistribution and use of this software in source and binary forms, 
with or without modification, are permitted provided that the 
following conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the ASSIMP team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the ASSIMP Development Team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------
*/


/** @file Defines helper functions for text parsing  */
#ifndef AI_PARSING_UTILS_H_INC
#define AI_PARSING_UTILS_H_INC

// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool IsSpace( const char_t in)
{
	return (in == (char_t)' ' || in == (char_t)'\t');
}
// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool IsLineEnd( const char_t in)
{
	return (in == (char_t)'\r' || in == (char_t)'\n' || in == (char_t)'\0');
}
// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool IsSpaceOrNewLine( const char_t in)
{
	return IsSpace<char_t>(in) || IsLineEnd<char_t>(in);
}
// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool SkipSpaces( const char_t* in, const char_t** out)
{
	while (*in == (char_t)' ' || *in == (char_t)'\t')in++;
	*out = in;
	return !IsLineEnd<char_t>(*in);
}
// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool SkipSpaces( const char_t** inout)
{
	return SkipSpaces<char_t>(*inout,inout);
}
// ---------------------------------------------------------------------------------
template <class char_t>
inline bool SkipLine( const char_t* in, const char_t** out)
{
	while (*in != (char_t)'\r' && *in != (char_t)'\n' && *in != (char_t)'\0')in++;

	// files are opened in binary mode. Ergo there are both NL and CR
	while (*in == (char_t)'\r' || *in == (char_t)'\n')in++;
	*out = in;
	return *in != (char_t)'\0';
}
// ---------------------------------------------------------------------------------
template <class char_t>
inline bool SkipLine( const char_t** inout)
{
	return SkipLine<char_t>(*inout,inout);
}
// ---------------------------------------------------------------------------------
template <class char_t>
inline bool SkipSpacesAndLineEnd( const char_t* in, const char_t** out)
{
	while (*in == (char_t)' ' || *in == (char_t)'\t' ||
		*in == (char_t)'\r' || *in == (char_t)'\n')in++;
	*out = in;
	return *in != '\0';
}
// ---------------------------------------------------------------------------------
template <class char_t>
inline bool SkipSpacesAndLineEnd( const char_t** inout)
{
	return SkipSpacesAndLineEnd<char_t>(*inout,inout);
}
// ---------------------------------------------------------------------------------
template <class char_t>
inline bool GetNextLine(const char_t*& buffer, char_t out[4096])
{
	if ((char_t)'\0' == *buffer)return false;

	char* _out = out;
	char* const end = _out+4096;
	while (!IsLineEnd( *buffer ) && _out < end)
		*_out++ = *buffer++;
	*_out = (char_t)'\0';

	while (IsLineEnd( *buffer ) && '\0' != *buffer)++buffer;
	return true;
}
// ---------------------------------------------------------------------------------
template <class char_t>
AI_FORCE_INLINE bool IsNumeric( char_t in)
{
	return in >= '0' && in <= '9' || '-' == in || '+' == in;
}
// ---------------------------------------------------------------------------------
AI_FORCE_INLINE bool TokenMatch(const char*& in, const char* token, unsigned int len)
{
	if (!::strncmp(token,in,len) && IsSpaceOrNewLine(in[len]))
	{
		in += len+1;
		return true;
	}
	return false;
}
// ---------------------------------------------------------------------------------
AI_FORCE_INLINE bool TokenMatch(char*& in, const char* token, unsigned int len)
{
	if (!::strncmp(token,in,len) && IsSpaceOrNewLine(in[len]))
	{
		in += len+1;
		return true;
	}
	return false;
}
// ---------------------------------------------------------------------------------
AI_FORCE_INLINE void SkipToken(const char*& in)
{
	SkipSpaces(&in);
	while (!IsSpaceOrNewLine(*in))++in;
}
#endif // ! AI_PARSING_UTILS_H_INC
