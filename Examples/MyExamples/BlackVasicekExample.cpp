// FILE: `QuantLib/Examples/MyExamples/BlackKarasinskiExample.cpp`

#include <iostream>
// #include <ql/quantlib.hpp>
#include <ql/qldefines.hpp> 											// QuantLib basic definitions/types/configs
#include <ql/instruments/vanillaoption.hpp>  							// Option type definitions
#include <ql/pricingengines/vanilla/analyticeuropeanengine.hpp> 		// Pricing engine for option price under analytic models
#include <ql/time/calendars/target.hpp> 								// Date/calendar management
#include <ql/termstructures/yield/flatforward.hpp> 						// Yield term structure
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp> 	// Volatility curve term structure
#include <ql/processes/blackscholesprocess.hpp> 						// Define underlying's stochastic process
#include <ql/quotes/simplequote.hpp> 									// Defines SimpleQuote class (mutable holder for quote number, e.g. Observable)
#include <ql/payoff.hpp> 												// Define option payoff
#include <ql/exercise.hpp> 												// Definitions/implementations of option exercise features (when/how ok to exercise)

int main() {
	std::cout << "hello, black!" << std::endl;
	std::cout << "hello, karasinski!" << std::endl;

	return 0;
}
