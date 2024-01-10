#ifndef SEARCH_ENGINE_INJECTOR_HPP 
#define SEARCH_ENGINE_INJECTOR_HPP 

#include "search_engine.hpp"
#include "safe_scores_map.hpp"
 

namespace se
{

SearchEngine searchEngine_injector(SafeScoresPointer& scores);    

} // namespace se

 
 
#endif
