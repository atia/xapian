/** @file soaktest.cc
 * @brief Long-running "soak" tests for Xapian.
 */
/* Copyright (C) 2010 Richard boulton
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

#include "soaktest/soaktest.h"

#include "soaktest/soaktest_all.h"
#include "testrunner.h"
#include "testsuite.h"

#include <cstdlib>

using namespace std;

unsigned int g_random_seed;

extern unsigned int initrand()
{
    tout << "Setting random seed to " << g_random_seed << "\n";
    srandom(g_random_seed);
    return g_random_seed;
}

extern unsigned int randint(unsigned int s)
{
    unsigned long int r = static_cast<unsigned long int>(random());
    r = r % static_cast<unsigned long int>(s);
    return static_cast<unsigned int>(r);
}

class SoakTestRunner : public TestRunner
{
    string seed_str;
  public:
    SoakTestRunner() : seed_str("42") {
	test_driver::add_command_line_option("seed", 's', &seed_str);
    }

    int run() const {
	int result = 0;
	g_random_seed = atoi(seed_str.c_str());
#include "soaktest/soaktest_collated.h"
	return result;
    }
};

int main(int argc, char **argv)
{
    SoakTestRunner runner;
    return runner.run_tests(argc, argv);
}
