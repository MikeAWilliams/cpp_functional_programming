#include <string> 
#include <chrono>
#include <thread>
 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"

using namespace std::chrono_literals;

class SimplePerson
{
public:
	SimplePerson(std::string first, std::string last)
		: m_firstName{std::move(first)}
		, m_lastName{std::move(last)}
	{
	}

	SimplePerson(const SimplePerson& other)
		: m_firstName{other.m_firstName}
		, m_lastName{other.m_lastName}
	{
		// make the copy arbitrarily expensive
		std::this_thread::sleep_for(1ms);
	}

	SimplePerson(SimplePerson&& other)
		: m_firstName{std::move(other.m_firstName)}
		, m_lastName{std::move(other.m_lastName)}
	{
	}

	SimplePerson WithFirstName(std::string first) const
	{
		SimplePerson result {*this};
		result.m_firstName = std::move(first);
		return result;
	}

	SimplePerson WithLastName(std::string last) const
	{
		SimplePerson result {*this};
		result.m_lastName = std::move(last);
		return result;
	}

	const std::string& First()
	{
		return m_firstName;
	}
	const std::string& Last()
	{
		return m_lastName;
	}
private:
	std::string m_firstName;
	std::string m_lastName;
};

TEST_CASE("SimplePerson WithFirstName")
{
	SimplePerson testObject {"Mike", "Williams"};
	auto wife {testObject.WithFirstName("Stephanie")};

	REQUIRE("Stephanie" == wife.First());
	REQUIRE("Williams" == wife.Last());
}

TEST_CASE("SimplePerson WithLastName")
{
	SimplePerson testObject {"Mike", "Williams"};
	auto dude {testObject.WithLastName("Jones")};

	REQUIRE("Mike" == dude.First());
	REQUIRE("Jones" == dude.Last());
}

class FancyPerson
{
public:
	FancyPerson(std::string first, std::string last)
		: m_firstName{std::move(first)}
		, m_lastName{std::move(last)}
	{
	}
	FancyPerson(const FancyPerson& other)
		: m_firstName{other.m_firstName}
		, m_lastName{other.m_lastName}
	{
		// make the copy arbitrarily expensive
		 std::this_thread::sleep_for(1ms);
	}

	FancyPerson(FancyPerson&& other)
		: m_firstName{std::move(other.m_firstName)}
		, m_lastName{std::move(other.m_lastName)}
	{
	}

	FancyPerson WithFirstName(std::string first) const &
	{
		FancyPerson result {*this};
		result.m_firstName = std::move(first);
		return result;
	}

	FancyPerson WithFirstName(std::string first) &&
	{
		FancyPerson result {std::move(*this)};
		result.m_firstName = std::move(first);
		return FancyPerson{std::move(first), std::move(m_lastName)};
	}

	FancyPerson WithLastName(std::string last) const &
	{
		FancyPerson result {*this};
		result.m_lastName = std::move(last);
		return result;
	}

	FancyPerson WithLastName(std::string last) &&
	{
		FancyPerson result {std::move(*this)};
		result.m_lastName = std::move(last);
		return result;
	}

	const std::string& First()
	{
		return m_firstName;
	}
	const std::string& Last()
	{
		return m_lastName;
	}
private:
	std::string m_firstName;
	std::string m_lastName;
};

TEST_CASE("FancyPerson WithFirstName")
{
	FancyPerson testObject {"Mike", "Williams"};
	auto wife {testObject.WithFirstName("Stephanie")};

	REQUIRE("Stephanie" == wife.First());
	REQUIRE("Williams" == wife.Last());
}

TEST_CASE("FancyPerson WithLastName")
{
	FancyPerson testObject {"Mike", "Williams"};
	auto dude {testObject.WithLastName("Jones")};

	REQUIRE("Mike" == dude.First());
	REQUIRE("Jones" == dude.Last());
}

TEST_CASE("Performance testing")
{
	SimplePerson simpleTestObject {"Mike", "Williams"};
	BENCHMARK("Copy assignment unoptimized")
	{	
		auto result {simpleTestObject.WithLastName("Stephen").WithLastName("Strange")};
	};

	FancyPerson fancyTestObject {"Mike", "Williams"};
	BENCHMARK("Copy assignment optimized")
	{	
		auto result {fancyTestObject.WithLastName("Stephen").WithLastName("Strange")};
	};
}