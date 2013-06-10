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
 ** \file TileMetadata.hh
 **
 ** Packaging of the metadata associated to a tile.
 **
 ** \author Come Raczy
 **/

#ifndef iSAAC_FLOWCELL_TILE_METADATA_HH
#define iSAAC_FLOWCELL_TILE_METADATA_HH

#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

namespace isaac
{
namespace flowcell
{

/**
 ** \brief Read-only interface to the metadata associated to a tile.
 **
 ** The intended usage is for tile management in ordered collections (the index
 ** in the collectionis is associated to each tile metadata instance).
 **
 ** \todo Provide a robust and flexible indexing mechanism for the tiles.
 **/
class TileMetadata
{
    /*
     * \brief enable serialization
     */
    template <class Archive> friend void serialize(Archive &ar, TileMetadata &tm, const unsigned int version);

public:
    enum Compression
    {
        NoCompression,
        GzCompression
    };

    TileMetadata();
    TileMetadata(const TileMetadata &that, const unsigned newIndex);
    TileMetadata(
        const std::string &flowcellId,
        const unsigned flowcellIndex,
        const unsigned tile,
        const unsigned int lane,
        const boost::filesystem::path &baseCallsPath,
        const unsigned int clusterCount,
        const Compression compression,
        const unsigned int index);
    TileMetadata(const TileMetadata &tileMetadata);
    TileMetadata &operator=(const TileMetadata &tileMetadata);
    /// \brief Allow inheritance
    virtual ~TileMetadata() {}
    const std::string &getFlowcellId() const {return flowcellId_;}
    unsigned getFlowcellIndex() const {return flowcellIndex_;}
    unsigned int getTile() const {return tile_;}
    const std::string &getTileString() const {return tileString_;}
    unsigned int getLane() const {return lane_;}
    const std::string &getLaneString() const {return laneString_;}
    boost::filesystem::path getBaseCallsPath() const {return baseCallsPath_;}

    unsigned int getClusterCount() const {return clusterCount_;}
    Compression getCompression() const {return compression_;}
    unsigned int getIndex() const {return index_;}

    bool operator==(const TileMetadata &rhs) const;
    bool operator!=(const TileMetadata &rhs) const
    {
        return !(rhs == *this);
    }


protected:
    void setFlowcellId(const std::string &flowcellId);
    void setTile(unsigned int tile);
    void setLane(unsigned int lane);
    void setBaseCallsPath(const boost::filesystem::path baseCallsPath);
    void setClusterCount(unsigned int clusterCount);
    void setIndex(unsigned int index);
private:
    std::string flowcellId_;
    unsigned flowcellIndex_;
    unsigned int tile_;
    std::string tileString_;
    unsigned int lane_;
    std::string laneString_;
    boost::filesystem::path baseCallsPath_;
    /// \note initializing this value is left to derived classes
    unsigned int clusterCount_;
    Compression compression_;
    unsigned int index_;
};

//typedef std::vector<TileMetadata> TileMetadataList;
struct TileMetadataList : public std::vector<flowcell::TileMetadata>
{
    TileMetadataList(){}
//    TileMetadataList(size_t size) : std::vector<flowcell::TileMetadata>(size){}
    TileMetadataList(const TileMetadataList &that) : std::vector<flowcell::TileMetadata>(that){}
};

inline unsigned getMaxTileClulsters(const TileMetadataList &tileMetadataList_)
{
    return std::max_element(tileMetadataList_.begin(), tileMetadataList_.end(),
                            boost::bind(&flowcell::TileMetadata::getClusterCount, _1)<
                            boost::bind(&flowcell::TileMetadata::getClusterCount, _2))->getClusterCount();
}

inline boost::filesystem::path getLongestBaseCallsPath(const TileMetadataList &tileMetadataList)
{
    boost::filesystem::path ret;
    BOOST_FOREACH(const flowcell::TileMetadata &tileMetadata, tileMetadataList)
    {
        if (ret.string().size() < tileMetadata.getBaseCallsPath().string().size())
        {
            ret = tileMetadata.getBaseCallsPath();
        }
    }
    return ret;
}

inline std::ostream &operator<<(std::ostream &os, const TileMetadata &tileMetadata)
{
    return os << "TileMetadata(" 
              << tileMetadata.getFlowcellId() << ", " 
              << tileMetadata.getTile() << ", " 
              << tileMetadata.getLane() << ", " 
              << tileMetadata.getBaseCallsPath() << ", " 
              << tileMetadata.getClusterCount() << ", "
              << tileMetadata.getIndex()
              << ")";
}

inline std::ostream &operator<<(std::ostream &os, const TileMetadataList &tileMetadataList)
{
    std::copy(tileMetadataList.begin(), tileMetadataList.end(), std::ostream_iterator<TileMetadata>(os, " "));
    return os;
}

} // namespace flowcell
} // namespace isaac

#endif // #ifndef iSAAC_FLOWCELL_TILE_METADATA_HH
