#ifndef SAFE_SCORE_HPP 
#define SAFE_SCORE_HPP 

#include <memory>
#include <unordered_map>
#include <string>

 
namespace se{

using ScorsMap = std::unordered_map<std::string, double>;

class SafeScoresPointer
{
public:
    SafeScoresPointer();
    ~SafeScoresPointer() = default;
    SafeScoresPointer(const SafeScoresPointer&) = default;
    SafeScoresPointer& operator= (const SafeScoresPointer&) = default;

    std::shared_ptr<ScorsMap> getScores()const;
    void updateScores(const ScorsMap& scorsMap);

private:
    std::shared_ptr<ScorsMap> m_scoresPointer;
};

} //se
#endif
 