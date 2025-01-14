/*
  This file is part of KDUtils.

  SPDX-FileCopyrightText: 2018-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Paul Lemire <paul.lemire@kdab.com>

  SPDX-License-Identifier: AGPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
//krazy:excludeall=insecurenet "http usage in this file is for testing purposes"

#include <KDUtils/url.h>

namespace KC = KDUtils;

#define StringLiteral(str)                    \
    ([]() noexcept -> std::string {           \
        using namespace std::string_literals; \
        return u8##str##s;                    \
    }())

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_SUITE("Url")
{

    TEST_CASE("init")
    {
        static_assert(std::is_destructible<KC::Url>{},
                      "Url should be destructible");
        static_assert(std::is_default_constructible<KC::Url>{},
                      "Url should be default constructible");
        static_assert(std::is_copy_constructible<KC::Url>{},
                      "Url should be copy constructible");
        static_assert(std::is_copy_assignable<KC::Url>{},
                      "Url should be copy assignable");
        static_assert(std::is_move_constructible<KC::Url>{},
                      "Url should be move constructible");
        static_assert(std::is_move_assignable<KC::Url>{},
                      "Url should be move assignable");
    }

    TEST_CASE("checkEmpty")
    {
        {
            // GIVEN
            KC::Url url;

            // THEN
            CHECK(url.isEmpty());
            CHECK(url.empty());
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:file.txt"));

            // THEN
            CHECK(!url.isEmpty());
            CHECK(!url.empty());
        }
    }

    TEST_CASE("checkToLocalFile")
    {
        {
            // GIVEN
            KC::Url url(StringLiteral("file:file.txt"));

            // THEN
            CHECK(url.toLocalFile() == StringLiteral("file.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:/home/bruce_w/file.txt"));

            // THEN
            CHECK(url.toLocalFile() == StringLiteral("/home/bruce_w/file.txt"));
        }
        {
            // GIVEN -> No scheme
            KC::Url url(StringLiteral("file.txt"));

            // THEN
            CHECK(url.toLocalFile() == StringLiteral(""));
        }
        {
            // GIVEN -> No file: scheme
            KC::Url url(StringLiteral("http:file.txt"));

            // THEN
            CHECK(url.toLocalFile() == StringLiteral(""));
        }
    }

    TEST_CASE("checkFromLocalFile")
    {
        {
            // GIVEN
            KC::Url url = KC::Url::fromLocalFile(StringLiteral("file.txt"));

            // THEN
            CHECK(url == KC::Url(StringLiteral("file:file.txt")));
        }
        {
            // GIVEN
            KC::Url url = KC::Url::fromLocalFile(StringLiteral("/home/bruce_w/file.txt"));

            // THEN
            CHECK(url == KC::Url(StringLiteral("file:///home/bruce_w/file.txt")));
        }
        {
            // GIVEN
            KC::Url url = KC::Url::fromLocalFile(StringLiteral("file:file.txt"));

            // THEN -> Nothing since url has already a scheme
            CHECK(url == KC::Url(StringLiteral("file:file.txt")));
        }
    }

    TEST_CASE("checkScheme")
    {
        {
            // GIVEN
            KC::Url url(StringLiteral("http://www.msn.fr/"));

            // THEN
            CHECK(url.scheme() == StringLiteral("http"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:///myfile.txt"));

            // THEN
            CHECK(url.scheme() == StringLiteral("file"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:///home/bruce_w/myfile.txt"));

            // THEN
            CHECK(url.scheme() == StringLiteral("file"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:myfile.txt"));

            // THEN
            CHECK(url.scheme() == StringLiteral("file"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral(":/myfile.txt"));

            // THEN
            CHECK(url.scheme() == StringLiteral(""));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("myfile.txt"));

            // THEN
            CHECK(url.scheme() == StringLiteral(""));
        }
    }

    TEST_CASE("checkPath")
    {
        {
            // GIVEN
            KC::Url url(StringLiteral("http://www.msn.fr/"));

            // THEN
            CHECK(url.path() == StringLiteral("www.msn.fr/"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:///myfile.txt"));

            // THEN
            CHECK(url.path() == StringLiteral("/"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file://myfile.txt"));

            // THEN
            CHECK(url.path() == StringLiteral(""));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:myfile.txt"));

            // THEN
            CHECK(url.path() == StringLiteral(""));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral(":/myfile.txt"));

            // THEN
            CHECK(url.path() == StringLiteral("/"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("myfile.txt"));

            // THEN
            CHECK(url.path() == StringLiteral(""));
        }
    }

    TEST_CASE("checkFileName")
    {
        {
            // GIVEN
            KC::Url url(StringLiteral("http://www.msn.fr/"));

            // THEN
            CHECK(url.fileName() == StringLiteral(""));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:///myfile.txt"));

            // THEN
            CHECK(url.fileName() == StringLiteral("myfile.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file://myfile.txt"));

            // THEN
            CHECK(url.fileName() == StringLiteral("myfile.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("file:myfile.txt"));

            // THEN
            CHECK(url.fileName() == StringLiteral("myfile.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral(":/myfile.txt"));

            // THEN
            CHECK(url.fileName() == StringLiteral("myfile.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("myfile.txt"));

            // THEN
            CHECK(url.fileName() == StringLiteral("myfile.txt"));
        }
        {
            // GIVEN
            KC::Url url(StringLiteral("myfile.txt/"));

            // THEN
            CHECK(url.fileName() == StringLiteral(""));
        }
    }
}
