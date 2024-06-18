// FILE: `QuantLib/Examples/MyExamples/BlackScholesExample.cpp`
#include <iostream>

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



using namespace QuantLib;

int main() {
	std::cout << "hello, world!" << std::endl;

	//
	// Setup Calendar/Dates
	//

	Calendar calendar = TARGET(); // TARGET = Trans-European Automated Real-time Gross Settlement Express Transfer [cal used by ECB/Eurobanks]
	Date today = Date::todaysDate();
	Settings::instance().evaluationDate() = today;

	
	//
	// Specify Option Parameters
	//

	Real underlying = 100;
	Real strike = 100;
	Rate dividendRate = 0.00;
	Rate riskFreeRate = 0.05;
	Volatility vol = 0.20;
	Date maturity(17, July, 2024);

	Option::Type optionType = Option::Call;
	DayCounter dayCounter = Actual365Fixed();


	//
	// Define underlying
	//

	Handle<Quote> underlyingH(ext::make_shared<SimpleQuote>(underlying));


	//
	// Define Yield/Dividend/Volatility Term Structures
	//

	Handle<YieldTermStructure> dividendRateTS(ext::make_shared<FlatForward>(today, dividendRate, dayCounter));
	Handle<YieldTermStructure> riskFreeTS(ext::make_shared<FlatForward>(today, riskFreeRate, dayCounter));
	Handle<BlackVolTermStructure> volTS(ext::make_shared<BlackConstantVol>(today, calendar, vol, dayCounter));

	
	//
	// Configure Option - Exercise Type, Payoff
	//

	auto europeanExercise = ext::make_shared<EuropeanExercise>(maturity);
	auto payoff = ext::make_shared<PlainVanillaPayoff>(optionType, strike);


	//
	// Define Black-Scholes Model for Underlying Dynamics
	//

	auto bsmProcess = ext::make_shared<BlackScholesMertonProcess>(underlyingH, dividendRateTS, riskFreeTS, volTS);


	//
	// Instantiate Vanilla Option
	//

	VanillaOption europeanOption(payoff, europeanExercise);


	//
	// Use PricingEngine to Compute Option Price
	//

	europeanOption.setPricingEngine(ext::make_shared<AnalyticEuropeanEngine>(bsmProcess));

	
	//
	// Define Option Price to be the Net Present Value
	//

	Real optionPrice = europeanOption.NPV();

	std::cout << "Option Price [NPV]: " << optionPrice << std::endl;

	
	//
	// No mas
	//

	return 0;
}


//
// OUTPUT
//

// thammons@toms-MacBook-Air MyExamples % ./BlackScholesExample 
// hello, world!
// Option Price [NPV]: 2.44807