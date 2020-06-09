#include "catch2/catch.hpp"

#include <tuple>
#include <variant>

enum class TennisScore
{
    love,
    fifteen,
    thirty,
    fourty,
    advantage,
    notAdvantage,
    victory
};

enum class player
{
    player1,
    player2
};

class TennisGame
{
    enum class points 
    {
        love,
        fifteen,
        thirty
    };

    struct normalScoring
    {
        points player1Score;
        points player2Score;
    };

    struct fourtyScoring
    {
        player leader;
        points other_player_score;
    };

    struct duce {};

    struct advantageScoring
    {
        player whoHasAdvantate;
    };

    std::variant<normalScoring, fourtyScoring, duce, advantageScoring> m_state;

    public:
    TennisGame()
        : m_state{normalScoring{ points::love, points::love}}
    {

    }

    std::tuple<TennisScore, TennisScore> GetScore()
    {
        return {TennisScore::love, TennisScore::love};
    }
};

TEST_CASE("test constructor", "[tennis]")
{
    TennisGame testObject;
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::love == p1Score);
    REQUIRE(TennisScore::love == p2Score);
}