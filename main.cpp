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

#include <iostream>
#include <fstream>
#include <array>
#include <stdio.h>
#include <inttypes.h>

#include "capstone/include/capstone.h"

#include "elf_object.h"

#define MAX_IDEAL_PAYLOAD_SIZE 10000

int main(int argc, char *argv[]) {

    std::fstream file;
    file.exceptions(std::fstream::badbit | std::fstream::failbit | std::fstream::eofbit);
    file.open(argv[1], std::fstream::in | std::fstream::binary);

    ElfObject elfObject;

    elfObject.Parse(&file);

//    uint8_t ideal_payload[MAX_IDEAL_PAYLOAD_SIZE];
//    size_t ideal_payload_size = ideal_program.Read(0 /* TODO: NOT hard code for COFF */, ideal_payload, MAX_IDEAL_PAYLOAD_SIZE);
//    csh handle;
//    cs_insn *insn;
//    size_t count;
//    if (cs_open(CS_ARCH_ARM, CS_MODE_ARM, &handle) != CS_ERR_OK)
//        return -1;
//
//    count = cs_disasm_ex(handle, ideal_payload, ideal_payload_size, 0x1000 /* TODO: stubbed */, 0, &insn);
//
//    if (count > 0) {
//        size_t j;
//
//        for (j = 0; j < count; j++) {
//            printf("0x%" PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
//        }
//
//        cs_free(insn, count);
//    } else {
//        printf("ERROR: Failed to disassemble given code!\n");
//    }
//
//    cs_close(&handle);
}
