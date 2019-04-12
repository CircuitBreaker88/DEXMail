 /*Copyright (c) 2010 Satoshi Nakamoto
 * Copyright (c) 2009-2014 The Bitcoin developers
 * Copyright (c) 2014-2015 The Dash developers
 * Copyright (c) 2015-2019 The PIVX developers
 * Copyright (c) 2019 The DEXMail developers
 * Distributed under the MIT software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 *
 * DevPayment.cpp
 */

#include "DevPayment.h"
//#include "standard.h";
#include "util.h"
#include "chainparams.h"
#include <boost/foreach.hpp>

CAmount DevPayment::getDevPaymentAmount(int blockHeight, CAmount blockReward) {
	 if (blockHeight < 200){
		 return 0;
	 }
	 return blockReward * 0.05;
}

void DevPayment::FillDevPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutDevRet) {
    // make sure it's not filled yet
	txoutDevRet = CTxOut();

    CScript payee;
    // fill payee with the dev address
    payee = GetScriptForDestination(devAddress.Get());

    // GET DEV PAYMENT VARIABLES SETUP
    CAmount DEVdevPayment = getDevPaymentAmount(nBlockHeight, blockReward);
    // split reward between miner ...
    txNew.vout[0].nValue -= devPayment;
    // ... and masternode
    txoutDevRet = CTxOut(devPayment, payee);
    txNew.vout.push_back(txoutDevRet);
    LogPrintf("CMasternodePayments::FillDevPayment -- Dev payment %lld to %s\n", devPayment, devAddress.ToString());
}

bool DevPayment::IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward) {
	CScript payee;
	// fill payee with the dev address
	payee = GetScriptForDestination(devAddress.Get());
	CAmount devReward = getDevPaymentAmount(height, blockReward);
	BOOST_FOREACH(const CTxOut& out, txNew.vout) {
		if(out.scriptPubKey == payee && out.nValue >= devReward) {
			return true;
		}
	}

	return false;
}
