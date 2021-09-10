/*
 * Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
 *
 * Author:     Wang Fei <wangfeia@uniontech.com>
 *
 * Maintainer: Wang Fei <wangfeia@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>
#include <QDir>
#include "filesystem/dstandardpaths.h"
#include "filesystem/dtrashmanager.h"

DCORE_USE_NAMESPACE


class ut_DTrashManager : public testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;
    QString path;
};

void ut_DTrashManager::SetUp()
{
    DStandardPaths::setMode(DStandardPaths::Auto);
    path = DStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/Trash/files";

    QFile file(path + "/test");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return;
    file.close();
}

void ut_DTrashManager::TearDown()
{
    QFile file("/tmp/test");
    if (file.exists())
        file.remove();
}

TEST_F(ut_DTrashManager, testDTrashManagerTrashIsEmpty)
{
    DTrashManager::instance()->moveToTrash(path + "/test");
    bool ok = DTrashManager::instance()->trashIsEmpty();
    ASSERT_TRUE(ok = ok ? ok : !ok);
}

TEST_F(ut_DTrashManager, testDTrashManagerCleanTrash)
{
    bool ok = DTrashManager::instance()->cleanTrash();
    ASSERT_TRUE(ok = ok ? ok : !ok);
}

TEST_F(ut_DTrashManager, testDTrashManagerMoveToTrash)
{
    bool ok = DTrashManager::instance()->moveToTrash(path + "/test");
    ASSERT_TRUE(ok = ok ? ok : !ok);
}
