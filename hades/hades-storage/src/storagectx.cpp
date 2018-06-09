//
// Created by Leon on 01/06/2018.
//

#include <storage/storagectx.h>
#include <common/log/log.h>
#include <storage/mysql/mysqlplayers.h>

using namespace hades;

static std::shared_ptr<StorageCtx> currentCtx;

void StorageCtx::ctx(std::shared_ptr<StorageCtx> ctx) {
    currentCtx = ctx;
}

std::shared_ptr<StorageCtx> StorageCtx::ctx() {
    return currentCtx;
}
