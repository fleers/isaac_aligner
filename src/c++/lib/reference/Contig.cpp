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
 ** \file Contig.
 **
 ** \brief See Contig.hh
 **
 ** \author Come Raczy
 **/

#include <numeric>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "reference/Contig.hh"

namespace isaac
{
namespace reference
{

size_t genomeLength(const std::vector<Contig> &contigList)
{
    using boost::lambda::_1;
    using boost::lambda::_2;
    using boost::lambda::bind;
    return std::accumulate(
        contigList.begin(), contigList.end(),
        size_t(0), bind<size_t>(std::plus<size_t>(), _1, bind(&Contig::getLength, _2)));
}

} // namespace reference
} // namespace isaac