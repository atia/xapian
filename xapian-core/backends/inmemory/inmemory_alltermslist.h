/* inmemory_alltermslist.h
 *
 * ----START-LICENCE----
 * Copyright 1999,2000,2001 BrightStation PLC
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 * -----END-LICENCE-----
 */

#ifndef OM_HGUARD_INMEMORY_ALLTERMSLIST_H
#define OM_HGUARD_INMEMORY_ALLTERMSLIST_H

#include "alltermslist.h"
#include "inmemory_database.h"

/** class for alltermslists over several databases */
class InMemoryAllTermsList : public AllTermsList
{
    private:
	/// Copying is not allowed.
	InMemoryAllTermsList(const InMemoryAllTermsList &);

	/// Assignment is not allowed.
	void operator=(const InMemoryAllTermsList &);

	const std::map<string, InMemoryTerm> *tmap;

	std::map<string, InMemoryTerm>::const_iterator it;

	RefCntPtr<const InMemoryDatabase> database;

	bool started;
    public:
	/// Standard constructor for base class.
	InMemoryAllTermsList(const std::map<string, InMemoryTerm> *tmap_,
			     RefCntPtr<const InMemoryDatabase> database_);

	/// Standard destructor for base class.
	~InMemoryAllTermsList();

        // Gets size of termlist
	om_termcount get_approx_size() const;

	// Gets current termname
	string get_termname() const;

	// Get num of docs indexed by term
	om_doccount get_termfreq() const;

	// Get num of docs indexed by term
	om_termcount get_collection_freq() const;

	TermList * skip_to(const string &tname);

	/** next() causes the AllTermsList to move to the next term in the list.
	 */
	TermList * next();

	// True if we're off the end of the list
	bool at_end() const;
};

#endif /* OM_HGUARD_INMEMORY_ALLTERMSLIST_H */
