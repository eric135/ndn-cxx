/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2017 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#include "security/pib/identity-container.hpp"
#include "security/pib/pib.hpp"
#include "security/pib/pib-memory.hpp"

#include "boost-test.hpp"
#include "pib-data-fixture.hpp"

namespace ndn {
namespace security {
namespace pib {
namespace tests {

using namespace ndn::security::tests;

BOOST_AUTO_TEST_SUITE(Security)
BOOST_AUTO_TEST_SUITE(Pib)
BOOST_AUTO_TEST_SUITE(TestIdentityContainer)

using pib::Pib;

BOOST_FIXTURE_TEST_CASE(Basic, PibDataFixture)
{
  auto pibImpl = make_shared<PibMemory>();
  Pib pib("pib-memory", "", pibImpl);

  Identity identity1 = pib.addIdentity(id1);
  Identity identity2 = pib.addIdentity(id2);

  IdentityContainer container = pib.getIdentities();
  BOOST_CHECK_EQUAL(container.size(), 2);
  BOOST_CHECK(container.find(id1) != container.end());
  BOOST_CHECK(container.find(id2) != container.end());

  std::set<Name> idNames;
  idNames.insert(id1);
  idNames.insert(id2);

  IdentityContainer::const_iterator it = container.begin();
  std::set<Name>::const_iterator testIt = idNames.begin();
  BOOST_CHECK_EQUAL((*it).getName(), *testIt);
  it++;
  testIt++;
  BOOST_CHECK_EQUAL((*it).getName(), *testIt);
  ++it;
  testIt++;
  BOOST_CHECK(it == container.end());

  size_t count = 0;
  testIt = idNames.begin();
  for (const auto& identity : container) {
    BOOST_CHECK_EQUAL(identity.getName(), *testIt);
    testIt++;
    count++;
  }
  BOOST_CHECK_EQUAL(count, 2);
}

BOOST_AUTO_TEST_SUITE_END() // TestIdentityContainer
BOOST_AUTO_TEST_SUITE_END() // Pib
BOOST_AUTO_TEST_SUITE_END() // Security

} // namespace tests
} // namespace pib
} // namespace security
} // namespace ndn
