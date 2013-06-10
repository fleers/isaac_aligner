/**
 ** Isaac Genome Alignment Software
 ** Copyright (c) 2010-2012 Illumina, Inc.
 **
 ** This software is provided under the terms and conditions of the
 ** Illumina Open Source Software License 1.
 **
 ** You should have received a copy of the Illumina Open Source
 ** Software License 1 along with this program. If not, see
 ** <https://github.com/downloads/sequencing/licenses/>.
 **
 ** The distribution includes the code libraries listed below in the
 ** 'redist' sub-directory. These are distributed according to the
 ** licensing terms governing each library.
 **
 ** \file Nucleotides.cpp
 **
 ** \brief See Nucleotides.hh
 **
 ** \author Come Raczy
 **/

#include "oligo/Nucleotides.hh"

namespace isaac
{
namespace oligo
{

const std::vector<unsigned int> defaultTranslator = getTranslator();

} // namespace oligo
} // namespace isaac