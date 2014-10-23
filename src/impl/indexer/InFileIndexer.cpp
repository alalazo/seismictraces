#include <impl/indexer/InFileIndexer.h>

using namespace std;
using namespace boost::filesystem;

namespace seismic {
    template<>
    bool InFileIndexer::m_is_registered(      
    InFileIndexer::factory_type::getFactory()->registerType("InFile",make_shared<InFileIndexer>())
    );
}