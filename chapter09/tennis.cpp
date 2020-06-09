#include "catch2/catch.hpp"

#include <iostream>
#include <tuple>
#include <variant>

// This is an example sketched out in Functional Programming in C++ by Ivan Cukic chapter 9 section 9.3
// The pattern matcher template is the authors with out understanding or modification from me
template <typename... Ts>
struct patternMatcher : Ts... { using Ts::operator()...;};
template <typename... Ts> patternMatcher(Ts...) -> patternMatcher<Ts...>;

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

enum class Player
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
        Player leader;
        points otherPlayerScore;
    };

    struct duce {};

    struct advantageScoring
    {
        Player whoHasAdvantate;
    };

    std::variant<normalScoring, fourtyScoring, duce, advantageScoring> m_state;

    public:
    TennisGame()
        : m_state{normalScoring{ points::love, points::love}}
    {

    }

    void ScorePoint(Player whoScoredThePoint)
    {
        std::visit(
            patternMatcher 
            {
                [&](const normalScoring state)
                {
                    std::cout << "scoring point in normal scoring" << std::endl;
                },
                [&](const fourtyScoring state)
                {
                    std::cout << "scoring point in fourty scoring" << std::endl;
                },
                [&](const duce state)
                {
                    std::cout << "scoring point in douce scoring" << std::endl;
                },
                [&](const advantageScoring state)
                {
                    std::cout << "scoring point in advantage scoring" << std::endl;
                }

            },
            m_state);

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

TEST_CASE("test scoring one point", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player1);
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::fifteen == p1Score);
    REQUIRE(TennisScore::love == p2Score);
}