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
#include <inttypes.h>
#include <fstream>
#include <array>

#include "elf_object.h"

void ElfObject::ParseSectionNames(std::fstream* file) {

    file->seekg(0);

    uint32_t string_table_offset = m_section_headers[m_elf_header.section_header_string_index].offset;

    for (auto section : m_section_headers) {
        file->seekg(string_table_offset + section.name);

        // TODO: -- refactor
        static char temp[1000];
        std::string newstring = "";

        file->read(temp, 1000);
        newstring.insert(0, temp);
        // --

        m_secion_names[section.name] = newstring;
    }
}

void ElfObject::ParseSectionHeaders(std::fstream* file) {

    file->seekg(0);
    file->seekg(m_elf_header.section_header_offset);

    // resize to fit all section headers
    m_section_headers.resize(m_elf_header.section_header_entry_count);

    // read headers
    size_t header_size = m_elf_header.section_header_entry_count * sizeof(SectionHeader);
    file->read((char*)m_section_headers.data(), header_size);

}

void ElfObject::Parse(std::fstream* file) {

    file->seekg(0);
    file->read((char*)&m_elf_header, sizeof(ELFHeader));

    ParseSectionHeaders(file);
    ParseSectionNames(file);

    // Dump strings table
    for (auto entry : m_secion_names) {
        printf("Key: %d     Value: %s\n", entry.first, entry.second.c_str());
    }
}
