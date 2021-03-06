/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
http://www.etlcpp.com

Copyright(c) 2016 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#include <UnitTest++/UnitTest++.h>

#include <map>
#include <array>
#include <algorithm>
#include <utility>
#include <iterator>
#include <string>
#include <vector>
#include <numeric>

#include "data.h"

#include "../src/unordered_map.h"

namespace
{
  //*************************************************************************
  struct simple_hash
  {
    size_t operator ()(const std::string& text) const
    {
      return std::accumulate(text.begin(), text.end(), 0);
    }
  };

  //*************************************************************************
  template <typename T1, typename T2>
  bool Check_Equal(T1 begin1, T1 end1, T2 begin2)
  {
    while (begin1 != end1)
    {
      if ((begin1->first != begin2->first) || (begin1->second != begin2->second))
      {
        return false;
      }

      ++begin1;
      ++begin2;
    }

    return true;
  }

  SUITE(test_unordered_map)
  {
    static const size_t SIZE = 10;

    typedef TestDataDC<std::string>  DC;
    typedef TestDataNDC<std::string> NDC;

    typedef std::pair<std::string, DC>  ElementDC;
    typedef std::pair<std::string, NDC> ElementNDC;

    typedef etl::unordered_map<std::string, DC,  SIZE, simple_hash> DataDC;
    typedef etl::unordered_map<std::string, NDC, SIZE, simple_hash> DataNDC;
    typedef etl::iunordered_map<std::string, NDC, simple_hash>      IDataNDC;

    NDC N0 = NDC("A");
    NDC N1 = NDC("B");
    NDC N2 = NDC("C");
    NDC N3 = NDC("D");
    NDC N4 = NDC("E");
    NDC N5 = NDC("F");
    NDC N6 = NDC("G");
    NDC N7 = NDC("H");
    NDC N8 = NDC("I");
    NDC N9 = NDC("J");
    NDC N10 = NDC("K");
    NDC N11 = NDC("L");
    NDC N12 = NDC("M");
    NDC N13 = NDC("N");
    NDC N14 = NDC("O");
    NDC N15 = NDC("P");
    NDC N16 = NDC("Q");
    NDC N17 = NDC("R");
    NDC N18 = NDC("S");
    NDC N19 = NDC("T");

    const char* K0  = "FF"; // 0
    const char* K1  = "FG"; // 1
    const char* K2  = "FH"; // 2
    const char* K3  = "FI"; // 3
    const char* K4  = "FJ"; // 4
    const char* K5  = "FK"; // 5
    const char* K6  = "FL"; // 6
    const char* K7  = "FM"; // 7
    const char* K8  = "FN"; // 8
    const char* K9  = "FO"; // 9
    const char* K10 = "FP"; // 0
    const char* K11 = "FQ"; // 1
    const char* K12 = "FR"; // 2
    const char* K13 = "FS"; // 3
    const char* K14 = "FT"; // 4
    const char* K15 = "FU"; // 5
    const char* K16 = "FV"; // 6
    const char* K17 = "FW"; // 7
    const char* K18 = "FX"; // 8
    const char* K19 = "FY"; // 9

    std::string K[] = { K0, K1, K2, K3, K4, K5, K6, K7, K8, K9, K10, K11, K12, K13, K14, K15, K16, K17, K18, K19 };

    std::vector<ElementNDC> initial_data;
    std::vector<ElementNDC> excess_data;
    std::vector<ElementNDC> different_data;

    //*************************************************************************
    template <typename T1, typename T2>
    bool Check_Equal(T1 begin1, T1 end1, T2 begin2)
    {
      while (begin1 != end1)
      {
        if ((begin1->first != begin2->first) || (begin1->second != begin2->second))
        {
          return false;
        }

        ++begin1;
        ++begin2;
      }

      return true;
    }

    //*************************************************************************
    struct SetupFixture
    {
      SetupFixture()
      {
        ElementNDC n[] =
        {
          ElementNDC(K0, N0), ElementNDC(K1, N1), ElementNDC(K2, N2), ElementNDC(K3, N3), ElementNDC(K4, N4),
          ElementNDC(K5, N5), ElementNDC(K6, N6), ElementNDC(K7, N7), ElementNDC(K8, N8), ElementNDC(K9, N9)
        };

        ElementNDC n2[] =
        {
          ElementNDC(K0, N0), ElementNDC(K1, N1), ElementNDC(K2, N2), ElementNDC(K3, N3), ElementNDC(K4, N4),
          ElementNDC(K5, N5), ElementNDC(K6, N6), ElementNDC(K7, N7), ElementNDC(K8, N8), ElementNDC(K9, N9),
          ElementNDC(K10, N10)
        };

        ElementNDC n3[] =
        {
          ElementNDC(K10, N10), ElementNDC(K11, N11), ElementNDC(K12, N12), ElementNDC(K13, N13), ElementNDC(K14, N14),
          ElementNDC(K15, N15), ElementNDC(K16, N16), ElementNDC(K17, N17), ElementNDC(K18, N18), ElementNDC(K19, N19)
        };

        initial_data.assign(std::begin(n), std::end(n));
        excess_data.assign(std::begin(n2), std::end(n2));
        different_data.assign(std::begin(n3), std::end(n3));
      }
    };

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_default_constructor)
    {
      DataDC data;

      CHECK_EQUAL(data.size(), size_t(0));
      CHECK(data.empty());
      CHECK_EQUAL(data.max_size(), SIZE);
      CHECK(data.begin() == data.end());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_constructor_range)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      CHECK(data.size() == SIZE);
      CHECK(!data.empty());
      CHECK(data.full());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_assignment)
    {
      DataNDC data(initial_data.begin(), initial_data.end());
      DataNDC other_data;

      other_data = data;

      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                other_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_assignment_interface)
    {
      DataNDC data1(initial_data.begin(), initial_data.end());
      DataNDC data2;

      IDataNDC& idata1 = data1;
      IDataNDC& idata2 = data2;

      idata2 = idata1;

      bool isEqual = std::equal(data1.begin(),
                                data1.end(),
                                data2.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_self_assignment)
    {
      DataNDC data(initial_data.begin(), initial_data.end());
      DataNDC other_data(data);

      other_data = other_data;

      bool isEqual = std::equal(data.begin(),
                                data.end(),
                                other_data.begin());

      CHECK(isEqual);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_empty_full)
    {
      DataNDC data;

      CHECK(!data.full());
      CHECK(data.empty());

      data.insert(initial_data.begin(), initial_data.end());

      CHECK(data.full());
      CHECK(!data.empty());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_index_read)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(N0, data[K0]);
      CHECK_EQUAL(N1, data[K1]);
      CHECK_EQUAL(N2, data[K2]);
      CHECK_EQUAL(N3, data[K3]);
      CHECK_EQUAL(N4, data[K4]);
      CHECK_EQUAL(N5, data[K5]);
      CHECK_EQUAL(N6, data[K6]);
      CHECK_EQUAL(N7, data[K7]);
      CHECK_EQUAL(N8, data[K8]);
      CHECK_EQUAL(N9, data[K9]);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_index_write)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      data[K0] = N9;
      data[K1] = N8;
      data[K2] = N7;
      data[K3] = N6;
      data[K4] = N5;
      data[K5] = N4;
      data[K6] = N3;
      data[K7] = N2;
      data[K8] = N1;
      data[K9] = N0;

      CHECK_EQUAL(N9, data[K0]);
      CHECK_EQUAL(N8, data[K1]);
      CHECK_EQUAL(N7, data[K2]);
      CHECK_EQUAL(N6, data[K3]);
      CHECK_EQUAL(N5, data[K4]);
      CHECK_EQUAL(N4, data[K5]);
      CHECK_EQUAL(N3, data[K6]);
      CHECK_EQUAL(N2, data[K7]);
      CHECK_EQUAL(N1, data[K8]);
      CHECK_EQUAL(N0, data[K9]);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_at)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(data.at(K0), N0);
      CHECK_EQUAL(data.at(K1), N1);
      CHECK_EQUAL(data.at(K2), N2);
      CHECK_EQUAL(data.at(K3), N3);
      CHECK_EQUAL(data.at(K4), N4);
      CHECK_EQUAL(data.at(K5), N5);
      CHECK_EQUAL(data.at(K6), N6);
      CHECK_EQUAL(data.at(K7), N7);
      CHECK_EQUAL(data.at(K8), N8);
      CHECK_EQUAL(data.at(K9), N9);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_at_const)
    {
      const DataNDC data(initial_data.begin(), initial_data.end());

      CHECK_EQUAL(data.at(K0), N0);
      CHECK_EQUAL(data.at(K1), N1);
      CHECK_EQUAL(data.at(K2), N2);
      CHECK_EQUAL(data.at(K3), N3);
      CHECK_EQUAL(data.at(K4), N4);
      CHECK_EQUAL(data.at(K5), N5);
      CHECK_EQUAL(data.at(K6), N6);
      CHECK_EQUAL(data.at(K7), N7);
      CHECK_EQUAL(data.at(K8), N8);
      CHECK_EQUAL(data.at(K9), N9);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_assign_range)
    {
      DataNDC data;

      data.assign(initial_data.begin(), initial_data.end());

      DataNDC::iterator idata;

      for (size_t i = 0; i < 10; ++i)
      {
        idata = data.find(K[i]);
        CHECK(idata != data.end());
      }
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_value)
    {
      DataNDC data;

      data.insert(DataNDC::value_type(K0,  N0)); // Inserted
      data.insert(DataNDC::value_type(K2,  N2)); // Inserted
      data.insert(DataNDC::value_type(K1,  N1)); // Inserted
      data.insert(DataNDC::value_type(K11, N1)); // Duplicate hash. Inserted
      data.insert(DataNDC::value_type(K1,  N3)); // Duplicate key.  Not inserted

      CHECK_EQUAL(4U, data.size());

      DataNDC::iterator idata;

      idata = data.find(K0);
      CHECK(idata != data.end());
      CHECK(idata->first  == K0);
      CHECK(idata->second == N0);

      idata = data.find(K1);
      CHECK(idata != data.end());
      CHECK(idata->first  == K1);
      CHECK(idata->second == N1);

      idata = data.find(K2);
      CHECK(idata != data.end());
      CHECK(idata->first  == K2);
      CHECK(idata->second == N2);

      idata = data.find(K11);
      CHECK(idata != data.end());
      CHECK(idata->first  == K11);
      CHECK(idata->second == N1);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_value_excess)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      CHECK_THROW(data.insert(std::make_pair(K10, N10)), etl::unordered_map_full);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_range)
    {
      DataNDC data;

      data.insert(initial_data.begin(), initial_data.end());

      for (size_t i = 0; i < data.size(); ++i)
      {
        DataNDC::iterator idata = data.find(initial_data[i].first);
        CHECK(idata != data.end());
      }
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_insert_range_excess)
    {
      DataNDC data;

      CHECK_THROW(data.insert(excess_data.begin(), excess_data.end()), etl::unordered_map_full);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_key)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      size_t count = data.erase(K5);

      CHECK_EQUAL(1, count);

      DataNDC::iterator idata = data.find(K5);
      CHECK(idata == data.end());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_single)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      DataNDC::const_iterator idata = data.find(K5);
      DataNDC::const_iterator inext = idata;
      ++inext;

      DataNDC::const_iterator iafter = data.erase(idata);
      idata = data.find(K5);

      CHECK(idata == data.end());
      CHECK(inext == iafter);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_erase_range)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      DataNDC::iterator idata     = data.find(K5);
      DataNDC::iterator idata_end = data.find(K8);

      idata = data.erase(idata, idata_end); // Erase K5, K6, K7
      CHECK(idata == data.find(K8));

      idata = data.find(K0);
      CHECK(idata != data.end());

      idata = data.find(K1);
      CHECK(idata != data.end());

      idata = data.find(K2);
      CHECK(idata != data.end());

      idata = data.find(K3);
      CHECK(idata != data.end());

      idata = data.find(K4);
      CHECK(idata != data.end());

      idata = data.find(K5);
      CHECK(idata == data.end());

      idata = data.find(K6);
      CHECK(idata == data.end());

      idata = data.find(K7);
      CHECK(idata == data.end());

      idata = data.find(K8);
      CHECK(idata != data.end());

      idata = data.find(K9);
      CHECK(idata != data.end());
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_clear)
    {
      DataNDC data(initial_data.begin(), initial_data.end());
      data.clear();

      CHECK_EQUAL(data.size(), size_t(0));
    }


    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_count_key)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      size_t count = data.count(K5);
      CHECK_EQUAL(1, count);

      count = data.count(K12);
      CHECK_EQUAL(0, count);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_equal_range)
    {
      DataNDC data(initial_data.begin(), initial_data.end());

      std::pair<DataNDC::iterator, DataNDC::iterator> result;

      result = data.equal_range(K0);
      CHECK(result.first  == data.begin());
      CHECK(result.second != data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K0);

      result = data.equal_range(K3);
      CHECK(result.first  != data.begin());
      CHECK(result.second != data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K3);

      result = data.equal_range(K9);
      CHECK(result.first  != data.begin());
      CHECK(result.second == data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K9);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_equal_range_const)
    {
      const DataNDC data(initial_data.begin(), initial_data.end());

      std::pair<DataNDC::const_iterator, DataNDC::const_iterator> result;

      result = data.equal_range(K0);
      CHECK(result.first == data.begin());
      CHECK(result.second != data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K0);

      result = data.equal_range(K3);
      CHECK(result.first != data.begin());
      CHECK(result.second != data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K3);

      result = data.equal_range(K9);
      CHECK(result.first != data.begin());
      CHECK(result.second == data.end());
      CHECK_EQUAL(std::distance(result.first, result.second), 1);
      CHECK_EQUAL(result.first->first, K9);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_equal)
    {
      const DataNDC initial1(initial_data.begin(), initial_data.end());
      const DataNDC initial2(initial_data.begin(), initial_data.end());

      CHECK(initial1 == initial2);

      const DataNDC different(different_data.begin(), different_data.end());

      CHECK(!(initial1 == different));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_not_equal)
    {
      const DataNDC initial1(initial_data.begin(), initial_data.end());
      const DataNDC initial2(initial_data.begin(), initial_data.end());

      CHECK(!(initial1 != initial2));

      const DataNDC different(different_data.begin(), different_data.end());

      CHECK(initial1 != different);
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_hash_function)
    {
      DataNDC data;
      DataNDC::hasher hash_function =  data.hash_function();

      CHECK_EQUAL(simple_hash()(std::string("ABCDEF")), hash_function(std::string("ABCDEF")));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_key_eq_function)
    {
      DataNDC data;
      DataNDC::key_equal key_eq = data.key_eq();

      CHECK(key_eq(std::string("ABCDEF"), std::string("ABCDEF")));
      CHECK(!key_eq(std::string("ABCDEF"), std::string("ABCDEG")));
    }

    //*************************************************************************
    TEST_FIXTURE(SetupFixture, test_load_factor)
    {
      // Empty.
      DataNDC data;
      CHECK_CLOSE(0.0, data.load_factor(), 0.01);

      // Half the buckets used.
      data.assign(initial_data.begin(), initial_data.begin() + (initial_data.size() / 2));
      CHECK_CLOSE(0.5, data.load_factor(), 0.01);

      // All of the buckets used.
      data.clear();
      data.assign(initial_data.begin(), initial_data.end());
      CHECK_CLOSE(1.0, data.load_factor(), 0.01);
    }
  };
}
