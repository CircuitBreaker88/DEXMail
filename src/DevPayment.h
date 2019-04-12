/*Copyright (c) 2010 Satoshi Nakamoto
* Copyright (c) 2009-2014 The Bitcoin developers
* Copyright (c) 2014-2015 The Dash developers
* Copyright (c) 2015-2019 The PIVX developers
* Copyright (c) 2019 The DEXMail developers
* Distributed under the MIT software license, see the accompanying
* file COPYING or http://www.opensource.org/licenses/mit-license.php.
*
* DevPayment.h
*/

#ifndef SRC_DEVPAYMENT_H_
#define SRC_DEVPAYMENT_H_
#include <string>
#include "amount.h"
#include "primitives/transaction.h"
#include "base58.h"
using namespace std;

static const char* DEFAULT_DEV_ADDRESS = "";

class DevPayment {
public:
	DevPayment(const char* address = DEFAULT_DEV_ADDRESS) {
		devAddress.SetString(address);
	}
	~DevPayment(){};
	CAmount getDevPaymentAmount(int blockHeight, CAmount blockReward);
	void FillDevPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutDevRet);
	bool IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward);
private:
	CBitcoinAddress devAddress;
};



#endif /* SRC_DEVPAYMENT_H_ */
