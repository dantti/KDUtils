/*
  This file is part of KDUtils.

  SPDX-FileCopyrightText: 2021-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Paul Lemire <paul.lemire@kdab.com>

  SPDX-License-Identifier: AGPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDUTILS_DIR_H
#define KDUTILS_DIR_H

#include <KDUtils/kdutils_export.h>
#include <string>
#include <filesystem>

namespace KDUtils {

class KDUTILS_EXPORT Dir
{
public:
    Dir();
    Dir(const char *path);
    Dir(const std::string &path);
    Dir(const std::filesystem::path &path);

    bool exists() const;
    bool mkdir();
    bool rmdir();
    const std::string &path() const;
    std::string dirName() const;
    std::string absoluteFilePath(const std::string &file) const;

    static Dir applicationDir();

    bool operator==(const Dir &other) const;

private:
    std::string m_path;
};

} // namespace KDUtils

#endif // KUESA_COREUTILS_DIR_H
