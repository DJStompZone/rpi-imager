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

TEST_CASE("matchExpectedSha256 supports extracted or download hash manifests", "[hashutils]")
{
    const QByteArray expected("6e408c99b8e2540aab43a01333d2466d942dbff37c5c3727acf313566852dfc6");
    const QByteArray imageHash("45778e75fdedcffa3682ff9be155d3af7e0a36e267f06100cb5f3c6464c20f9a");

    REQUIRE(hashutils::matchExpectedSha256(expected, imageHash, expected) == hashutils::HashMatchMode::DownloadHash);
    REQUIRE(hashutils::matchExpectedSha256(imageHash, imageHash, expected) == hashutils::HashMatchMode::ImageHash);
    REQUIRE(hashutils::matchExpectedSha256(expected, imageHash, "deadbeef") == hashutils::HashMatchMode::NoMatch);
}
