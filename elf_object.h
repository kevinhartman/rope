// Copyright 2014 Kevin Hartman
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the owner nor the names of its contributors may
//       be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __rope__elf_object__
#define __rope__elf_object__

#include <stdio.h>
#include <inttypes.h>
#include <fstream>
#include <array>
#include <vector>
#include <map>
#include <string>

struct ELFHeader {
    struct : std::array<uint8_t, 16> {
        uint8_t* magic_number() { return &(*this)[0]; }
        uint8_t elf_class() { return (*this)[4]; }
        uint8_t encoding() { return (*this)[5]; }
        uint8_t version() { return (*this)[6]; }
    } identity;

    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint32_t entry_address;
    uint32_t program_header_offset;
    uint32_t section_header_offset;
    uint32_t flags;
    uint16_t elf_header_size;
    uint16_t program_header_entry_size;
    uint16_t program_header_entry_count;
    uint16_t section_header_entry_size;
    uint16_t section_header_entry_count;
    uint16_t section_header_string_index;

};

struct SectionHeader {
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t address;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t address_align;
    uint32_t entry_size;
};

static_assert(sizeof(ELFHeader) == 52, "ELF Header is not correct size.");

class ElfObject {

public:
    ElfObject() = default;

    void Parse(std::fstream* file);

private:
    void ParseSectionHeaders(std::fstream* file);
    void ParseSectionNames(std::fstream* file);

private:
    ELFHeader m_elf_header;

    std::vector<SectionHeader> m_section_headers;
    std::map<uint32_t, std::string> m_secion_names;
};

#endif /* defined(__rope__elf_object__) */
