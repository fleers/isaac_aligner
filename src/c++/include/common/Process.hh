/**
 ** Isaac Genome Alignment Software
 ** Copyright (c) 2010-2014 Illumina, Inc.
 ** All rights reserved.
 **
 ** This software is provided under the terms and conditions of the
 ** BSD 2-Clause License
 **
 ** You should have received a copy of the BSD 2-Clause License
 ** along with this program. If not, see
 ** <https://github.com/sequencing/licenses/>.
 **
 ** \file Process.hh
 **
 ** process management helper utilities.
 **
 ** \author Roman Petrovski
 **/

#ifndef iSAAC_COMMON_PROCESS_HPP
#define iSAAC_COMMON_PROCESS_HPP

#include "common/Debug.hh"

namespace isaac
{
namespace common
{

void executeCommand(const std::string &cmd);

} //namespace common
} //namespace isaac

#endif // #ifndef iSAAC_COMMON_PROCESS_HPP
