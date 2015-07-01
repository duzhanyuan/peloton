/*-------------------------------------------------------------------------
 *
 * transaction.cpp
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 *-------------------------------------------------------------------------
 */

#include "backend/concurrency/transaction.h"

#include "backend/common/synch.h"
#include "backend/common/logger.h"

#include <chrono>
#include <thread>
#include <iomanip>

namespace peloton {
namespace concurrency {

void Transaction::RecordInsert(ItemPointer location) {
    auto& manager = catalog::Manager::GetInstance();
    storage::TileGroup *tile_group = static_cast<storage::TileGroup *>(manager.locator[location.block]);
    inserted_tuples[tile_group].push_back(location.offset);
}

void Transaction::RecordDelete(ItemPointer location) {
    auto& manager = catalog::Manager::GetInstance();
    storage::TileGroup *tile_group = static_cast<storage::TileGroup *>(manager.locator[location.block]);
    deleted_tuples[tile_group].push_back(location.offset);
}

bool Transaction::HasInsertedTuples(storage::TileGroup* tile_group) const {
    auto tile_group_itr = inserted_tuples.find(tile_group);
    if(tile_group_itr != inserted_tuples.end() && !tile_group_itr->second.empty())
        return true;

    return false;
}

bool Transaction::HasDeletedTuples(storage::TileGroup* tile_group) const {
    auto tile_group_itr = deleted_tuples.find(tile_group);
    if(tile_group_itr != deleted_tuples.end() && !tile_group_itr->second.empty())
        return true;

    return false;
}

const std::map<storage::TileGroup*, std::vector<oid_t> >& Transaction::GetInsertedTuples() {
    return inserted_tuples;
}

const std::map<storage::TileGroup*, std::vector<oid_t> >& Transaction::GetDeletedTuples() {
    return deleted_tuples;
}

void Transaction::IncrementRefCount() {
    ++ref_count;
}

void Transaction::DecrementRefCount() {
    assert(ref_count > 0);

    // DROP transaction when ref count reaches 1
    if (ref_count.fetch_sub(1) == 1) {
        delete this;
    }
}

std::ostream& operator<<(std::ostream& os, const Transaction& txn) {

    os << "\tTxn :: @" <<  &txn << " ID : " << std::setw(4) << txn.txn_id
       << " Commit ID : " << std::setw(4) << txn.cid
       << " Last Commit ID : " << std::setw(4) << txn.last_cid;

    if(txn.next == nullptr) {
        os << " Next : " << std::setw(4) << txn.next;
    }
    else {
        os << " Next : " << std::setw(4) << txn.next->txn_id;
    }

    os << " Ref count : " << std::setw(4) << txn.ref_count <<  "\n";
    return os;
}


} // End concurrency namespace
} // End peloton namespace