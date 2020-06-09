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
    duce,
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

    struct winner
    {
        Player whoWon;
        TennisScore otherPlayerScore;
    };

    points Score(points initialValue)
    {
        if(points::love == initialValue)
        {
            return points::fifteen;
        }
        return points::thirty;
    }

    TennisScore Convert(points value)
    {
        switch(value)
        {
        case points::love :
            return TennisScore::love;
        case points::fifteen :
            return TennisScore::fifteen;
        case points::thirty :
            return TennisScore::thirty;
        }
        return TennisScore::love;
    }

    std::variant<normalScoring, fourtyScoring, duce, advantageScoring, winner> m_state;

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
                [&](normalScoring &state)
                {
                    if(Player::player1 == whoScoredThePoint)
                    {
                        if(points::thirty == state.player1Score)
                        {
                            m_state = fourtyScoring {Player::player1, state.player2Score};
                        }
                        else 
                        {
                            state.player1Score = Score(state.player1Score);
                        }
                    }
                    else 
                    {
                        if(points::thirty == state.player2Score)
                        {
                            m_state = fourtyScoring {Player::player2, state.player1Score};
                        }
                        else 
                        {
                            state.player2Score = Score(state.player2Score);
                        }
                    }
                },
                [&](fourtyScoring &state)
                {
                    if(state.leader == whoScoredThePoint)
                    {

                    }
                    else
                    {
                        if(points::thirty == state.otherPlayerScore)
                        {
                            m_state = duce{};
                        }
                        else 
                        {
                            state.otherPlayerScore = Score(state.otherPlayerScore);
                        }
                    }
                    
                },
                [&](const duce state)
                {
                    std::cout << "scoring point in douce scoring" << std::endl;
                },
                [&](const advantageScoring state)
                {
                    std::cout << "scoring point in advantage scoring" << std::endl;
                },
                [&](const winner state)
                {
                }

            },
            m_state);
    }

    std::tuple<TennisScore, TennisScore> GetScore()
    {
        std::tuple<TennisScore, TennisScore> result;
        std::visit(
            patternMatcher 
            {
                [&](const normalScoring state)
                {
                    result = {Convert(state.player1Score), Convert(state.player2Score)};
                },
                [&](const fourtyScoring state)
                {
                    if(Player::player1 == state.leader)
                    {
                        result = {TennisScore::fourty, Convert(state.otherPlayerScore) };
                    }
                    else
                    {
                        result = {Convert(state.otherPlayerScore), TennisScore::fourty };
                    }
                },
                [&](const duce state)
                {
                    result = {TennisScore::duce, TennisScore::duce};
                },
                [&](const advantageScoring state)
                {
                    std::cout << "GetScore in advantage scoring" << std::endl;
                    result = {TennisScore::love, TennisScore::love};
                },
                [&](const winner state)
                {
                    std::cout << "GetScore in winner scoring" << std::endl;
                    result = {TennisScore::love, TennisScore::love};
                }
            },
            m_state);
        return result;
    }
};

TEST_CASE("test constructor", "[tennis]")
{
    TennisGame testObject;
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::love == p1Score);
    REQUIRE(TennisScore::love == p2Score);
}

TEST_CASE("test scoring no state transition", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player1);
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::fifteen == p1Score);
    REQUIRE(TennisScore::love == p2Score);

    testObject.ScorePoint(Player::player1);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::thirty == p1Score);
    REQUIRE(TennisScore::love == p2Score);

    testObject.ScorePoint(Player::player2);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::thirty == p1Score);
    REQUIRE(TennisScore::fifteen == p2Score);

    testObject.ScorePoint(Player::player2);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::thirty == p1Score);
    REQUIRE(TennisScore::thirty == p2Score);
}

TEST_CASE("test scoring forty p1", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::fourty == p1Score);
    REQUIRE(TennisScore::love == p2Score);

    testObject.ScorePoint(Player::player2);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::fourty == p1Score);
    REQUIRE(TennisScore::fifteen == p2Score);

    testObject.ScorePoint(Player::player2);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::fourty == p1Score);
    REQUIRE(TennisScore::thirty == p2Score);
}

TEST_CASE("test scoring forty p2", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player2);
    testObject.ScorePoint(Player::player2);
    testObject.ScorePoint(Player::player2);
    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::love == p1Score);
    REQUIRE(TennisScore::fourty == p2Score);

    testObject.ScorePoint(Player::player1);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::fifteen == p1Score);
    REQUIRE(TennisScore::fourty == p2Score);

    testObject.ScorePoint(Player::player1);
    std::tie(p1Score, p2Score) = testObject.GetScore();

    REQUIRE(TennisScore::thirty == p1Score);
    REQUIRE(TennisScore::fourty == p2Score);
}

TEST_CASE("test p1 wins at forty", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);

    REQUIRE(TennisScore::victory == p1Score);
    REQUIRE(TennisScore::love == p2Score);
}

TEST_CASE("test scoring duce advantage", "[tennis]")
{
    TennisGame testObject;
    
    testObject.ScorePoint(Player::player2);
    testObject.ScorePoint(Player::player2);
    testObject.ScorePoint(Player::player2);
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);
    testObject.ScorePoint(Player::player1);

    auto [ p1Score, p2Score] = testObject.GetScore();

    REQUIRE(TennisScore::duce == p1Score);
    REQUIRE(TennisScore::duce == p2Score);
}