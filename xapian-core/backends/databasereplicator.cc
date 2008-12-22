/** @file databasereplicator.cc
 * @brief Support class for database replication.
 */
/* Copyright 2008 Lemur Consulting Ltd
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <config.h>

#include "databasereplicator.h"

#include "xapian/error.h"
#include "xapian/version.h" // For XAPIAN_HAS_XXX_BACKEND.

#include "fileutils.h"
#include "omdebug.h"
#include "utils.h"

#include "safeerrno.h"

#ifdef XAPIAN_HAS_CHERT_BACKEND
# include "chert/chert_databasereplicator.h"
#endif
#ifdef XAPIAN_HAS_FLINT_BACKEND
# include "flint/flint_databasereplicator.h"
#endif

using namespace std;

namespace Xapian {

DatabaseReplicator::DatabaseReplicator()
{
}

DatabaseReplicator::~DatabaseReplicator()
{
}

Xapian::Internal::RefCntPtr<DatabaseReplicator>
DatabaseReplicator::open(const std::string & path)
{
    DEBUGAPICALL(void, "DatabaseReplicator::DatabaseReplicator", path);

    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
	throw DatabaseOpeningError("Couldn't stat '" + path + "'", errno);
    }

    if (rare(!S_ISDIR(statbuf.st_mode))) {
	throw DatabaseOpeningError("Not a regular file or directory: '" + path + "'");
    }

#ifdef XAPIAN_HAS_FLINT_BACKEND
    if (file_exists(path + "/iamflint")) {
	//return new FlintDatabaseReplicator(path);
	DatabaseReplicator * result = new FlintDatabaseReplicator(path);
	return result;
    }
#endif

#ifdef XAPIAN_HAS_CHERT_BACKEND
    if (file_exists(path + "/iamchert")) {
	return new ChertDatabaseReplicator(path);
    }
#endif

    throw DatabaseOpeningError("Couldn't detect type of database");
}

}