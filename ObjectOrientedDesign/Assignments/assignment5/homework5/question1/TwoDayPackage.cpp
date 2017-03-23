#include "Package.h"
#include "TwoDayPackage.h"

using namespace std;


TwoDayPackage::TwoDayPackage(const string &sName, const string &sAddress,
	const string &sCity, const string &sState, int sZIP,
	const string &rName, const string &rAddress, const string &rCity,
	const string &rState, int rZIP, double w, double cost, double flat)
	: Package(sName, sAddress,sCity, sState, sZIP,
	rName, rAddress, rCity,rState, rZIP, w, cost)
{
	setFlatFee(flat);
}

double TwoDayPackage::getFlatFee() const
{
	return flatFee;
}

void TwoDayPackage::setFlatFee(const double fee)
{
	flatFee = fee;
}


double TwoDayPackage::calculateCost()
{
	return (getFlatFee()) + (Package::calculateCost());
}



