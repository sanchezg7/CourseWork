#include "Package.h"
#include "OvernightPackage.h"
using namespace std;

OvernightPackage::OvernightPackage(const string &sName, const string &sAddress,
	const string &sCity, const string &sState, int sZIP,
	const string &rName, const string &rAddress, const string &rCity,
	const string &rState, int rZIP, double w, double cost, double fee)
	:Package (sName, sAddress, sCity, sState, sZIP, rName, rAddress, rCity,
	rState, rZIP, w, cost)
{
	setFee(fee);
}

void OvernightPackage::setFee(const double fee)
{
	feePerOunce = fee;
}

double OvernightPackage::getFee() const
{
	return feePerOunce;
}

double OvernightPackage::calculateCost()
{
	return (getFee() * getWeight()) + (Package::calculateCost());
}

