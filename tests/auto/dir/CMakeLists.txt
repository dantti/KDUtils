# This file is part of KDUtils.
#
# SPDX-FileCopyrightText: 2021-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Paul Lemire <paul.lemire@kdab.com>
#
# SPDX-License-Identifier: AGPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

add_executable(tst_dir tst_dir.cpp)
target_link_libraries(tst_dir PRIVATE KDUtils doctest::doctest)
get_filename_component(ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../assets/ ABSOLUTE)
target_compile_definitions(tst_dir PRIVATE ASSETS="${ASSETS_DIR}/" TST_DIR="${CMAKE_BINARY_DIR}/bin/")
doctest_discover_tests(tst_dir ADD_LABELS 1 PROPERTIES LABELS "KDUtils")
