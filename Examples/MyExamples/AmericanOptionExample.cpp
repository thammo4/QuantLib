// FILE: `QuantLib/Examples/MyExamples/BlackScholesExample.cpp`
#include <iostream>

#include <ql/qldefines.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/processes/blackscholesprocess.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/payoff.hpp>
#include <ql/exercise.hpp>


using namespace QuantLib;

int main () {
	std::cout << "hello, world!" << std::endl;

	//
	// Setup Calendar/Dates
	//

	Calendar calendar = TARGET(); 						// TARGET = Trans-European Automated Real-time Gross Settlement Express Transfer
	Date today = Date::todaysDate();
	Settings::instance().evaluationDate() = today;


	//
	// Define Option Parameters
	//

	Real underlying = 100;
	Real strike = 100;
	Rate dividendYieldRate = 0.00;
	Rate riskFreeRate = 0.05;
	Volatility vol = 0.20;
	Date maturity(17, July, 2024);

	Option::Type optionType = Option::Call;
	DayCounter dayCounter = Actual365Fixed();


	//
	// Define Underlying Asset Handle
	//

	Handle<Quote> underlyingH(ext::make_shared<SimpleQuote>(underlying));

	//
	// Define Term Structures - Dividend Yield, Yield, Volatility
	//

	Handle<YieldTermStructure> dividendYieldTS(ext::make_shared<FlatForward>(today, dividendYieldRate, dayCounter));
	Handle<YieldTermStructure> riskFreeTS(ext::make_shared<FlatForward>(today, riskFreeRate, dayCounter));

	Handle<BlackVolTermStructure> volTS(ext::make_shared<BlackConstantVol>(today, calendar, vol, dayCounter));


	//
	// Define Black-Scholes for Underlying's Dynamics
	//

	auto bsmProcess = ext::make_shared<BlackScholesMertonProcess>(underlyingH, dividendYieldTS, riskFreeTS, volTS);


	//
	// Configure Option's Exercise, Payoff
	//

	auto amrExercise = ext::make_shared<AmericanExercise>(today, maturity);
	auto payoff = ext::make_shared<PlainVanillaPayoff>(optionType, strike);


	//
	// Instantiate VanillaOption
	//

	VanillaOption amrOption(payoff, amrExercise);


	//
	// Compute American Option Price via Barone-Adesi Whitney Pricing Engine
	//

	amrOption.setPricingEngine(ext::make_shared<BaroneAdesiWhaleyApproximationEngine>(bsmProcess));


	//
	// Define Option Price as Net Present Value
	//

	Real optionPrice = amrOption.NPV();

	std::cout << "AMR-Style Option Price [NPV]: " << optionPrice << std::endl;

	return 0;
}



//
// OUTPUT
//

// thammons@toms-MacBook-Air MyExamples % ./AmericanOptionExample 
// hello, world!
// AMR-Style Option Price [NPV]: 2.40209