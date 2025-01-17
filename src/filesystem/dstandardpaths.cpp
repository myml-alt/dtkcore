/*
 * Copyright (C) 2017 ~ 2021 Deepin Technology Co., Ltd.
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

#include "dstandardpaths.h"

#include <QProcessEnvironment>
#include <unistd.h>
#include <pwd.h>

DCORE_BEGIN_NAMESPACE

class DSnapStandardPathsPrivate
{
public:
    inline  static QString writableLocation(QStandardPaths::StandardLocation /*type*/)
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        return env.value("SNAP_USER_COMMON");
    }

    inline static QStringList standardLocations(QStandardPaths::StandardLocation type)
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

        switch (type) {
        case QStandardPaths::GenericDataLocation: {
            QString snapRoot = env.value("SNAP");
            QString genericDataDir = snapRoot + "/usr/share/";
            return QStringList() << genericDataDir;
        }
        default:
            break;
        }

        return QStringList() << env.value("SNAP_USER_COMMON");
    }

private:
    DSnapStandardPathsPrivate();
    ~DSnapStandardPathsPrivate();
    Q_DISABLE_COPY(DSnapStandardPathsPrivate)
};


/*!
  \class Dtk::Core::DStandardPaths
  \inmodule dtkcore
  \brief DStandardPaths提供兼容Snap/Dtk标准的路径模式。DStandardPaths实现了Qt的QStandardPaths主要接口.
  \sa QStandardPaths
 */

/*!
  \enum Dtk::Core::DStandardPaths::Mode
  \brief DStandardPaths支持的路径产生模式。
  \value Auto
  \brief 和Qt标准的行为表现一致。
  \value Snap
  \brief 读取SNAP相关的环境变量，支持将配置存储在SNAP对应目录。
  \value Test
  \brief 和Qt标准的行为表现一致，但是会开启测试模式，参考QStandardPaths::setTestModeEnabled。
 */


static DStandardPaths::Mode s_mode = DStandardPaths::Auto;

QString DStandardPaths::writableLocation(QStandardPaths::StandardLocation type)
{
    switch (s_mode) {
    case Auto:
    case Test:
        return  QStandardPaths::writableLocation(type);
    case Snap:
        return DSnapStandardPathsPrivate::writableLocation(type);
    }
    return QStandardPaths::writableLocation(type);
}

QStringList DStandardPaths::standardLocations(QStandardPaths::StandardLocation type)
{
    switch (s_mode) {
    case Auto:
    case Test:
        return  QStandardPaths::standardLocations(type);
    case Snap:
        return DSnapStandardPathsPrivate::standardLocations(type);
    }
    return  QStandardPaths::standardLocations(type);
}

QString DStandardPaths::locate(QStandardPaths::StandardLocation type, const QString &fileName, QStandardPaths::LocateOptions options)
{
    return QStandardPaths::locate(type, fileName, options);
}

QStringList DStandardPaths::locateAll(QStandardPaths::StandardLocation type, const QString &fileName, QStandardPaths::LocateOptions options)
{
    return QStandardPaths::locateAll(type, fileName, options);
}

QString DStandardPaths::findExecutable(const QString &executableName, const QStringList &paths)
{
    return QStandardPaths::findExecutable(executableName, paths);
}

void DStandardPaths::setMode(DStandardPaths::Mode mode)
{
    s_mode = mode;
    QStandardPaths::setTestModeEnabled(mode == Test);
}

// https://gitlabwh.uniontech.com/wuhan/se/deepin-specifications/-/issues/21

QString DStandardPaths::homePath()
{
    const QByteArray &home = qgetenv("HOME");

    if (!home.isEmpty())
        return QString::fromLocal8Bit(home);

    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    return QString::fromLocal8Bit(homedir);
}

QString DStandardPaths::path(DStandardPaths::XDG type)
{
    switch (type) {
    case XDG::DataHome: {
        const QByteArray &path = qgetenv("XDG_DATA_HOME");
        if (!path.isEmpty())
            return QString::fromLocal8Bit(path);
        return homePath() + QStringLiteral("/.local/share");
    }
    case XDG::CacheHome: {
        const QByteArray &path = qgetenv("XDG_CACHE_HOME");
        if (!path.isEmpty())
            return QString::fromLocal8Bit(path);
        return homePath() + QStringLiteral("/.cache");
    }
    case XDG::ConfigHome: {
        const QByteArray &path = qgetenv("XDG_CONFIG_HOME");
        if (!path.isEmpty())
            return QString::fromLocal8Bit(path);
        return homePath() + QStringLiteral("/.config");
    }
    case XDG::RuntimeTime: {
        const QByteArray &path = qgetenv("XDG_RUNTIME_DIR");
        if (!path.isEmpty())
            return QString::fromLocal8Bit(path);
        return QStringLiteral("/run/user/") + QString::number(getuid());
    }
    }
    return QString();
}

QString DStandardPaths::path(DStandardPaths::DSG type)
{
    switch (type) {
    case DSG::AppData: {
        const QByteArray &path = qgetenv("DSG_APP_DATA");
        //TODO 应用数据目录规范:`/deepin/appdata/{appid}`, now `appid` is not captured.
        return QString::fromLocal8Bit(path);
    }
    case DSG::DataDir: {
        const QByteArray &path = qgetenv("DSG_DATA_DIR");
        if (!path.isEmpty())
            return QString::fromLocal8Bit(path);
        return QStringLiteral("/usr/share/dsg");
    }
    }
    return QString();
}

QString DStandardPaths::filePath(DStandardPaths::XDG type, QString fileName)
{
    const QString &dir = path(type);

    if (dir.isEmpty())
        return QString();

    return dir + QLatin1Char('/') + fileName;
}

QString DStandardPaths::filePath(DStandardPaths::DSG type, const QString fileName)
{
    const QString &dir = path(type);

    if (dir.isEmpty())
        return QString();

    return dir + QLatin1Char('/') + fileName;
}

QString DStandardPaths::homePath(const uint uid)
{
    struct passwd *pw = getpwuid(uid);

    if (!pw)
        return QString();

    const char *homedir = pw->pw_dir;
    return QString::fromLocal8Bit(homedir);
}

DCORE_END_NAMESPACE
