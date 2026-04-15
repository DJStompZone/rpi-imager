/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2026 Raspberry Pi Ltd
 */

#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <QByteArray>

namespace hashutils {

enum class HashMatchMode {
    NoMatch,
    ImageHash,
    DownloadHash
};

inline QByteArray normalizeExpectedSha256(QByteArray hash)
{
    hash = hash.trimmed().toLower();

    if (hash.startsWith("sha256:"))
        hash = hash.mid(7);

    return hash;
}

inline HashMatchMode matchExpectedSha256(const QByteArray &expectedHash,
                                         const QByteArray &imageHash,
                                         const QByteArray &downloadHash = {})
{
    if (expectedHash.isEmpty())
        return HashMatchMode::NoMatch;

    if (expectedHash == imageHash)
        return HashMatchMode::ImageHash;

    if (!downloadHash.isEmpty() && expectedHash == downloadHash)
        return HashMatchMode::DownloadHash;

    return HashMatchMode::NoMatch;
}

} // namespace hashutils

#endif // HASHUTILS_H
