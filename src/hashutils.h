/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2026 Raspberry Pi Ltd
 */

#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <QByteArray>

namespace hashutils {

inline QByteArray normalizeExpectedSha256(QByteArray hash)
{
    hash = hash.trimmed().toLower();

    if (hash.startsWith("sha256:"))
        hash = hash.mid(7);

    return hash;
}

} // namespace hashutils

#endif // HASHUTILS_H
