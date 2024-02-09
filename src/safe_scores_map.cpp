#include "safe_scores_map.hpp"
 

se::SafeScoresPointer::SafeScoresPointer()
: m_scoresPointer(nullptr)
{}

std::shared_ptr<se::ScorsMap> se::SafeScoresPointer::getScores()const
{
    auto map = atomic_load(&m_scoresPointer);
    return map;
}

void se::SafeScoresPointer::updateScores(const ScorsMap& scorsMap)
{
    std::atomic_store(&m_scoresPointer, std::make_shared<ScorsMap>(scorsMap));
}
