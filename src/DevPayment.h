/*
 * Copyright (c) 2018 The resq Core developers
 * Copyright (c) 2019 The Bitcoin Monster Core developers
 * Distributed under the MIT software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 *
 */

#ifndef SRC_FOUNDERPAYMENT_H_
#define SRC_FOUNDERPAYMENT_H_
#include <string>
#include "amount.h"
#include "primitives/transaction.h"
#include "base58.h"
using namespace std;

static const char* DEFAULT_FOUNDER_ADDRESS = "Rnf9w6gEke3o7gUorrTVeyd9eGZjrxdGWK";

class DevPayment {
public:
	DevPayment(const char* address = DEFAULT_FOUNDER_ADDRESS) {
		founderAddress.SetString(address);
	}
	~DevPayment(){};
	CAmount getDevPaymentAmount(int blockHeight, CAmount blockReward);
	void FillDevPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutDevRet);
	bool IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward);
private:
	CBitcoinAddress founderAddress;
};



#endif /* SRC_FOUNDERPAYMENT_H_ */
