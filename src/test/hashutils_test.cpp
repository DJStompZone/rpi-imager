/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2026 Raspberry Pi Ltd
 */

#include <catch2/catch_test_macros.hpp>
#include "../hashutils.h"

TEST_CASE("normalizeExpectedSha256 canonicalizes equivalent hash representations", "[hashutils]")
{
    const QByteArray canonical("abcdef0123456789");

    REQUIRE(hashutils::normalizeExpectedSha256("ABCDEF0123456789") == canonical);
    REQUIRE(hashutils::normalizeExpectedSha256("  abcdef0123456789 \r\n") == canonical);
    REQUIRE(hashutils::normalizeExpectedSha256("sha256:abcdef0123456789") == canonical);
    REQUIRE(hashutils::normalizeExpectedSha256(" SHA256:ABCDEF0123456789 \n") == canonical);
}

TEST_CASE("normalizeExpectedSha256 leaves non-prefixed values intact except case/trim", "[hashutils]")
{
    REQUIRE(hashutils::normalizeExpectedSha256(" sha1:ABCDEF ") == QByteArray("sha1:abcdef"));
}
