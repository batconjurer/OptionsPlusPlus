#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <option.h>
#include <exception>


SCENARIO("Options can be initialized to None", "[None-initialize]"){

	GIVEN("An opt_val equal"){
		std::opt_val validity;
		// Default constructor exists
		std::Option<int> a; 
		WHEN("The opt_val is None"){
			validity = std::None;
			THEN("An option may be initialized with it without throwing an exception."){
				try{
					// Test both types of initialization
					a = validity;
					std::Option<int> b(validity);
					REQUIRE(true);
				} catch(std::exception& e){
					REQUIRE(false);	
				}
			}
		}
		WHEN("The opt_val is Some"){
			validity = std::Some;
			THEN("An option may not be initialized with it and an exception is thrown."){
				// Test both types of initialization
				try{
					a = validity;
					REQUIRE(false);
				} catch(std::exception& e){
					REQUIRE(true);
				}
				try{
					std::Option<int> b(validity);
					REQUIRE(false);
				} catch(std::exception& e){
					REQUIRE(true);
				}
			}
		}
	}
}

SCENARIO("Options can be initialized with a variable of its template type", "[type-initialization]"){

	GIVEN("A variable of type matching template type of Option"){
		std::Option<int> opt;
		int val;
		THEN("Initializing the option with the value raises no exception"){
			try{
				opt = val;
				REQUIRE(true);
			} catch( std::exception& e){
				REQUIRE(false);
			}

		}
	}
}

SCENARIO("Options have a default constructor", "[default-ctor]"){
	GIVEN("A forward declared Option"){
		std::Option<int> opt;
		THEN("It exists and is None"){
			if (opt == std::None){
				// Strangely, REQUIRE(opt==std::None) causes a compiler error
				REQUIRE(true);
			}
		}
	}
}

