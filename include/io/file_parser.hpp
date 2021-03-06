/*
 * Copyright nPrint 2020
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef FILE_PARSER
#define FILE_PARSER

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "file_writer.hpp"
#include "superpacket.hpp"
#include "conf.hpp"

/* 
 * File parser abstract class, any input file type that is new must conform to this 
 * abstract class definition
*/

class FileParser
{
    public:
        virtual void process_file() = 0;
        virtual void format_and_write_header() = 0;
        void set_conf(Config c);
        void set_filewriter(FileWriter *fw);
        SuperPacket *process_packet(void *pkt);
        void tokenize_line(std::string line, std::vector<std::string> &to_fill, 
                           char delimiter=',');
    protected:
        Config config;
        FileWriter *fw;
        uint32_t packets_processed;
        void write_output(SuperPacket *sp);
        
        std::vector<std::string> custom_output;
        std::vector<int8_t> bitstring_vec;
        std::vector<std::string> fields_vec;
    private:
        void load_ip_map(std::string ip_file);
        std::map<std::string, std::uint32_t> m;
        std::string output_type;
        bool has_ip_map;
};

#endif
